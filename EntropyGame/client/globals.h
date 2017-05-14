#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <map>
#include "score.h"

using namespace std;

/* Global Varibales*/
extern int boardSize;
extern char** board;
extern string role;
extern Scorer scoreCalc;
extern int cutOffDepth;
extern map<char,int> colorsMap;
extern int remainingColors;

#endif

