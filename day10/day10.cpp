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
	mp[')'] = 3; mp[']'] = 57; mp['}'] = 1197; mp['>'] = 25137;

	while(getline(cin, cinstring)){
		stringstream strcin(cinstring);
		int slen = cinstring.length();
		char x;

		stack<char> s;
		while(strcin >> x){
			if(x == '(' || x == '{' || x == '<' || x == '[')
				s.push(x);
			else{
				if(s.empty() || 
					(x == ')' && s.top() + 1 != x) ||
					(x != ')' && s.top() + 2 != x)){
					res += mp[x];
					break;
				}
				s.pop();
			}
		}
		
	}
	


	cout << "Part I answer:\n";//>
	cout << res << '\n';//>>

	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}
