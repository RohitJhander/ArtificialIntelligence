#ifndef MINIMAX_H
#define MINIMAX_H

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <float.h>


#include "globals.h"
#include "helper.h"

using namespace std;

long long hashBoard();
bool isCutOffState(int currentDepth);
double MIN_VALUE(int currentDepth,char color,double alpha,double beta);
double MAX_VALUE(int currentDepth,double alpha,double beta);
double EXPECT_VALUE(int currentDepth,double alpha,double beta);
orderMove orderAI();
chaosMove chaosAI(char color);

#endif
