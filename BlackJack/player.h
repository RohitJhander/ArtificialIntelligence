#ifndef __PLAYER_H_INCLUDED__   
#define __PLAYER_H_INCLUDED__   

#include <vector>
#include <utility>

#include "globals.h" 

// State Space
void createStateSpace();
void readDealerMaps();
// Transition
vector<transition> getPossibleTransitions(state,action);

// Reward
double reward(int);			

// Graph
void createGraph();

// Policy
void computePolicyWithoutSplit(double);
void computePolicyWithSplit();

// Utility
void printState(state);
void printAction(action);
void printPolicy();
void printPolicyWithSplit();

#endif 