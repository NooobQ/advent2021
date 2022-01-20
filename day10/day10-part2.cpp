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
	map<char, int> mp;
	mp['('] = 1; mp['['] = 2; mp['{'] = 3; mp['<'] = 4;
	vector<long long> arr;

	while(getline(cin, cinstring)){
		stringstream strcin(cinstring);
		int slen = cinstring.length();
		char x;
		int flag =0;

		stack<char> s;
		while(strcin >> x){
			if(x == '(' || x == '{' || x == '<' || x == '[')
				s.push(x);
			else{
				//Handle corrupted bracket
				if(s.empty() || 
					(x == ')' && s.top() + 1 != x) ||
					(x != ')' && s.top() + 2 != x)){
					flag = 1;
					break;
				}
				s.pop();
			}
		}

		if(!flag){
			long long score = 0;
			while(!s.empty()){
				score = score * 5LL + mp[s.top()] * 1LL;
				s.pop();
			}
			arr.push_back(score);
		}
	}

	sort(arr.begin(), arr.end());
	/* for(auto foo: arr) */
	/* 	cout << foo << endl; */
	/* cout << arr.size() <<endl; */

	cout << "Part II answer:\n";//>
	cout << arr[arr.size() / 2 ] << '\n';//>>

	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}
