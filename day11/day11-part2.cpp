#include<unordered_set>
#include<iostream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<string>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
using namespace std;

int main(){
	//Close Sync with stdio, Faster cin
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string cinstring;
	int res = 0;
	int matrix[120][120], vis[120][120];
	int m = 0, n = 0;
	queue<pair<int, int>> q;
	int dir[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1},};

	while(getline(cin, cinstring)){
		stringstream strcin(cinstring);
		int slen = cinstring.length();
		n = slen;
		char x;
		for(int i = 0; i < slen; i++){
			strcin >> x;
			matrix[m][i] = x - '0';
		}
		m++;
	}

	int loop = 100;
	while(++res){
		memset(vis, 0, sizeof(vis));
		int cnt = 0;
		//Step 1: Add 1
		for(int i = 0; i < m;i++){
			for(int j = 0; j < n;j++){
				matrix[i][j]++;
				if(matrix[i][j] >= 10){
					vis[i][j] = 1; //?
					q.push({i, j});
				}
			}
		}
		
		//cout << "test line 1\n";

		while(!q.empty()){
			int curx = q.front().first, cury = q.front().second;
			q.pop();
			/* if(vis[curx][cury]) */
			/* 	continue; */
			/* vis[curx][cury] = 1; */
			cnt++;
			for(int i = 0; i < 8; i++){
				int x = curx + dir[i][0], y = cury + dir[i][1];
				//flashed point or inavailible point
				if(x < 0 || y < 0 || x >= m || y >= n || vis[x][y])// || matrix[x][y] < 10)
					continue;
				//Adjacent influence
				matrix[x][y]++;
				if(matrix[x][y] < 10)
					continue;
				q.push({x, y});
				vis[x][y] = 1;
			}
			//Clear flashing point.
			matrix[curx][cury] = 0;
		}


		/* Test Printout
		if(loop > 90 || loop % 10 == 0){
			//Test Printout
			for(int i = 0; i < m; i++){
				for(int j = 0; j < n; j++)
					cout << matrix[i][j];
				cout << endl;
			}
		}
		*/
		if(cnt == m * n)
			break;
	}

	



	cout << "Part I answer:\n";//>
	cout << res << '\n';//>>

	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}
