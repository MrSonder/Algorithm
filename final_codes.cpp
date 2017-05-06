// Game Algorithm
// Use: Point a = GiveNextMove(blocks);
// a.x and a.y will be used to extract axes.
int board[6][6] = {{0,0,0,0,0,0},{2,0,0,0,0,0},{2,2,0,0,0,0},{2,2,2,0,0,0},{2,2,2,2,0,0},{2,2,2,2,2,0}} ;
int no_of_branches = 0;

Point GiveNextMove(vector<vector<int>> blocks){
	for (int i=0; i<6;i++){
		for (int j=0; j<6;j++){
			board[i][j]=0;
		}
	}

	for (int i=0; i<blocks.size();i++){
		int pos_x = blocks[i][0];
		int pos_y = 5 - blocks[i][1];
		int color = blocks[i][2];
		board[pos_x][pos_y] = color;
		}
	return RobotMove(board);
}


Point RobotMove(int board[6][6]){
	//Special cases:
	int count_moves = 0;
	for (int i=0; i<6; i++){
		if (board[i][5] != 0) count_moves++;
	}
	if (count_moves == 0 or count_moves == 1){
		if (board[2][5] == 0) return Point(2,0); // it was Point(2,5)
		else return Point(3,0); // it was Point(3,5)
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
				//cout<<thisScore<<endl;
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
	return Point(move_i, 5-move_j); //It was Point(move_i, move_j)

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



// This is for mask. 
// Input should be 1 or 2 contours only (black & white as well).
// Use: Mat mask = MaskForTriangle(input);
Mat MaskForTriangle(Mat input){
	Mat nonZeroCoordinates;
	double multiple_scale = 1.1;
	double divide_scale = 0.9;
	findNonZero(input, nonZeroCoordinates);
	vector<int> points {640,0,480,0}; 
	points[0]=640; //xmin
	points[1]=0;   //xmax
	points[2]=480; //ymin
	points[3]=0;   //ymax
    for (int i = 0; i < nonZeroCoordinates.total(); i++ ) {
        if (nonZeroCoordinates.at<Point>(i).x < points[0]) points[0]=nonZeroCoordinates.at<Point>(i).x;
        if (nonZeroCoordinates.at<Point>(i).x > points[1]) points[1]=nonZeroCoordinates.at<Point>(i).x;
        if (nonZeroCoordinates.at<Point>(i).y < points[2]) points[2]=nonZeroCoordinates.at<Point>(i).y;
        if (nonZeroCoordinates.at<Point>(i).y > points[3]) points[3]=nonZeroCoordinates.at<Point>(i).y;        
    }
    vector<Point> my_points {Point(points[0]*divide_scale,points[2]*divide_scale),Point( (points[1]*multiple_scale>input.cols)?input.cols:points[1]*multiple_scale, (points[1]*multiple_scale>input.rows)?input.rows:points[3]*multiple_scale )};
    Mat result = Mat::zeros(input.size(),CV_8UC1);
	Rect my_rect = boundingRect(my_points);
	rectangle( result, my_rect.tl(), my_rect.br(), Scalar(255,255,255), -1, 8, 0 );
    return result;
}