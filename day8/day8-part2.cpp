#include<unordered_set>
#include<iostream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<string>
#include<map>
using namespace std;


int main(){
	//Close Sync with stdio, Faster cin
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string pattern[10],digit[4];
	int unique_dig[] = {2, 3, 4, 7};
	map<int, int> unique_map;

	auto parse_pattern =[&](){
		unordered_set<int> five_dig, six_dig;
		int index[10];
		unordered_set<char> charset;
		unique_map.clear();
		for(int i = 0; i < 10; i++){
			sort(pattern[i].begin(), pattern[i].end());
			if(pattern[i].length() == 2){
				index[1] = i;
				unique_map[i] = 1;
				charset.insert(pattern[i][0]);
				charset.insert(pattern[i][1]);
			}
			if(pattern[i].length() == 3){
				index[7] = i; 
				unique_map[i] = 7;
			}
			if(pattern[i].length() == 4){
				unique_map[i] = 4;
				index[4] = i;
			}
			if(pattern[i].length() == 5)
				five_dig.insert(i);
			if(pattern[i].length() == 6)
				six_dig.insert(i);
			if(pattern[i].length() == 7){
				index[8] = i;
				unique_map[i] = 8;
			}
		}
		
		//Below can be abstract to function: pattern_recogni(set<char> Pattern_charset, set<string> M_strings, int x)
		//Compute the digit '6' & digit '3' using '1'
		for(auto idx: six_dig){
			int cnt = 0;
			for(auto ch: pattern[idx]){
				cnt += charset.count(ch);
			}
			if(cnt == 1){
				index[6] = idx;
				unique_map[idx] = 6;
			}
		}
		
		for(auto idx: five_dig){
			int cnt = 0;
			for(auto ch: pattern[idx]){
				cnt += charset.count(ch);
			}
			if(cnt == 2){
				index[3] = idx;
				unique_map[idx] = 3;
			}
		}
		//compute digit '2' & '5' using '6'
		charset.clear();
		for(auto ch: pattern[index[6]])
			charset.insert(ch);
		for(auto idx: five_dig){
			int cnt = 0;
			for(auto ch: pattern[idx]){
				cnt += charset.count(ch);
			}
			if(cnt == 5){
				index[5] = idx;
				unique_map[idx] = 5;
			}else if(!unique_map[idx]){
				index[2] = idx;
				unique_map[idx] = 2;
			}
		}
		
		//use '3' to compute '9'
		charset.clear();
		for(auto ch: pattern[index[3]])
			charset.insert(ch);
		for(auto idx: six_dig){
			int cnt = 0;
			for(auto ch: pattern[idx]){
				cnt += charset.count(ch);
			}
			if(cnt == 5){
				index[9] = idx;
				unique_map[idx] = 9;
			}
		}

		//Below for testing.
		/* for(int i = 0; i < 10; i++) */
		/* 	cout<<unique_map[i]<<'\t';//>//>("%d, ", unique_map[i]); */
		/* cout<<endl;//> */
	};

	string cinstring;
	int res = 0;
	while(getline(cin, cinstring)){
		stringstream strcin(cinstring);
		for(int i = 0; i < 10; i++)
			strcin>>pattern[i];
		parse_pattern();

		//Reading "|"
		char x;
		strcin>>x;

		int dignum = 0;
		for(int i = 0; i < 4; i++){
			strcin>>digit[i];
			sort(digit[i].begin(), digit[i].end());
			for(int j = 0; j < 10; j++){
				//compare string to pattern and add map to val;
				if(digit[i] == pattern[j])
					dignum = 10 * dignum + unique_map[j];
			}
			//cout<<digit[i]<<'\t'<<dignum<<endl;//>>>>
		}
		res +=dignum;
	}

	cout<<"Part II answer:\n";//>
	cout<<res<<'\n';//>>

	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}
