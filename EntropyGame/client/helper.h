#ifndef HELPER_H
#define HELPER_H

#include <utility>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

#include "globals.h"

using namespace std;

struct orderMove{
	pair<int,int> start;
	pair<int,int> end;
};

struct chaosMove{
	pair<int,int> tile;
	char color;
};

bool isGameOver();

bool makeChaosMove(chaosMove);
bool makeOrderMove(orderMove);
void undoChaosMove(chaosMove);
void undoOrderMove(orderMove);

bool isEmptyTile(int x,int y);


string getRow(int row);
string getColumn(int col);
int calculateStringScore(string s);
double calculateBoardScore();   

////////////////////////////////////
double dasHeuristic(string s);
double rohitHeuristic(string s);
double partialStringScore(string s);
double evalBoard(); 
////////////////////////////////////

vector<chaosMove> getChaosActions(char color);
vector<orderMove> getOrderActions();

void printChaosMove(chaosMove move); 
void printOrderMove(orderMove move);
void printX(string x);
void printBoard();


#endif
