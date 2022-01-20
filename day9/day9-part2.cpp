#include<unordered_set>
#include<iostream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<string>
#include<cstring>
#include<map>
#include<queue>
using namespace std;

int main(){
	//Close Sync with stdio, Faster cin
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int matrix[150][150];
	int vis[150][150];
	string cinstring;
	int res = 0;
	int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int m = 0, n = 0;
	queue<pair<int, int>> q;
	priority_queue<int, vector<int>, greater<int>> pq;

	while(getline(cin, cinstring)){
		//stringstream strcin(cinstring);
		int slen = cinstring.length();
		n = cinstring.length();
		for(int i = 0; i < slen; i++){
			matrix[m][i] = cinstring[i] - '0';
		}
		m++;
	}
	
	memset(vis, 0, sizeof(vis));
	for(int _i = 0; _i < m; _i++){
		for(int _j = 0; _j < n; _j++){
			if(matrix[_i][_j]!=9)
				q.push(make_pair(_i, _j));
			int area = 0;
			while(!q.empty()){
				int curx = q.front().first, cury = q.front().second;
				q.pop();
				if(vis[curx][cury])
					continue;
				vis[curx][cury] = 1;
				area++;

				for(int i = 0; i < 4; i++){
					int x = curx + dir[i][0], y = cury + dir[i][1];
					if(x < 0 || y < 0 || x >= m || y >= n || matrix[x][y] == 9)
						continue;
					q.push(make_pair(x, y));
				}
			}
			if(area)
				pq.push(area);
			while(pq.size() > 3)
				pq.pop();
		}
	}

	res = 1;
	while(!pq.empty()){
		res *= pq.top();
		pq.pop();
	}

	cout << "Part II answer:\n";//>
	cout << res << '\n';//>>

	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}
