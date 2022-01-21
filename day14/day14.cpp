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

	//Handling Input
	cin >> init_string;
	string bak;
	getline(cin, bak);
	while(getline(cin, pattern)){
		stringstream patternin(pattern);
		string S, arrow, T;
		patternin >> S >> arrow >> T;
		/* cout << S << T << endl; */
		int hashed = (S[0] - 'A' ) * 100 + S[1] - 'A';
		if(trans_map.count(hashed)){
			cout << S << "Hashed collision.\n";
		}
		trans_map[hashed] = T[0] - 'A';
	}
	
	auto testFoo = [&](){
	};

	string str = init_string;
	for(int i = 0; i < 10; i++){
		int slen = str.length();
		string x;
		//Transform;
		for(int idx = 1; idx < slen; idx++){
			x += str[idx - 1];
			int hashed = (str[idx - 1] - 'A') * 100 + str[idx] - 'A';
			x += ('A' + trans_map[hashed]);
		}
		x += str[slen - 1];
		//Get New Value;
		str = x;
		//cout << str << endl;
	}

	vector<long long> stats(26, 0);
	for(auto ch: str){
		stats[ch - 'A']++;
	}
	/* for(auto st: stats) */
	/* 	cout << st << '\t'; */
	/* cout << endl; */
	long long mce = 0, lce = 1e9;
	for(int i = 0; i < 26; i++){
		mce = max(mce, stats[i]);
		if(stats[i])
			lce = min(lce, stats[i]);
	}

	//8:42 30
	cout << "Part I answer:\n" <<  mce - lce << endl;

	return 0;
}

