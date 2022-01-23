#include <cstdint>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main(){
	string cinstring;
	vector<vector<int>> original_matrix(100);
	vector<vector<int>> map(500, vector<int>(500,0));
	vector<vector<int>> dis(500, vector<int>(500, INT32_MAX));
	vector<vector<int>> vis(500, vector<int>(500,0));
	auto cmp = [&](const pair<int, int> a, const pair<int, int> b){
		return dis[a.first][a.second] > dis[b.first][b.second];
	};
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
	vector<int> dp;
	int n = 0;
	while(cin >> cinstring){
		for(auto ch: cinstring){
			original_matrix[n].push_back(ch - '0');
		}
		n++;
	}
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			for(int x = 0; x < n; x++){
				for(int y = 0; y < n; y++){
					int riskLevel = (original_matrix[x][y] + i + j) % 9;
					if(!riskLevel)
						riskLevel = 9;
					map[x + i * n][y + j * n] = riskLevel;
				}
			}
		}
	}
	/* for(int i = 0; i < 5 * n; i++){ */
	/* 	for(int j = 0; j < 5 * n; j++) */
	/* 		cout << map[i][j]; */
	/* 	cout << endl; */
	/* } */

	int dir[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

	//change cmp -> pair<int,int> ---dis[int]
	dis[0][0] = 0;
	q.push({0, 0});
	while(!q.empty()){
		int curx = q.top().first, cury = q.top().second;
		q.pop();
		if(vis[curx][cury])
			continue;
		vis[curx][cury] = true;
		for(int i = 0; i < 4; i++){
			int x = curx + dir[i][0], y = cury + dir[i][1];
			if(x < 0 || y < 0 || x >= 5 * n || y >= 5 * n ){
				continue;
			}
			dis[x][y] = min(dis[curx][cury] + map[x][y], dis[x][y]);
			q.push({x, y});
		}
	}
	/* for(int i = 0; i < n; i++){ */
	/* 	for(int j = 0; j < n; j++) */
	/* 		cout << dis[i][j] << ' '; */
	/* 	cout << endl; */
	/* } */
	cout << "Part II answer:" << endl;
	cout << dis[5 * n - 1][5 * n - 1] << endl;
	
	//LINE 0
	/* if(dp.empty()){ */
	/* 	dp.push_back(original_matrix[0][0]); */
	/* 	/1* cout << original_matrix[0][0]; *1/ */
	/* 	for(int i = 1; i < 5 * n; i++){ */
	/* 		int gridLevel = (original_matrix[0][i % n] + i / n) % 9; */
	/* 		if(!gridLevel) */
	/* 			gridLevel += 9; */
	/* 		/1* cout << gridLevel; *1/ */
	/* 		dp.push_back(gridLevel + dp[i - 1]); */
	/* 	} */
	/* } */

	/* for(int i = 1; i < 5 * n; i++){ */
	/* 	int riskLevel = (original_matrix[i % n][0] + i / n) % 9; */
	/* 	if(!riskLevel) */
	/* 		riskLevel += 9; */
	/* 	/1* cout << riskLevel; *1/ */
	/* 	dp[0] += riskLevel; */
	/* 	for(int j = 1; j < 5 * n; j++){ */
	/* 		riskLevel = (original_matrix[i % n][j % n] + (i / n) + (j / n)) %9; */
	/* 		if(!riskLevel) */
	/* 			riskLevel += 9; */
	/* 		/1* cout << riskLevel; *1/ */
	/* 		dp[j] = min(dp[j - 1], dp[j]) + riskLevel; */
	/* 	} */
	/* 	/1* cout << endl; *1/ */
	/* 	cout << dp.back() << '\n'; */
	/* } */
	/* cout << "---- Risk Level above ----\n"; */
	/* for(auto num: dp) */
	/* 	cout << num << ' '; */
	/* cout << endl; */
	/* cout << "Part I answer:\n" << dp.back() - original_matrix[0][0] << endl; */

	return 0;
}
