
#include "random.h"
using namespace std;

vector<orderMove> getValidOrderMovesFromTile(pair<int,int> coloredTile){

	vector<orderMove> possibleMoves;
	
	orderMove move;

	int x = coloredTile.first;
	int y = coloredTile.second;

	move.start = coloredTile;

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

	return possibleMoves;
}

chaosMove chaosRandomAI(char c){
	
	vector<pair<int,int> > emptyTiles;

	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]=='-'){
				emptyTiles.push_back(make_pair(i,j));
			}
		}
	}

	int choice = rand()%(emptyTiles.size());
	pair<int,int> move = emptyTiles.at(choice);
	
	chaosMove toReturn;
	toReturn.tile = move;
	toReturn.color = c; 
	return toReturn;
}

orderMove orderRandomAI(){
	
	pair<int,int> start;
	pair<int,int> end;
	vector<pair<int,int> > coloredTiles;
	
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			if(board[i][j]!='-'){
				coloredTiles.push_back(make_pair(i,j));
			}
		}
	}

	orderMove toReturn;
	vector<orderMove> possibleMoves;
	int choice;
	
	for(int i=0;i<coloredTiles.size();i++){
		if(getValidOrderMovesFromTile(coloredTiles.at(i)).size()!=0){
			start = coloredTiles.at(i);
			possibleMoves = getValidOrderMovesFromTile(start);
			choice = rand()%possibleMoves.size();
			toReturn  = possibleMoves.at(choice);
			break;
		}
	}

 	return toReturn;
}
