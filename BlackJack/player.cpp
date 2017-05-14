#include "player.h"
#include "valueIteration.h"
#include "dealer.h"
#include <fstream>  
#include <sstream>

using namespace std;


bool isPair(state s){
	if(s.handValue%2==0 && s.handValue>2 && s.handValue<=20){
		return true;
	}
	return false;
}

void printState(state x){
	cout<<"---------STATE--------"<<endl;
	cout<<x.handValue<<endl;
	cout<<x.dealerCard<<endl;
	cout<<x.soft<<endl;
	cout<<x.goal<<endl;
	cout<<x.start<<endl;
	cout<<"----------------"<<endl;
}

void printAction(action a){	
	switch(a){
		case HIT:
			cout<<"H";
			break;
		case STAND:
			cout<<"S";
			break;
		case DOUBLE:
			cout<<"D";
			break;
		case SPLIT:
			cout<<"P";
			break;
		case X:
			cout<<"X";
			break;
		default:
			cout<<"X";
	}
	return;
}

double max3(double x, double y, double z) {
	double max = x; 
	if (y > max) { 
		max = y;
	} 
	if (z > max) {
		max = z;
	}
	return max;
} 

bool compareState(state state1,state state2){
	if(	state1.handValue == state2.handValue  
		&& state1.dealerCard == state2.dealerCard && state1.soft == state2.soft 
		&& state1.goal== state2.goal && state1.start == state2.start){
		return true;
	}
	return false;
}

bool isPlayerBlackJack(state playerState){
	if(playerState.start && playerState.goal &&  playerState.handValue==21 && playerState.soft){
		return true;
	}
	return false;
}

vector<double> splitString(string str, char delimiter) {
  vector<double> internal;
  stringstream ss(str); 
  string tok;
  while(getline(ss, tok, delimiter)) {
    internal.push_back(stof(tok));
  }
  return internal;
}

void readDealerMaps(){
	ifstream infile;
    infile.open ("hard.txt");
    string line="";
    int i=1;
    while((!infile.eof())){
		getline(infile,line);
		vector<double> v = splitString(line,' ');
    	dealerHardMap[i] = v;
    	i++;
    }
    infile.close();

 	ifstream infile1;
    infile1.open ("ace.txt");
    string line1= "";
    getline(infile1,line1);
	vector<double> v = splitString(line1,' ');
    dealerAce = v;
    infile1.close();
       
}

void createStateSpace(){	
	state tempState;
	cout<<"Creating stateSpace...."<<endl;

	for(int i=4;i<=22;i++){
		for(int j=2;j<=11;j++){
			tempState.handValue=i;
			tempState.dealerCard=j;
			tempState.soft=false;
			
			///
			tempState.goal=1;
			tempState.start=0;
			stateSpace.push_back(tempState);
			
			///
			tempState.goal=0;
			tempState.start=1;
			stateSpace.push_back(tempState);
			if(isPair(tempState)){
				pairStatesIndex.push_back(stateSpace.size()-1);
			}
			policy.push_back(stateSpace.size()-1);
			
			///
			tempState.goal=0;
			tempState.start=0;
			stateSpace.push_back(tempState);
			
			///
			tempState.goal=1;
			tempState.start=1;
			stateSpace.push_back(tempState);
		}
	}

	for(int i=1;i<=10;i++){
		for(int j=2;j<=11;j++){
			tempState.handValue=i+11;
			tempState.dealerCard=j;		
			tempState.soft=true;
			
			///
			tempState.goal=1;
			tempState.start=0;
			stateSpace.push_back(tempState);
			
			///
			tempState.goal=0;
			tempState.start=1;
			stateSpace.push_back(tempState);
			policy.push_back(stateSpace.size()-1);
			
			///
			tempState.goal=0;
			tempState.start=0;
			stateSpace.push_back(tempState);
			
			///
			tempState.goal=1;
			tempState.start=1;
			stateSpace.push_back(tempState);
		}
	}
}

int getStateId(state s){
	for(int i=0;i<stateSpace.size();i++){
		if(compareState(stateSpace[i],s)){
			return i; 
		}
	}
	// ERROR
	return -1;
}

vector<action> getPossibleActions(state intialState){
	vector<action> actions;
	
	if(intialState.start==1 && intialState.goal==0){
		actions.push_back(HIT);
		actions.push_back(STAND);
		actions.push_back(DOUBLE);
		return actions;
	}
	if(intialState.start==0 && intialState.goal==0){
		actions.push_back(HIT);
		actions.push_back(STAND);
		return actions;
	} 
	return actions;
}	

