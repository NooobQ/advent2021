#include<iostream>
#include<vector>

using namespace std;

int main(){
	string cinstring;
	vector<int> dp;
	while(cin >> cinstring){
		if(dp.empty()){
			for(auto ch: cinstring){
				dp.push_back(ch - '0');
			}
			dp[0] = 0;
			for(int i = 1; i < dp.size(); i++)
				dp[i] += dp[i - 1];
		}
		else{
			//scrolling vector
			dp[0] += cinstring[0] - '0';
			for(int i = 1; i < dp.size(); i++){
				dp[i] = min(dp[i], dp[i - 1]) + cinstring[i] - '0';
			}
		}
		/* for(auto num: dp) */
		/* 	cout << num << ' '; */
		/* cout << endl; */
	}
	cout << "Part I answer:\n" << dp.back() << endl;
	return 0;
}
