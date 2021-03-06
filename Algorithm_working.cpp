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

int minimax(int board[6][6], int player);
void DrawTable(int board[6][6]);
int win(int board[6][6]);
void PlayerMove(int board[6][6]);
void RobotMove(int board[6][6]);




/** @function main */
int main( int argc, char** argv )
{
  
	int board[6][6] = {{0,2,2,2,2,2},{0,0,2,2,2,2},{0,0,0,2,2,2},{0,0,0,0,2,2},{0,0,0,0,0,2},{0,0,0,0,0,0}} ;
	cout<<"Do you want to play first or second?"<<endl;
	cout<<"Write 1 to play first and 2 to play second"<<endl;
  	int player = 0;
  	cin >> player;
  	for (int turn=0; turn<21 and win(board) == 0;turn++){
  		cout<<"Turn is "<<turn<<endl;
  		if ((turn+player)%2 ==0) {
  			RobotMove(board);
  		}
  		else{
  			DrawTable(board);
  			PlayerMove(board);
  		}
	}
	cout<<win(board)<<endl;
  	waitKey(0);

  	time_t start,end;
  	time (&start);
	  

  	time (&end);
  	double dif = difftime (end,start);
  	printf ("Elasped time is %.2lf seconds.", dif );
	  
  	return 0;
}


int minimax(int board[6][6], int player){
	int winner = win(board);
	if (winner!=0) return winner*player;

	int move_i = -1;
	int move_j = -1;
	int score = -2;
	for (int i=0; i<6;i++){
		for (int j=0; j<6;j++){
			if (board[i][j] == 0 and (i==5 or ((board[i+1][j]!=0) and (board[i+1][j+1]!=0) ))) {
				board[i][j] = player;
				int thisScore = -minimax(board, player*-1);
				if (thisScore > score){
					score = thisScore;
					move_i = i;
					move_j = j;
				}
				board[i][j] = 0;
			}

		}
	}
	if (move_i == -1) return 0;
	return score;

}


void DrawTable(int board[6][6]){
	//cout<<"X";
	cout<<"\t"<<"\t"<<"Table"<<endl;
	for (int i = 0; i<6;i++){
		//cout<<i<<"\t";
		for (int j = 0; j<6;j++){
			cout<<board[i][j]<<"\t";		
  		}
  		cout<<endl;
	}	
	//cout<<"Y"<<"\t"<<0<<"\t"<<1<<"\t"<<2<<"\t"<<3<<"\t"<<4<<"\t"<<5<<endl;
}

int win(int board[6][6]){
	int win_conditions[33][3][2] ={{{0,0},{1,0},{2,0}},
								  {{0,0},{1,1},{2,2}},
								  {{1,0},{2,1},{3,2}},
								  {{1,0},{2,0},{3,0}},
								  {{1,1},{2,1},{3,1}},
								  {{1,1},{2,2},{3,3}},							
								  {{2,0},{2,1},{2,2}},
								  {{2,0},{3,0},{4,0}},
								  {{2,0},{3,1},{4,2}},
								  {{2,1},{3,1},{4,1}},
								  {{2,1},{3,2},{4,3}},
								  {{2,2},{3,3},{4,4}},
								  {{2,2},{3,2},{4,2}},
								  {{2,2},{3,1},{4,0}},
								  {{3,0},{4,0},{5,0}},
								  {{3,0},{3,1},{3,2}},
								  {{3,0},{4,1},{5,2}},
								  {{3,1},{3,2},{3,3}},
								  {{3,1},{4,1},{5,1}},
								  {{3,1},{4,2},{5,3}},
								  {{3,2},{4,1},{5,0}},
								  {{3,2},{4,2},{5,2}},
								  {{3,2},{4,3},{5,4}},
								  {{3,3},{4,2},{5,1}},
								  {{3,3},{4,3},{5,3}},
								  {{3,3},{4,4},{5,5}},
								  {{4,0},{4,1},{4,2}},
								  {{4,1},{4,2},{4,3}},
								  {{4,2},{4,3},{4,4}},
								  {{5,0},{5,1},{5,2}},
								  {{5,1},{5,2},{5,3}},
								  {{5,2},{5,3},{5,4}},
								  {{5,3},{5,4},{5,5}}
								};
	for (int x=0;x<33;x++)
	{
		if (board[win_conditions[x][0][0]][win_conditions[x][0][1]] != 0 and
			board[win_conditions[x][0][0]][win_conditions[x][0][1]] == board[win_conditions[x][1][0]][win_conditions[x][1][1]] and
			board[win_conditions[x][0][0]][win_conditions[x][0][1]] == board[win_conditions[x][2][0]][win_conditions[x][2][1]]
			) {return board[win_conditions[x][0][0]][win_conditions[x][0][1]];}
	}								
	return 0;
}

void RobotMove(int board[6][6]){
	int move_i = -1;
	int move_j = -1;
	int score = -2;
	for (int i=0; i<6;i++){
		for (int j=0; j<6;j++){
			if (board[i][j] == 0 and (i==5 or ((board[i+1][j] != 0) and (board[i+1][j+1] != 0))  )){
				board[i][j] = 1;
				int tempScore = -minimax(board, -1);
				board[i][j] = 0;
				if (tempScore > score){
					score = tempScore;
					move_i = i;
					move_j = j;
				}
				
			}

		}
	}
	board[move_i][move_j] = 1;
}


void PlayerMove(int board[6][6]) {
    int move_i = 0;
    int move_j = 0;
    while (true) {
        cout<<"What's your move y axis?"<<"\n"<<"> ";
        cin >> move_i;
        cout<<"your"<<move_i;
        cout<<"\n"<<"What's your move x axis?"<<"\n"<<"> ";
        cin >> move_j;
    	if (board[move_i][move_j] == 0 and (move_i==5 or ((board[move_i+1][move_j]!=0) and (board[move_i+1][move_j+1]!=0) ))){
    		board[move_i][move_j] = -1;
    		break;
    	}
    	cout<<"\n"<<"Invalid move."<<endl;
	}
}