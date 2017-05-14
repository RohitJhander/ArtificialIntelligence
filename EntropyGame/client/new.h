#ifndef NEW_H
#define NEW_H

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <float.h>


#include "globals.h"
#include "helper.h"

using namespace std;

bool isCutOffState(int currentDepth);
double minValue(char color,int currentDepth,int& index);
double maxValue(int currentDepth,int& index);
double expectedValue(int currentDepth,int& index);
chaosMove chaosAI(char color);
orderMove orderAI();

#endif
