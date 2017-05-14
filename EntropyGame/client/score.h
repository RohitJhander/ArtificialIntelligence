#ifndef SCORE_H
#define SCORE_H

#include <vector>
#include <map>
#include <string>

using namespace std;

class Scorer{
private:
	bool isPal[8][8];
public:
	Scorer();
	double score(string s);
	//double dasHeuristic(string str);
};

#endif