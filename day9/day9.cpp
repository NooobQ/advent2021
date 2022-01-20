#include<unordered_set>
#include<iostream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<string>
#include<map>
using namespace std;

int main(){
	//Close Sync with stdio, Faster cin
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int matrix[150][150];
	string cinstring;
	int res = 0;
	int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int m = 0, n = 0;

	while(getline(cin, cinstring)){
		//stringstream strcin(cinstring);
		int slen = cinstring.length();
		n = cinstring.length();
		for(int i = 0; i < slen; i++)
			matrix[m][i] = cinstring[i] - '0';
		m++;
	}
	
	auto check = [&](const int x, const int y){
		for(int i = 0; i < 4; i++){
			int a = x + dir[i][0], b = y + dir[i][1];
			if(a < 0 || b < 0 || a >= m || b >= n)
				continue;
			if(matrix[a][b] <= matrix[x][y])
				return false;
		}
		return true;
	};

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(check(i, j)){
				/* cout << i << '\t' << j <<endl; */
				res += matrix[i][j] + 1;
			}
		}
	}

	cout<<"Part I answer:\n";//>
	cout<<res<<'\n';//>>

	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}
