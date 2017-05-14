#include <iostream>
#include <limits>
#include "minimax.h"

using namespace std;

bool isCutOffState(int currentDepth){
	return currentDepth == cutOffDepth;
}

chaosMove chaosAI(char color){
	
	double minimum = DBL_MAX;
	double actionValue;
	chaosMove decision;
	vector<chaosMove> actionSet = getChaosActions(color);
	

	// Nan issue
	if(actionSet.size()==1){
		return actionSet[0];
	}

	int test=0;
	cerr<<"Possible moves for chaos: "<<endl;
	for(int i=0;i<actionSet.size();i++){
		cerr<<actionSet[i].tile.first<<" "<<actionSet[i].tile.second<<" ,";
	}
	cerr<<endl;
	
	for(int i=0;i<actionSet.size();i++){
		
		makeChaosMove(actionSet.at(i));
		colorsMap[color] = colorsMap[color]-1;
		remainingColors--;

		actionValue = MAX_VALUE(1,-DBL_MAX,DBL_MAX);
		cerr<<"Node "<<i <<": "<<actionValue<<" , ";
		
		if(actionValue<minimum){
			minimum=actionValue;
			decision = actionSet[i]; 
			test=i;
		}

		undoChaosMove(actionSet.at(i));
		colorsMap[color] = colorsMap[color]+1;
		remainingColors++;
	
	}
	cerr<<endl;
	cerr<<"Best move's index: "<<test<<endl;
	return decision;		
}

orderMove orderAI(){

	double maximum = -DBL_MAX;
	double actionValue;	
	int test=0;
	orderMove decision;
	vector<orderMove> actionSet = getOrderActions();
	cerr<<"Possible moves for order: "<<endl;
	for(int i=0;i<actionSet.size();i++){
		cerr<<actionSet[i].start.first<< " " <<actionSet[i].start.second<<" "<<actionSet[i].end.first<<" "<<actionSet[i].end.second<<", ";
	}
		
	for(int i=0;i<actionSet.size();i++){
		
		makeOrderMove(actionSet.at(i));
		
		actionValue = EXPECT_VALUE(1,-DBL_MAX,DBL_MAX); 
		cerr<<"Node "<<i<<": "<<actionValue<<" , ";
		
		if(actionValue>maximum){
			maximum = actionValue;
			decision = actionSet[i];
			test=i;
		}	
	
		undoOrderMove(actionSet.at(i));	
	}
	cerr<<endl;
	cerr<<"Best move's index: "<<test<<endl;
	return decision;
}

double MIN_VALUE(int currentDepth,char color,double alpha, double beta){
	
	if( isCutOffState(currentDepth) || isGameOver() ) {
		double evalVal=evalBoard();
		return evalVal;
	}

	vector<chaosMove> actionSet = getChaosActions(color);
	double v = DBL_MAX;
	
	for(int i=0;i<actionSet.size();i++){
		makeChaosMove(actionSet.at(i));
		colorsMap[color] = colorsMap[color]-1;
		remainingColors--;


		v  = min(v,MAX_VALUE(currentDepth+1,alpha,beta));

		undoChaosMove(actionSet.at(i));
		colorsMap[color] = colorsMap[color]+1;
		remainingColors++;
	}
	return v;		
}

double MAX_VALUE(int currentDepth,double alpha, double beta){


	if( isCutOffState(currentDepth) || isGameOver() ) {

		double evalVal=evalBoard();
		return evalVal;
	}
	
	vector<orderMove> actionSet = getOrderActions();
	double v = -DBL_MAX;

	for(int i=0;i<actionSet.size();i++){	
		makeOrderMove(actionSet.at(i));
		v = max(v,EXPECT_VALUE(currentDepth+1,alpha,beta)); 
		undoOrderMove(actionSet.at(i));	
	}
	return v;	
}

double EXPECT_VALUE(int currentDepth,double alpha,double beta){
	if( isCutOffState(currentDepth) || isGameOver() ) {
		return evalBoard();
	}

	double probability,minVal;
	char colour;
	double expectedValue = 0;
	int ascii = 65;
	
	for(int i=0;i<boardSize;i++){
		colour=ascii;
		
		if(colorsMap[colour]==0){
			continue;
		}
		if(remainingColors!=0) {
			probability = ((double) colorsMap[colour])/((double )remainingColors);
		}else{
			probability=0;
		}

		if(probability!=0){
			expectedValue += probability*MIN_VALUE(currentDepth+1,colour,-DBL_MAX,DBL_MAX);
		}
		
		ascii++;
	}
	return expectedValue;
}