state getNextState(state initialState,action move,int actionValue){
	state finalState;
	switch(move){
		case HIT:
		{
			int newHandValue=0;
			finalState = initialState;
			if(!initialState.soft){ // IF HARD STATE
				if(actionValue == 1){ // IF ACE
					if(initialState.handValue+11>21){
						newHandValue = initialState.handValue+1;	
					}else{
						newHandValue = initialState.handValue+11;
						finalState.soft=true; 
					}
				}else{ //IF NOT ACE
					newHandValue = initialState.handValue+actionValue;
				}		
			}else{ 	// IF SOFT STATE
              	if(initialState.handValue+actionValue>21){
					newHandValue = initialState.handValue-10+actionValue;
					finalState.soft=false;
				}else{
					newHandValue = initialState.handValue + actionValue;
				}	
			}
			
			finalState.handValue = newHandValue;
			finalState.start=false;
	
			if(finalState.handValue==21){
				finalState.goal=true;
			}
			if(finalState.handValue > 21){
				finalState.handValue=22; 
				finalState.goal=true;
				finalState.soft=false;
			}
			break;
		}
		case STAND:
			finalState = initialState;
			finalState.goal=true;
			break;

		case DOUBLE:
			{
				int newHandValue=0;
				finalState = initialState;
				// IF HARD STATE
				if(!initialState.soft){
					// IF ACE
					if(actionValue == 1){
						if(initialState.handValue+11>21){
							newHandValue = initialState.handValue+1;	
						}else{
							newHandValue = initialState.handValue+11;
							finalState.soft=true;
						}
					//IF NOT ACE
					}else{ 
						newHandValue = initialState.handValue+actionValue;
					}
				// IF SOFT STATE			
				}else{ 	
		          	if(initialState.handValue+actionValue>21){
						newHandValue = initialState.handValue-10+actionValue;
					}else{
						newHandValue = initialState.handValue + actionValue;
					}	
				}

				finalState.handValue = newHandValue;
				finalState.goal=true;
				finalState.start=false;
				if(finalState.handValue > 21){
					finalState.handValue=22; 
					finalState.soft=false;
				}
				break;
			}
		default:
			break;
	}
	return finalState;	
}

vector<transition> getPossibleTransitions(state intialState){
	vector<transition> states;
    transition temp;
	vector<action> actions = getPossibleActions(intialState);
	action move;
	for(int j=0;j<actions.size();j++){
		move=actions[j];
		switch(move){
			case HIT:
				for(int i=1;i<=10;i++){
					temp.a = HIT;
					if(i==10){
						temp.sDash = getNextState(intialState,HIT,10);
						temp.id = getStateId(temp.sDash); 
						temp.prob = probabilityOfFaceCard;
					}else{
						temp.sDash = getNextState(intialState,HIT,i);
						temp.id = getStateId(temp.sDash);
						temp.prob = probabilityOfOtherCard;
					}
					states.push_back(temp);
				}
				break;
			case STAND:
				temp.a = STAND;
				temp.sDash = getNextState(intialState,STAND,0);
				temp.id = getStateId(temp.sDash);
				temp.prob = 1;
				states.push_back(temp);
				break;
			case DOUBLE:
				for(int i=1;i<=10;i++){
					temp.a = DOUBLE;
					temp.sDash = getNextState(intialState,DOUBLE,i);
					temp.id = getStateId(temp.sDash);
					if(i==10){
						temp.prob = probabilityOfFaceCard;
					}else{
						temp.prob = probabilityOfOtherCard;
					}
					states.push_back(temp);
				}
				break;
			default:
				break;
		}
	}
	return states;
}

double payOff(state playerState,int dealerScore,bool dealerBJ){

	bool isBlackJack = isPlayerBlackJack(playerState);
	double playerScore = playerState.handValue;

	// Push
	if(dealerBJ && isBlackJack){
		return 0;
	}	
	//a
	if(isBlackJack){
		return 1.5; 
	}
	//b
	if(playerScore>21){
		return -1.0;
	}
	//c
	if(dealerScore>21){
		return 1.0;
	}
	//d
	if(dealerScore>playerScore){
		return -1.0;
	}
	//e
	if(playerScore>dealerScore){
		return 1.0;
	}
	//f
	if(dealerBJ && !isBlackJack){
		return -1.0;
	}
	//g
	if(playerScore==dealerScore){
		return 0;
	}
	return 0;
}

double reward(int id){
	
	state s = stateSpace[id];
	
	if(!s.goal){
		return 0;
	}
	
	int playerScore = s.handValue;
	int dealerScore;
	double expectedReward=0;

	// BLACKJACK CASE
	double dealerBlackJackProb;
	if(s.dealerCard==11){
		dealerBlackJackProb = probabilityOfFaceCard;
	}else if(s.dealerCard==10){
		dealerBlackJackProb = probabilityOfOtherCard;
	}else{
		dealerBlackJackProb = 0;	
	}
	expectedReward += payOff(s,21,true)*dealerBlackJackProb;
	//////////////////////////
	
	
	double scoreProb;
	typedef map<int,double>::iterator it;
	
	vector<double> dealerTransitons;	
	
	if(s.dealerCard==11){
		dealerTransitons = dealerAce;
		//cout<<dealerAce.size()<<endl;	
	}else{
		dealerTransitons = dealerHardMap[s.dealerCard];
		//cout<<dealerTransitons.size()<<endl;		
	}

	//cout<<expectedReward<<" :E"<<endl;
	dealerScore =17;
	for(int i=0;i<dealerTransitons.size();i++){
		scoreProb = dealerTransitons[i];
		//cout<<"ScoreProb"<<scoreProb<<endl;
		expectedReward += payOff(s,dealerScore,false)*scoreProb;
		//cout<<"Hello"<<endl;
		dealerScore++;
	}
	//cout<<"Reward Calculated"<<expectedReward<<endl;
	return expectedReward;
}

