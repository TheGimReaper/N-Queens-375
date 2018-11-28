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
//for getting combinations for brute force
vector<vector<int>> set;
vector<int> arr;

/* ------------------------------------ */

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

void getPermutations(int start, int end) {
    if(start == end) {
	current_board.clear();
	for(int j = 0; j < arr.size(); j++) {
		string str = "";
		for(int k = 0; k < n; k++) {
			if(k != arr[j]) {
				str += ".";
			}
			else {
				str += "Q";

			}
		}
		current_board.push_back(str);
	}

	bool valid = true;
	for(int i = 0; i < arr.size(); i++) {
		if(!isValid(i,arr[i])) {
			valid = false;
		}
	}
	if(valid == true) {
		set.push_back(arr);
	}
	return;
    }
    for(int i = start; i <= end; i++) {
        int temp;
        temp = arr[i];
	arr[i] = arr[start];
	arr[start] = temp;

	getPermutations(start+1,end);

        temp = arr[i];
	arr[i] = arr[start];
	arr[start] = temp;

    }
}

void brute(int n) {
	// get all possible combinations for placement of queen (one to a row)
        for(int i = 0; i < n; i++) {
	  arr.push_back(i);
	}
      	getPermutations(0,n-1);

	// format solutions back to "." and "Q"
	for(int i = 0; i < set.size(); i++) {
		vector<string> temp;
		for(int j = 0; j < set[i].size(); j++) {
			for(int k = 0; k < n; k++) {
				if(k != set[i][j]) {
					temp.push_back(".");
				}
				else {
					temp.push_back("Q");
				}
			}
		}
		boards.push_back(temp);
	}
}


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

void printBoardsBrute() {
	for(int i = 0; i < boards.size(); i++) {

		cout << "Solution #" << i+1 << ":" << endl;

		  int c = 0;
		for(int j = 0; j < boards[i].size(); j++){
			if(c == n) {
				c = 0;
				cout << ""<<endl;
			}
			c++;
			cout<<boards[i][j];
		}
		cout<<"\n"<<endl;
	}
}

void printBoards(){
	for(int i = 0; i < boards.size(); i++){
		cout << "Solution #" << i+1 << ":" << endl;
		for(int j = 0; j < boards[i].size(); j++){
			cout << boards[i][j] << endl;
		}
	}
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
	 brute(n);
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
		if(algorithm == 0) {
			printBoardsBrute();
		}
		else {

			printBoards();
		}
	}
	return 0;
}
