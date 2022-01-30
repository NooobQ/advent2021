#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

void transform(vector<string> &mp, vector<string> &trans_mp, vector<int> &zoom, char &flipSym, int m, int n);
int main(){
	vector<int> zoom;
	vector<string> mp;
	string s;
	int m = 0, n = 0, slen;
	cin >> s;
	slen = s.length();
	for(int i = 0; i < slen; i++)
	{
		zoom.push_back(s[i] == '#');
	}
	
	while(cin >> s){
		n = s.length();
		mp.push_back(s);
		m++;
	}
	
	vector<string> trans_mp;
	char flipSym = '.';
	auto calc = [&](int x, int y){
		int idx = 0;
		for(int i = -1; i < 2; i++){
			for(int j = -1; j < 2; j++){
				char tmp = (x + i < 1 || y + j < 1 || x + i - 1 >= m || y + j - 1 >= n  ? flipSym: mp[x + i - 1][y + j - 1]);
				idx = (idx << 1) + (tmp == '#');
			}
		}
		/* cout << idx << '\t'; */
		return zoom[idx];
	};

	int loop = 50, flag = 0;
	while(loop--){
		transform(mp, trans_mp, zoom, flipSym, m, n);
		mp.clear();
		for(auto foo: trans_mp)
			mp.push_back(foo);
		m += 2;n += 2;
		if(zoom[0])
			flipSym = flipSym == '.'? '#': '.';

		trans_mp.clear();
	}
	/* for(int i = 0; i < m + 2; i++){ */
	/* 	string str; */
	/* 	for(int j = 0; j < n + 2; j++){ */
	/* 		str.push_back(calc(i, j)? '#': '.'); */
	/* 	} */
	/* 	trans_mp.push_back(str); */
	/* } */


	int cnt = 0;
	for(auto foo: mp){
		for(auto ch: foo)
			if(ch == '#')
				cnt++;
		/* cout << foo << endl; */
	}
	cout << "Part II answer:" << endl;
	cout << cnt << endl;
	// 6532 X
	// 5776 X higher
}
void transform(vector<string> &mp, vector<string> &trans_mp, vector<int> &zoom, char &flipSym, int m, int n){
	auto calc = [&](int x, int y){
		int idx = 0;
		for(int i = -1; i < 2; i++){
			for(int j = -1; j < 2; j++){
				char tmp = (x + i < 1 || y + j < 1 || x + i - 1 >= m || y + j - 1 >= n  ? flipSym: mp[x + i - 1][y + j - 1]);
				idx = (idx << 1) + (tmp == '#');
			}
		}
		/* cout << idx << '\t'; */
		return zoom[idx];
	};

	for(int i = 0; i < m + 2; i++){
		string str;
		for(int j = 0; j < n + 2; j++){
			str.push_back(calc(i, j)? '#': '.');
		}
		trans_mp.push_back(str);
	}

}
