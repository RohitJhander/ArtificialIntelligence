#include "valueIteration.h"
#include "player.h"

using namespace std;

double chooseAction(double expectedDOUBLE, double expectedHIT, double expectedSTAND,action& a) {
	double max = expectedDOUBLE;
	a = DOUBLE;
	if (expectedHIT > max) { 
		max = expectedHIT;
		a = HIT;
	} 
	if (expectedSTAND > max) {
		max = expectedSTAND;
		a = STAND;
	}
	return max;
	/*if(expectedSTAND>expectedHIT){
		a=STAND;
		return expectedSTAND;
	}else{
		a=HIT;
		return expectedHIT;
	}
	*/
} 

void computeValue(int stateId){
	
	double maxValue = -DBL_MAX;
	action maxAction = X;

	if(stateSpace[stateId].goal){ 
		value[stateId] = reward(stateId);
		greedyPolicy[stateId]= X; 
	}else{
		double expectedDOUBLE=0;
		double expectedHIT=0;
		double expectedSTAND=0;
		action a;
		int sDash;		
		vector<transition> transitions = graph[stateId];
		for(int i=0;i<transitions.size();i++){
			//cout<<"transitions "<<transitions.size()<<endl;
			a = transitions[i].a; 
			sDash = transitions[i].id;
			if(a==DOUBLE){
				expectedDOUBLE += transitions[i].prob*2*(value[sDash]);			
			}else if(a==HIT){
				expectedHIT += transitions[i].prob*(value[sDash]);	
			}else if(a==STAND){
				expectedSTAND += transitions[i].prob*(value[sDash]);	
			}
		}
		//cout<<"S "<<expectedSTAND<<" H "<<expectedHIT<<" D "<<expectedDOUBLE<<endl;
		value[stateId] = chooseAction(expectedDOUBLE,expectedHIT,expectedSTAND,maxAction);
		//printAction(maxAction);
		//cout<<"VALUE ("<<stateId<<") "<<value[stateId]<<endl;
		greedyPolicy[stateId] = maxAction;
	}
}

void valueIteration(double epsilon){
	
	vector<int> greedPolicy(stateSpace.size());
	double residual;
	double prevValue;
	double maxResidual=0;
		
	for(int i=0;i<stateSpace.size();i++){
		value.push_back(0);
		greedyPolicy.push_back(X);
	}
	
	do{
		maxResidual=0;
		cout<<"Value Iterating ...... "<<endl;
		for(int i=0;i<stateSpace.size();i++){ 
			prevValue = value[i];
			computeValue(i);
			residual = fabs(value[i]-prevValue);
			if(residual>maxResidual){
				maxResidual=residual;
			}	
		}
		//cout<<"maxResidual"<<maxResidual<<endl;
	}while(maxResidual>=epsilon);
}