#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;


vector<vector<int>> set;
vector<int> arr;

vector<vector<string>> formattedSets;
vector<string> formattedSet;
int n = 5;

bool isValid(int row, int column){
	// Is there already a queen in this column?
	for(int r = 0; r < row; r++){
		if(formattedSet[r][column] == 'Q') {
			return false;
	
		}
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
	formattedSet.clear();
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
		formattedSet.push_back(str);
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
		formattedSets.push_back(temp);
	}
}


int main() {
	brute(n);
  for(int i = 0; i < set.size(); i++) {
	  for(int j = 0; j<set[i].size();j++) {
		cout<<set[i][j];
	  }
cout<<"\n"<<endl;
  }
  for(int i = 0; i < formattedSets.size(); i++) {
	  int c = 0;
	for(int j = 0; j < formattedSets[i].size(); j++){
		if(c == n) {
			c = 0;
			cout << ""<<endl;
		}
		c++;
		cout<<formattedSets[i][j];
	}
	cout<<"\n"<<endl;
  }
}
