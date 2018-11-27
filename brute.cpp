#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;


vector<vector<int>> set;
vector<int> arr;

vector<string> formattedSet;
int n = 10;

bool isValid(int row, int column){
	// Is there already a queen in this column?
	for(int r = 0; r < row; r++){
		if(formattedSet[r][column] == 'Q') return false;
	}
	// Is there already a queen in the 45 degree diagonal?
	int r = row-1, c = column-1;
	while(r >= 0 && c >= 0){
		if(formattedSet[r][c] == 'Q'){
		       	return false;
		}else{
			r--;
			c--;
		}
	}
	// Is there already a queen in the 135 degree diagonal?
	r = row-1, c = column+1;
	while(r >= 0 && c < n){
		if(formattedSet[r][c] == 'Q'){
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
	for(int j = 0; j < arr.size(); j++) {
		for(int k = 0; k < n; k++) {
			if(k != arr[j]) {
				formattedSet.push_back(".");
			}
			else {
				formattedSet.push_back("Q");
			}
		}
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
}


int main() {
	brute(5);

  for(int i = 0; i < set.size(); i++) {
	  for(int j = 0; j<set[i].size();j++) {
		cout<<set[i][j];
	  }
cout<<"\n"<<endl;
  }
}
