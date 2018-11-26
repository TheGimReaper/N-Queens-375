#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/time.h>

using namespace std;

/* ----------GLOBAL VARIABLES---------- */
int n = 0;
// holds all valid boards
vector<vector<string>> boards;	
// initializing board to have no queens
vector<string> current_board;
/* ------------------------------------ */

int getTime(struct timeval *t){
	return gettimeofday(t, NULL);
}

int diffTime(struct timeval *start, struct timeval *end, struct timeval *difference){
	long int diff = (end -> tv_usec + 1000000 * end -> tv_sec) - (start -> tv_usec + 1000000 * start -> tv_sec);
	difference -> tv_sec = diff / 1000000;
	difference -> tv_usec = diff % 1000000;

	if(diff < 0){
		return -1;
	}
	return 0;
}


void printBoards(){
	for(int i = 0; i < boards.size(); i++){
		cout << "Solution #" << i+1 << ":" << endl;
		for(int j = 0; j < boards[i].size(); j++){
			cout << boards[i][j] << endl;
		}
	}
}

bool isValid(int row, int column){
	// Is there already a queen in this column?
	for(int r = 0; r < row; r++){
		if(current_board[r][column] == 'Q') return false;
	}
	// Is there already a queen in the 45 degree diagonal?
	int r = row-1, c = column-1;
	while(r >= 0 && c >= 0){
		if(current_board[r][c] == 'Q'){
		       	return false;
		}else{
			r--;
			c--;
		}
	}
	// Is there already a queen in the 135 degree diagonal?
	r = row-1, c = column+1;
	while(r >= 0 && c < n){
		if(current_board[r][c] == 'Q'){
			return false;
		}else{
			r--;
			c++;
		}
	}
	return true;
}

void backtracking(int row){
	// Base case, got to end of board
	if(row == n){
		boards.push_back(current_board);
	}
	// Iterate through all columns in the current row
	for(int column = 0; column < n; column++){
		// Checks if queen can be placed at [row][column]
		if(isValid(row, column)){
			// A queen can be placed here
			current_board[row][column] = 'Q';
			// Move forward with the puzzle
			backtracking(row+1);
			// Check for other possible solutions
			current_board[row][column] = '.';
		}
	}
}

int main(int argc, char **argv){
	struct timeval start, end, diff;
	if(argc != 3){
		cout << "Error: incorrect number of arguments. Usage: ./submission <n> <0/1/2>" << endl;
		exit(-1);
	}
	// size of NxN board
	n = atoi(argv[1]);
	// what algorithm to use: 0 = brute force, 1 = backtracking, 2 = bit mask
	int algorithm = atoi(argv[2]);

	// initializing board to no queens
	vector<string> test(n, string(n, '.'));
	current_board = test;


	cout << "Generating solutions . . . " << endl;
	getTime(&start);
	// call brute force
	if(algorithm == 0){

	}
	// call back tracking
	else if(algorithm == 1){
		backtracking(0);
	}
	// call bit mask
	else if(algorithm == 2){

	}

	getTime(&end);
	diffTime(&start, &end, &diff);
	string time = to_string(diff.tv_sec) + "." + to_string(diff.tv_usec) + "s";
	ofstream oFile;
	oFile.open("output.txt", ios_base::app);
	oFile << "backtracking | n = " << n << " | solutions = " << boards.size() << " | " << time << endl;

	string ans = "";
	cout << "Would you like to print out all " << boards.size() << " solutions (Y/N)?" << endl;
	cin >> ans;
	if(ans == "Y"){
		printBoards();
	}
	return 0;
}
