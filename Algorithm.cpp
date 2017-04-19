#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace cv;
using namespace std;



int out_matrix[7][7];
int color_info = 0;
int no_of_branches = 0;
int no_of_branches2 = 0;

Point RobotMove(int board[6][6]);
void DrawTable(int board[6][6]);
int win(int board[6][6]);
void PlayerMove(int board[6][6]);

int GetScore(int board[6][6], int player);
int GetScore2(int board[6][6], int player);


/** @function main */
int main( int argc, char** argv )
{
  
	int board[6][6] = {{0,0,0,0,0,0},{2,0,0,0,0,0},{2,2,0,0,0,0},{2,2,2,0,0,0},{2,2,2,2,0,0},{2,2,2,2,2,0}} ;
	Point a = RobotMove(board);
	cout<<"X: "<<a.x<<endl;
	cout<<"Y: "<<a.y<<endl;

  	time_t start,end;
  	time (&start);
	  

  	time (&end);
  	double dif = difftime (end,start);
  	printf ("Elasped time is %.2lf seconds.\n", dif );
	  
  	return 0;
}


Point RobotMove(int board[6][6]){
	//Special cases:
	int count_moves = 0;
	for (int i=0; i<6; i++){
		if (board[i][5] != 0) count_moves++;
	}
	if (count_moves == 0 or count_moves == 1){
		if (board[2][5] == 0) return Point(2,5);
		else return Point(3,5);
	}
	int player = 1;
	int move_i = -1;
	int move_j = -1;
	double score = 0;
	no_of_branches = 0;
	for (int i=0; i<6;i++){
		for (int j=0; j<6;j++){
			if (board[i][j] == 0 and (j==5 or ((board[i][j+1]!=0) and (board[i+1][j+1]!=0) ))) {
				board[i][j] = player;
				double thisScore = GetScore(board, player*-1);
				thisScore /= no_of_branches;
				no_of_branches = 0;
				cout<<thisScore<<endl;
				if (thisScore > score){
					score = thisScore;
					move_i = i;
					move_j = j;
				}

				board[i][j] = 0;
			}

		}
	}
	//board[move_i][move_j] = player;
	return Point(move_i,move_j);

}

int GetScore(int board[6][6], int player){

	int score = 0;
	int counter = 0;
	if (win(board)==1) { no_of_branches++;return 1;}
	else if (win(board)==-1) { no_of_branches++;return 0;}
	else
		for (int i=0; i<6 ;i++){
			for (int j=0; j<6;j++){
				if (board[i][j] == 0 and (j==5 or ((board[i][j+1]!=0) and (board[i+1][j+1]!=0) ))) {
					board[i][j] = player;
					counter++;
					score = score + GetScore(board, player*-1);
					board[i][j] = 0;
				}

			}
		}
	if (counter == 0) no_of_branches++;
	return score;

}
int GetScore2(int board[6][6], int player){
	int score = 0;
	if (win(board)==1) {return 0;}
	//if (win(board)==1) {no_of_branches2++;return 0;}
	else if (win(board)==-1) {return 1;}
	//else if (win(board)==-1) {no_of_branches2++;return 1;}
	else
		for (int i=0; i<6 ;i++){
			for (int j=0; j<6;j++){
				if (board[i][j] == 0 and (j==5 or ((board[i][j+1]!=0) and (board[i+1][j+1]!=0) ))) {
					board[i][j] = player;
					score = score + GetScore2(board, player*-1);
					board[i][j] = 0;
				}

			}
		}
	return score;

}

void DrawTable(int board[6][6]){
	//cout<<"X";
	cout<<"\t"<<"\t"<<"Table"<<endl;
	for (int j = 0; j<6;j++){
		//cout<<i<<"\t";
		for (int i = 0; i<6;i++){
			cout<<board[i][j]<<"\t";		
  		}
  		cout<<endl;
	}	
	//cout<<"Y"<<"\t"<<0<<"\t"<<1<<"\t"<<2<<"\t"<<3<<"\t"<<4<<"\t"<<5<<endl;
}

int win(int board[6][6]){
	int win_conditions[30][3][2] ={{{0,0},{0,1},{0,2}},
								  {{0,1},{0,2},{0,3}},
								  {{0,2},{0,3},{0,4}},
								  {{0,3},{0,4},{0,5}},
								  {{1,1},{1,2},{1,3}},
								  {{1,2},{1,3},{1,4}},
								  {{1,3},{1,4},{1,5}},
								  {{2,2},{2,3},{2,4}},
								  {{2,3},{2,4},{2,5}},
								  {{3,3},{3,4},{3,5}},
								  {{0,0},{1,1},{2,2}},
								  {{1,1},{2,2},{3,3}},
								  {{2,2},{3,3},{4,4}},
								  {{3,3},{4,4},{5,5}},
								  {{0,1},{1,2},{2,3}},
								  {{1,2},{2,3},{3,4}},
								  {{2,3},{3,4},{4,5}},
								  {{0,2},{1,3},{2,4}},
								  {{1,3},{2,4},{3,5}},
								  {{0,3},{1,4},{2,5}},
								  {{0,2},{1,2},{2,2}},
								  {{0,3},{1,3},{2,3}},
								  {{1,3},{2,3},{3,3}},
								  {{0,4},{1,4},{2,4}},
								  {{1,4},{2,4},{3,4}},
								  {{2,4},{3,4},{4,4}},
								  {{0,5},{1,5},{2,5}},
								  {{1,5},{2,5},{3,5}},
								  {{2,5},{3,5},{4,5}},
								  {{3,5},{4,5},{5,5}},
								};
	for (int x=0;x<30;x++)
	{
		if (board[win_conditions[x][0][0]][win_conditions[x][0][1]] != 0 and
			board[win_conditions[x][0][0]][win_conditions[x][0][1]] == board[win_conditions[x][1][0]][win_conditions[x][1][1]] and
			board[win_conditions[x][0][0]][win_conditions[x][0][1]] == board[win_conditions[x][2][0]][win_conditions[x][2][1]]
			) {return board[win_conditions[x][0][0]][win_conditions[x][0][1]];}
	}								
	return 0;
}



void PlayerMove(int board[6][6]) {
	/*
	int player = -1;
    int move_i = -1;
	int move_j = -1;
	double score = 0;
	no_of_branches2 = 0;
	for (int i=0; i<6;i++){
		for (int j=0; j<6;j++){
			if (board[i][j] == 0 and (i==5 or ((board[i][j+1]!=0) and (board[i+1][j+1]!=0) ))) {
				board[i][j] = player;
				double thisScore = GetScore2(board, player*-1);
				//thisScore /= no_of_branches2;
				//no_of_branches2 = 0;
				cout<<thisScore<<endl;
				if (thisScore > score){
					score = thisScore;
					move_i = i;
					move_j = j;
				}

				board[i][j] = 0;
			}

		}
	}
	board[move_i][move_j] = player;
	*/
	int move_i = 0;
    int move_j = 0;
    while (true) {
        cout<<"What's your move y axis?"<<"\n"<<"> ";
        cin >> move_j;
        cout<<"your"<<move_j;
        cout<<"\n"<<"What's your move x axis?"<<"\n"<<"> ";
        cin >> move_i;
    	if (board[move_i][move_j] == 0 and (move_j==5 or ((board[move_i][move_j+1]!=0) and (board[move_i+1][move_j+1]!=0) ))){
    		board[move_i][move_j] = -1;
    		break;
    	}
    	cout<<"\n"<<"Invalid move."<<endl;
	}
}
