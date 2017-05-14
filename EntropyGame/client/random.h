#ifndef RANDOM_H
#define RANDOM_H

#include "globals.h"
#include "helper.h"

#include <ctime>
#include <cstdlib>
#include <vector>
#include <utility>

using namespace std;

vector<orderMove> getValidOrderMovesFromTile(pair<int,int> coloredTile);
chaosMove chaosRandomAI(char c);
orderMove orderRandomAI();

#endif