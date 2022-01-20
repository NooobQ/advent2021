#include<unordered_set>
#include<iostream>
#include<vector>
#include<sstream>
#include<string>
using namespace std;


int main(){
	//Close Sync with stdio, Faster cin
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string pattern[10],digit[4];
	int unique_dig[] = {2, 3, 4, 7};
	auto check = [&unique_dig](const string &str){
		int sz = str.length();
		for(auto cnt:unique_dig){
			if(cnt == sz)
				return 1;
		}
		return 0;
	};
	
	int res = 0;
	for(int loop = 0; loop < 200; loop++){
		for(int i = 0; i < 10; i++)
			cin>>pattern[i];
		char x;
		cin>>x;
		for(int i = 0; i < 4; i++){
			cin>>digit[i];
			res += check(digit[i]);
		}
	}

	cout<<"Part I answer:\n";//>
	cout<<res<<'\n';//>>

	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}
