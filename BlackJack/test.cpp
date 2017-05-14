#include <iostream>
#include <map>
#include <vector>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <cstdlib>   
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

map<int,vector<double> > dealerHardMap;

vector<double> splitString(string str, char delimiter) {
  vector<double> internal;
  stringstream ss(str); 
  string tok;
  while(getline(ss, tok, delimiter)) {
    internal.push_back(stof(tok));
  }
  return internal;
}

void readDealerMaps(){
	ifstream infile;
    infile.open ("hard.txt");
    string line="";
    int i=2;
    while((!infile.eof())){
		getline(infile,line);
		vector<double> v = splitString(line,' ');
    	dealerHardMap[i] = v;
    	i++;
    }
    infile.close();
}


void print_vector(vector<double> v)
{
	for(int i=0;i<v.size();i++)
	{
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

void print_map(map<int,vector<double> > m)
{
	double totl=0;
	typedef map<int,vector<double> >::iterator it;
	for(it iterator = m.begin(); iterator != m.end(); iterator++)
	{
		print_vector(iterator->second);
	}
}

int main(){
	readDealerMaps();
	print_map(dealerHardMap);
}