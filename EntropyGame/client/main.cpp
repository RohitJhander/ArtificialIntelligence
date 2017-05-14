#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <utility>

#include "helper.h"
#include "globals.h"
#include "minimax.h"
#include "random.h"

using namespace std;

int boardSize;
char** board;
string role;
Scorer scoreCalc;
int cutOffDepth = 4;
map<char,int> colorsMap;
int remainingColors;


void playAsChaos(){

	printX("CHAOS");
	char color;
	chaosMove move;
	int order_x1,order_y1,order_x2,order_y2;
	orderMove order_move;
	
	cin>>color;
	//cerr << "Color received " << color << endl;
	
	move = chaosRandomAI(color);
	board[move.tile.first][move.tile.second]=color;
	//cerr << "Move by me := " << move.tile.first << " " << move.tile.second << endl;
		
	colorsMap[color] = colorsMap[color] - 1;
	remainingColors--;
	//cerr << "Remaining Colors = " << remainingColors << endl;
	
	printChaosMove(move);
	
	for(int i=0;i<boardSize*boardSize-1;i++){
	
		if(isGameOver()){
			return;
		}
	
		cin>>order_x1>>order_y1>>order_x2>>order_y2;
		//cerr << "Move by Order := " << order_x1 << " " << order_y1 << " -> " << order_x2 << " " << order_y2 << endl;
	
		order_move.start =  make_pair(order_x1,order_y1);
		order_move.end = make_pair(order_x2,order_y2);
		makeOrderMove(order_move);
		
		cin>>color;
		//cerr << "Color received :" << color << endl;	
	
		move = chaosAI(color);		
		
		//cerr << "Move by me := " << move.tile.first << " " << move.tile.second << endl;
		
		colorsMap[color] = colorsMap[color] - 1;
		remainingColors--;
		//cerr << "Remaining Colors := " << remainingColors << endl;

		board[move.tile.first][move.tile.second]=color;
	
		printChaosMove(move);
	}
	return;
}

void playAsOrder(){
	printX("ORDER");
	char color;
	int chaos_x,chaos_y;
	orderMove move;
	for(int i=0;i<boardSize*boardSize-1;i++){
	
		cin>>chaos_x>>chaos_y>>color;
		//cerr << "Moves by chaos received : ";
		//cerr << chaos_x << " " << chaos_y << " " << color << endl;
	
		board[chaos_x][chaos_y]=color;
		
		colorsMap[color] = colorsMap[color] - 1;
		remainingColors--;

		//cerr << "Remaining Colors := " << remainingColors << endl;

		if(isGameOver()){
			return;
		}

		move = orderAI();		
		
		
		//cerr << "Moves by me := " << move.start.first << " " << move.start.second << " -> " << move.end.first << " " << move.end.second << endl;
	
		makeOrderMove(move);
		
		printOrderMove(move);
	}
	
	cin>>chaos_x>>chaos_y>>color;
	//cerr << "Moves by chaos received := ";
	//cerr << chaos_x << " " << chaos_y << " " << color << endl;
	board[chaos_x][chaos_y]=color;
	
	colorsMap[color] = colorsMap[color] - 1;
	remainingColors--;

	//cerr << "Remaining Colors := " << remainingColors << endl;
	return;
}

int main(){
		
	srand (time(NULL));

	
	cin>>boardSize;
	cin>>role;

    //cerr<< " --- Role switched ---- "<<endl;
	//cerr << "Boardsize = " << boardSize << endl;
	//cerr << "Role = " << role << endl;

	// Allocating memory to board
	board = new char*[boardSize];			
	for(int i=0;i<boardSize;i++){
		board[i] = new char[boardSize];
	}	

	//Initialising board
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			board[i][j]='-';
		}
	}

	//Intialising colors map
	colorsMap.clear();
	int ascii = 65;
	char c;
	for(int i=0;i<boardSize;i++){
		c=ascii;
		colorsMap.insert(make_pair(c,boardSize));
		ascii++;
	}

	//Remaining colors
	remainingColors = boardSize*boardSize;

	if(role.compare("CHAOS")==0){
		playAsChaos();
	}else{
		playAsOrder();
	}
}
