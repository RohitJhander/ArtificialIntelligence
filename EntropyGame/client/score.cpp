#include "score.h"
#include <iostream>	

Scorer::Scorer(){
	for(int i=0;i!=64;i++){
		if(i/8==i%8||i/8==(i%8)+1)
			isPal[i/8][i%8]=true;
		else
			isPal[i/8][i%8]=false;
	}
}

double Scorer::score(string s){
	string input=s;
	int limit=s.size()+1;
	double score=0;
	for(int i=2;i!=limit;i++){
		int seclimit=limit-i;
		for(int j=0;j!=seclimit;j++){
			if(input[j]==input[j+i-1]&&isPal[j+1][j+i-2]){
				score+=i;	
				isPal[j][j+i-1]=true;
			}
			else{
				isPal[j][j+i]=false;
			}
		}
	}
	return score;
}

/*
double Scorer::dasHeuristic(string s){
	vector<pair<string,int> > str_gap;
	string str;
	int gap=0;
	bool inGap=true;
	map<int ,int> gapIndex;
	
	for(int i=0; i!=s.size();i++){
		if(s[i]!='-'&&inGap){
			inGap=false;
			if(str!=""){
				str_gap.push_back(make_pair(str,gap));
				// cout<<str<<" "<<gap<<endl;
				gapIndex[gap]=str_gap.size()-1;
			}
			str=s[i];
			gap=0;
		}
		else if(s[i]=='-'&&inGap){
			gap++;
		}
		else if(!inGap&&s[i]=='-'){
			inGap=true;
			gap++;
		}
		else {
			str+=s[i];
		}

		if(i==s.size()-1&&str!=""){
			str_gap.push_back(make_pair(str,gap));
			// cout<<str<<" "<<gap<<endl;
			gapIndex[gap]=str_gap.size()-1;
		}
	}
	double finScore=0,scoreComp=0;
	bool hasChanged;
	int count=0;

	for(int i=0;i!=str_gap.size();i++)
		scoreComp+=score(str_gap[i].first);
	for(map<int,int>::iterator i=gapIndex.begin();i!=gapIndex.end();i++){
		gap=str_gap[i->second].second;
		
		if(gap!=0){

			for(int j=0;j!=str_gap.size();j++)
				str_gap[j].second=max(0,str_gap[j].second-gap);
			
			count+=	gap;
			finScore+=gap*scoreComp;
			// cout<<gap<<" "<<scoreComp<<endl;
			string str;
			scoreComp=0;

			for(int j=0;j!=str_gap.size();j++){
				if(str_gap[j].second==0&&j!=str_gap.size()-1){
					str+=str_gap[j].first;
				}
				else{
					str+=str_gap[j].first;
					scoreComp+=score(str);
					str="";
				}
			}

		}
	}

	finScore+=(s.size()-2-count)*scoreComp;
	// cout<<(s.size()-2-count)<<" "<<scoreComp<<endl;

	return finScore;

}

*/
// int main(){
// 	Scorer skr;
// 	while(1){
// 		string in;
// 		cin>>in;
// 		cout<<skr.partialScore(in)<<endl;
// 	}
// }