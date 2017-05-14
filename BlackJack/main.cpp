#include<iostream>

#include "globals.h"
#include "player.h"
#include "dealer.h"

using namespace std;

double probabilityOfFaceCard;
double probabilityOfOtherCard; 

vector<state> stateSpace;
vector<double> value;
vector<action> greedyPolicy;
vector<int> policy;
vector<vector<transition> > graph;

vector<int> pairStatesIndex;
vector<action> pairPolicy;

vector<double> dealerAce;
map<int,vector<double> > dealerHardMap;


int main(int argc, char **argv){
	probabilityOfFaceCard = atof(argv[1]);
	probabilityOfOtherCard = (1-probabilityOfFaceCard)/9;
	cout<<"Probability Of face card: "<<probabilityOfFaceCard<<endl;
	cout<<"Probability Of other card: "<<probabilityOfOtherCard<<endl;
	createStateSpace();
	cout<<"Number of states : "<<stateSpace.size()<<endl;
	createGraph();
	//cout<<"Graph created"<<endl;
	readDealerMaps();
	computePolicyWithoutSplit(1e-8);
	printPolicy(); 
	computePolicyWithSplit();
	printPolicyWithSplit();
}
