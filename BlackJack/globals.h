#ifndef __GLOBALS_H_INCLUDED__   
#define __GLOBALS_H_INCLUDED__   

#include <iostream>
#include <map>
#include <vector>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <cstdlib>   
#include <string>

using namespace std;

typedef enum action{ HIT=0, STAND=1, SPLIT=2, DOUBLE=3,X=4} action;

typedef struct state{
	int handValue;
	int dealerCard;
	bool soft;
	bool goal;
	bool start;
}state;

typedef struct transition{
	state sDash;
	double prob;
	int id;
	action a;	
}transition;

extern double probabilityOfFaceCard;
extern double probabilityOfOtherCard;

extern vector<state> stateSpace;
extern vector<double> value;
extern vector<vector<transition> > graph;
extern vector<action> greedyPolicy;
extern vector<int> policy;


extern vector<int> pairStatesIndex;
extern vector<action> pairPolicy;

extern vector<double> dealerAce;
extern map<int,vector<double> > dealerHardMap;

#endif 
