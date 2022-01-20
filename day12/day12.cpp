#include<unordered_set>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<string>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
#include<cstdio>
#include<ctype.h>
using namespace std;

void dfs(int n, unordered_set<int> &small_caves, int cur);

int matrix[25][25];
int vis[25];
int endpoint, result;
int main(){
	//Close Sync with stdio, Faster cin
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	char s[7],t[7];
	int res = 0;
	unordered_map<string, int> Map;
	unordered_set<int> small_caves;
	int cnt = 0;
	result = 0;

	memset(vis, 0, sizeof(vis));
	memset(matrix, 0, sizeof(matrix));
	while(scanf("%99[^-]-%s", s, t )!=EOF){
		getchar();
		string a(s), b(t);
		/* printf("Test:%s, %s\n", a.c_str(), b.c_str()); */
		if(!Map.count(a))
			Map[a] = ++cnt;
		if(!Map.count(b))
			Map[b] = ++cnt;
		matrix[Map[a]][Map[b]] = 1;
		matrix[Map[b]][Map[a]] = 1;
		if(islower(a[0]))
			small_caves.insert(Map[a]);
		if(islower(b[0]))
			small_caves.insert(Map[b]);
	}


	//Test Input for graph
	/* for(auto kv: Map) */
	/* 	printf("%s: %d, ", kv.first.c_str(), kv.second); */
	/* puts(""); */
	/* for(int i = 1; i <= cnt; i++){ */
	/* 	for(int j = 1; j <= cnt; j++) */
	/* 		printf("%d ", matrix[i][j]); */
	/* 	puts(""); */
	/* } */

	int start = Map["start"];
	endpoint = Map["end"];
	/* small_caves.erase(start); */
	/* vis[start] = 1; */
	/* printf("dfs(%d)\n", start); */
	dfs(cnt, small_caves, start);

	cout << "Part I answer:\n";//>
	cout << result << '\n';//>>

	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}

//GLOBAL VARIABLE: vis, graph, n, small
void dfs(int n, unordered_set<int> &small_caves, int cur){
	/* printf("%d -> ", cur); */
	if(cur == endpoint){
		/* puts("--------"); */
		result++;
		return;
	}
	//set State:
	if(small_caves.count(cur)){
		vis[cur] = 1;
	}

	//DFS
	for(int i = 1; i <= n; i++){
		if(matrix[cur][i] && !vis[i]){
			/* printf("dfs(%d -> %d)\n", cur, i); */
			dfs(n, small_caves, i);
		}
	}
	
	//reset State:
	if(small_caves.count(cur)){
		vis[cur] = 0;
	}

}
