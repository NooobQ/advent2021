#include<unordered_set>
#include<iostream>
#include<vector>
#include<sstream>
using namespace std;

int check_row(vector<vector<pair<int, int>>> &bingo, int row);
int check_col(vector<vector<pair<int, int>>> &bingo, int col);
int calc_sum(vector<vector<pair<int, int>>> &bingo);
pair<int, int> set_matrix(vector<vector<pair<int, int>>> &bingo, int num);

int main(){
	//Close Sync with stdio, Faster cin
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	unordered_set<int> sequence_num;
	vector<vector<pair<int, int>>> matrix[102];
	unordered_set<int> num_set[102];
	for(int i = 0; i < 102; i++){
		for(int j = 0; j < 5; j++)
			matrix[i].push_back(vector<pair<int, int>>(5, make_pair(0, 0)));
	}

	//cout<<matrix[0].size()<<'\t'<<matrix[0][1].size();
	string sequence_bingo;
	cin>>sequence_bingo;
	
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 5; j++){
			for(int k = 0; k < 5; k++){
				int num;
				cin>>num;
				num_set[i].insert(num);
				matrix[i][j][k].first = num;
			}
		}	
	}

	istringstream _stream(sequence_bingo);
	char dot;
	int num;
	while(_stream>>num){
		_stream>>dot;
		//Process simulating BINGO
		//Duplicate num ignore
		if(sequence_num.count(num))
			continue;
		sequence_num.insert(num);
		
		//Traverse the BINGO matrix
		for(int i = 0; i < 100; i++){
			if(!num_set[i].count(num))		
				continue;
			auto rc = set_matrix(matrix[i], num);
			if(rc.first == -1){
				cout<<"Error occur.\n";
			}
			if(check_col(matrix[i], rc.second) || check_row(matrix[i], rc.first)){
				cout<<"Part I Answer:\t"<<calc_sum(matrix[i]) * num <<'\n';
				return 0;
			}
		}
	}

	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}

pair<int, int> set_matrix(vector<vector<pair<int, int>>> &bingo, int num){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++)
			if(bingo[i][j].first==num){
				bingo[i][j].second = 1;
				return make_pair(i, j);
			}
	}
	return make_pair(-1,-1);
}

int check_row(vector<vector<pair<int, int>>> &bingo, int row){
	for(int i = 0; i < 5; i++)
		if(!bingo[row][i].second)
			return 0;
	return 1;
}
int check_col(vector<vector<pair<int, int>>> &bingo, int col){
	for(int i = 0; i < 5; i++)
		if(!bingo[i][col].second)
			return 0;
	return 1;
}
int calc_sum(vector<vector<pair<int, int>>> &bingo){
	int sum = 0;
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			if(!bingo[i][j].second)
				sum += bingo[i][j].first;
		}
	}
	return sum;
}
