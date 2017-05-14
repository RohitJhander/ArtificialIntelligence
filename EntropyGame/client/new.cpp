#include <iostream>
#include "new.h"

using namespace std;

bool isCutOffState(int currentDepth){
	return currentDepth == cutOffDepth;
}


double minValue(char color,int currentDepth,int& index){
	if( isCutOffState(currentDepth) || isGameOver() ) {
		return evalBoard();
	}
	vector<chaosMove> actionSet = getChaosActions(color);
	double minimum = DBL_MAX;
	double actionValue;
	for(int i=0;i<actionSet.size();i++){
		makeChaosMove(actionSet.at(i));
		colorsMap[color] = colorsMap[color]-1;
		remainingColors--;
		actionValue = maxValue(currentDepth+1,index);
		if(actionValue<minimum){
			minimum=actionValue;
			index = i; 
		}
		undoChaosMove(actionSet.at(i));
		colorsMap[color] = colorsMap[color]+1;
		remainingColors++;
	}
	return minimum;		
}

double maxValue(int currentDepth,int& index){
	if( isCutOffState(currentDepth) || isGameOver() ) {
		return evalBoard();
	}
	vector<orderMove> actionSet = getOrderActions();
	double maximum = -DBL_MAX;
	double actionValue;
	for(int i=0;i<actionSet.size();i++){	
		makeOrderMove(actionSet.at(i));
		actionValue = expectedValue(currentDepth+1,index); 
		if(actionValue>maximum){
			maximum = actionValue;
			index=i;
		}
		undoOrderMove(actionSet.at(i));	
	}
	return maximum;
}


double expectedValue(int currentDepth,int&index){
	if( isCutOffState(currentDepth) || isGameOver() ) {
		return evalBoard();
	}
	double probability;
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
			expectedValue += probability*minValue(colour,currentDepth+1,index);	
		}else{
			probability=0;
		}	
		ascii++;
	}
	return expectedValue;
}

chaosMove chaosAI(char color){
	vector<chaosMove> actionSet = getChaosActions(color);
	int index; 
	minValue(color,0,index);
	cerr<<"Index :"<<index<<" Size: "<<actionSet.size()<<endl;
	chaosMove move = actionSet[index];
	return move;
}

orderMove orderAI(){
	vector<orderMove> actionSet = getOrderActions();
	int index;
	maxValue(0,index);
	cerr<<"Index :"<<index<<" Size: "<<actionSet.size()<<endl;
	orderMove move = actionSet[index];
	return move;
}