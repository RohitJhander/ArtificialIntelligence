#include "helper.h"

using namespace std;

bool isGameOver(){
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]=='-'){
				return false;
			}
		}
	}	
	return true;
}

bool makeChaosMove(chaosMove move){
	if(board[move.tile.first][move.tile.second]!='-'){
		return false;
	}
	board[move.tile.first][move.tile.second]=move.color;		
	return true;
}

bool makeOrderMove(orderMove move){
	if(move.start == move.end){
		return true;
	}
	board[move.end.first][move.end.second] = board[move.start.first][move.start.second];
	board[move.start.first][move.start.second]='-';
	return true;
}

void undoChaosMove(chaosMove move){
	board[move.tile.first][move.tile.second]='-';		
}

void undoOrderMove(orderMove move){
	
	if(move.start == move.end){
		return ;
	}
	
	board[move.start.first][move.start.second] = board[move.end.first][move.end.second];
	board[move.end.first][move.end.second]='-';
}

bool isEmptyTile(int x,int y){
	
	if(board[x][y]=='-'){
		return true;
	}
	
	return false;
}

string getRow(int row){
	string s;
	s = board[row];
	return s;	
}

string getColumn(int col){
	string s;
	for(int i=0;i<boardSize;i++){
		s += board[i][col];
	}
	
	return s;
}

int calculateStringScore(string s){
	return scoreCalc.score(s);
}

double calculateBoardScore(){
	
	double score=0;
	
	for(int i=0;i<boardSize;i++){
		score += calculateStringScore(getRow(i));
		score += calculateStringScore(getColumn(i));
	}

	return score;
}

double partialStringScore(string s){
	string partialString ="";
	double score =0;
	for(int j=0;j<s.size();j++){
		if(s[j] != '-'){
			partialString = partialString + s[j];
		}else{
			if(partialString.size() >=2 ){
				score += calculateStringScore(partialString);
			}
			partialString="";
		}
	}
	if(partialString.size()>=2){
		score += calculateStringScore(partialString);
	}
	return score;
}

double rohitHeuristic(string s){
	
	double numDashes=0;
	int ascii=65;
	double toReturn=0;
	char color;
	char c = ascii;
	double probColor;
	double probOfString;
	string origString = s;
	vector<int> dashes;
	vector<char> remColors;

	for(int i=0;i<s.size();i++){
		if(s[i]=='-'){
			numDashes++;
			dashes.push_back(i);			
		}
	}

	for(int i=0;i<colorsMap.size();i++){
		c=ascii;
		if(colorsMap[c] != 0){
			remColors.push_back(color);
		}
		ascii++;
	}

	probOfString = (numDashes/(double)remainingColors);
	double partialAns;
	for(int i=0;i<remColors.size();i++){
		color = remColors[i];
		partialAns=0;
		for(int j=0;j<dashes.size();j++){
			s = origString;
			s[dashes.at(j)] = color;
			probColor = ((double)colorsMap[color]/(double)remainingColors);
			partialAns +=  partialStringScore(s);
		}
		toReturn += probColor*partialAns;
	}	
	return  toReturn*probOfString;
}

double dasHeuristic(string s){
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
		scoreComp+=calculateStringScore(str_gap[i].first);
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
					scoreComp+=calculateStringScore(str);
					str="";
				}
			}

		}
	}

	finScore+=(s.size()-2-count)*scoreComp;
	// cout<<(s.size()-2-count)<<" "<<scoreComp<<endl;

	return finScore;

}

double evalBoard(){
	double score = 0;
	for(int i=0;i<boardSize;i++){
		 // score += rohitHeuristic(getColumn(i)) + rohitHeuristic(getRow(i));
		//score += partialStringScore(getColumn(i)) + partialStringScore(getRow(i));
		score += dasHeuristic(getColumn(i)) + dasHeuristic(getRow(i));	
	} 
	return score;
}

vector<chaosMove> getChaosActions(char color){
	
	vector<chaosMove> chaosActions;
	chaosMove move; 
	
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
				if(board[i][j]=='-'){
					move.tile = make_pair(i,j);
					move.color=color;
					chaosActions.push_back(move);
				}
		}	
	}
	
	return chaosActions;
}

vector<orderMove> getOrderActions(){
	
	vector<orderMove> possibleMoves;
	pair<int,int> coloredTile;
	orderMove move;
	int x,y;

	for(int i=0;i<boardSize;i++){

		for(int j=0;j<boardSize;j++){

			if(board[i][j]!='-'){
				
				coloredTile = make_pair(i,j);

				x = coloredTile.first;
				y = coloredTile.second;

				move.start = coloredTile;
				move.end = coloredTile;	
				possibleMoves.push_back(move);
					
				for(int itr=y-1;itr>=0;itr--){
					if(isEmptyTile(x,itr)){
						move.end = make_pair(x,itr);
						possibleMoves.push_back(move);
					}else{
						break;			
					}
				}
				
				for(int itr=y+1;itr<boardSize;itr++){
					if(isEmptyTile(x,itr)){
						move.end = make_pair(x,itr);
						possibleMoves.push_back(move);
					}else{
						break;			
					}
				}
				
				for(int itr=x+1;itr<boardSize;itr++){
					if(isEmptyTile(itr,y)){
						move.end = make_pair(itr,y);
						possibleMoves.push_back(move);
					}else{
						break;			
					}
				}
				
				for(int itr=x-1;itr>=0;itr--){
					if(isEmptyTile(itr,y)){
						move.end = make_pair(itr,y);
						possibleMoves.push_back(move);
					}else{
						break;			
					}
				}

			}
		}
	}
	
	return possibleMoves;
}

void printBoard(){
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			cerr<<board[i][j]<<" ";
			}
	}
	cerr<<endl;
}

void printChaosMove(chaosMove move){
	cout<<move.tile.first<<" "<<move.tile.second<<endl;
} 

void printOrderMove(orderMove move){
	cout<<move.start.first<< " " <<move.start.second<<" "<<move.end.first<<" "<<move.end.second<<endl;
}

void printX(string x){
	cerr<<x<<endl;
}