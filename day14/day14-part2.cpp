#include <cstdint>
#include<unordered_set>
#include<set>
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

int main(){
	//Close Sync with stdio, Faster cin
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int res = 0;
	string init_string, pattern;
	unordered_map<int, int> trans_map;
	unordered_map<string, int> dict;
	vector<vector<int>> graph(26 * 26 + 20, vector<int>(2,0));

	/* for(int i = 0; i < 26; i++) */
	/* 	for(int j = 0; j < 26; j++){ */
	/* 		string s; */
	/* 		s.push_back('A' + i); */
	/* 		s.push_back('A' + j); */
	/* 		dict[s] = i * 26 + j; */
	/* 	} */

	auto func_hash = [](const char x, const char y){
		return (x - 'A') * 26 + y - 'A';
	};

	//Handling Input
	cin >> init_string;
	string bak;
	getline(cin, bak);
	getline(cin, bak);
	while(getline(cin, pattern)){
		stringstream patternin(pattern);
		string S, arrow, t;
		patternin >> S >> arrow >> t;
		/* cout << S << t << endl; */
		int hashed = func_hash(S[0], S[1]);
		int hashed2 = (S[0] - 'A' ) * 26 + S[1] - 'A';
		if(hashed != hashed2)
			cout << "Errrrror hash function\n";
		if(trans_map.count(hashed)){
			cout << S << "Hashed collision.\n";
		}
		graph[hashed][0] = func_hash(S[0], t[0]);
		graph[hashed][1] = func_hash(t[0], S[1]);
	}

	
	auto testFoo = [&](){
	};

	vector<long long> dp(26 * 26, 0);
	string str = init_string;int slen = str.length();
	for(int i = 1; i < slen; i++){
		int hash_val = func_hash(str[i - 1], str[i]);
		dp[hash_val]++; 
	}

	for(int loop = 0; loop < 40; loop++){
		vector<long long> Tmp(26 * 26, 0);
		for(int i = 0; i < 26 * 26; i++){
			//Calc the next count to Tmp vector;
			if(dp[i]){
				Tmp[graph[i][0]] += dp[i];
				Tmp[graph[i][1]] += dp[i];
			}
		}
		for(int i = 0; i < 26 * 26; i++)
			dp[i] = Tmp[i];
	}
	/* for(int i = 0; i < 26 * 26; i++){ */
	/* 	if(dp[i]){ */
	/* 		printf("count:%c%c->%lld\n", i / 26 + 'A', i % 26 + 'A', dp[i]); */
	/* 	} */
	/* } */

	vector<long long> stats(26, 0);
	/* for(auto ch: str){ */
	/* 	stats[ch - 'A']++; */
	/* } */
	for(int i = 0; i < 26 * 26; i++){
		if(dp[i]){
			stats[i % 26] += dp[i];
			stats[i / 26] += dp[i];
		}
	}

	/* for(auto st: stats) */
	/* 	cout << st << '\t'; */
	/* cout << endl; */
	long long mce = 0, lce = INT64_MAX;
	for(int i = 0; i < 26; i++){
		mce = max(mce, stats[i]);
		if(stats[i])
			lce = min(lce, stats[i]);
	}

	/* //8:42 30 */
	cout << "Part II answer:\n" <<  (mce + 1LL) / 2LL - (lce + 1LL) / 2LL << endl;

	return 0;
}