void createGraph(){
	for(int i=0;i<stateSpace.size();i++){
		vector<transition> transitions = getPossibleTransitions(stateSpace[i]);
		graph.push_back(transitions);
	}
}

void computePolicyWithoutSplit(double e){
	cout<<"Computing policy without split ......"<<endl;
	valueIteration(e);
}

void printPolicy(){
	int i=0;
	while(i<policy.size()){
		int playerHand = stateSpace[policy[i]].handValue;
		bool soft = stateSpace[policy[i]].soft;
		if(playerHand>19 && !stateSpace[policy[i]].soft){
			i++;
			continue;
		}
		if(playerHand>20 && stateSpace[policy[i]].soft){
			i++;
			continue;
		}
		if(soft){
			cout<<"A"<<(playerHand-11)<<"  ";
			for(int j=2;j<=11;j++){
				if(stateSpace[policy[i]].dealerCard==j){
					printAction(greedyPolicy[policy[i]]);
					cout<<" ";
					i++;
				}
				else{
					cout<<"X";
					cout<<" ";
					i++;
				}
			}
			cout<<endl;
		}else{
			cout<<playerHand<<"  ";
			for(int j=2;j<=11;j++){
				if(stateSpace[policy[i]].dealerCard==j){
					printAction(greedyPolicy[policy[i]]);
					cout<<" ";
					i++;
				}
				else{
					cout<<"X";
					cout<<" ";
					i++;
				}
			}	
			cout<<endl;
		}
	}
}

double getValueWithSplit(state s){
	
	int pairCard = s.handValue/2;

	// Intialise Split States
	state split1;
	state split2;
	split1.dealerCard = s.dealerCard;
	split1.start=true;
	split1.goal=false;
	split2.dealerCard = s.dealerCard;
	split2.start=true;
	split2.goal=false;
	double valueX,valueY,pX,pY;
	double pValue;
	
	for(int x=1;x<=10;x++){
		for(int y=1;y<=10;y++){
		
			/////////////// FOR SPLIT1////////////
			if(x==1){
				split1.handValue = s.handValue+11; 
				split1.soft =true;
			}else{
				split1.handValue = s.handValue+x; 
			}
			valueX = value[getStateId(split1)];
			////////////////////////////////////


			////////////// FOR SPLIT2///////////
			if(y==1){
				split2.handValue = s.handValue+11; 
				split2.soft =true;	
			}else{
				split2.handValue = s.handValue+y;
			}
			valueY = value[getStateId(split1)];
			////////////////////////////////////

			
			////////////////////////////////
			if(x==10){
				pX = probabilityOfFaceCard;
			}else{
				pX = probabilityOfOtherCard;
			}

			if(y==10){
				pY = probabilityOfFaceCard;
			}else{
				pY = probabilityOfOtherCard;
			}
			///////////////////////////////


			////////////////////////////////
			if(x==pairCard && y==pairCard){
				pValue =  
			}else if(x==pairCard){
				pValue = 
			}else if(y==pairCard){
				pValue = 
			}else{
				pValue += pX*pY*(valueY+valueX);
			}
			////////////////////////////////
		}	
	}
	return pValue;
}

// NOT ACE CASE
void computePolicyWithSplit(){
	for(int i=0;i<pairStatesIndex.size();i++){
		double valueWithSplit = 0;//getValueWithSplit(stateSpace[pairStatesIndex[i]]); 
		double valueWithoutSplit = value[pairStatesIndex[i]];
		if(valueWithSplit>valueWithoutSplit){
			pairPolicy.push_back(SPLIT);
		}else{
			pairPolicy.push_back(greedyPolicy[pairStatesIndex[i]]);	
		}
	}
}

void printPolicyWithSplit(){
	// Print Ace-Ace policy before this
	int i=0;
	int dealerCard;
	int pair;
	while(i<pairPolicy.size()){
		pair = stateSpace[pairStatesIndex[i]].handValue/2;
		cout<<pair<<pair<<" ";
		for(int j=2;j<=11;j++){
			dealerCard = stateSpace[pairStatesIndex[i]].dealerCard;
			if(dealerCard==j){
				printAction(pairPolicy[i]);
				cout<<" ";
				i++;
			}else{
				cout<<"X";
				cout<<" ";
				i++;
			}
		}
		cout<<endl;
	}	
}