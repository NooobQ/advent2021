#include<iostream>
#include<bitset>

using namespace std;
int idx = 0;
string hexStr;
int parse();
int main(){
	cin >> hexStr;
	int versionSum = 0;
	int res =parse();
	cout << "Part I answer:\n" << res << endl;
	return 0;
}
int get(int n){
	string num = hexStr.substr(idx / 4, (idx % 4 != 0) + (n + 3) / 4);
	int blen = num.length() * 4;
	int res = stoi(num, nullptr, 16);
	res = (res >> (blen - n - (idx % 4))) % (1 << n);
	/* cout << num << endl; */
	/* cout << "blen :" << blen << '\t' << "idx % 4:" << idx % 4 << '\n'; */
	/* cout << "GET " << n << ":\t" << res << endl; */
	idx += n;
	return res;
}
int parse(){
	pair<int, int> ans;
	int val = 0;
	int version = get(3);
	int Typeid = get(3);
	/* cout << "version: " << version << " | type: " << Typeid << endl; */
	if(Typeid == 4){
		int lit;
		while((lit = get(5)) & 16){
			val = 8 * val + lit % 16;
		}
		val = 8 * val + lit % 16;
	}
	else{
		//Sub-packet parse:
		/* version += get(3); */
		/* Typeid = get(3); */
		int I = get(1);
		int len;
		if(I){
			len = get(11);
			for(int i = 0; i < len; i++){
				version += parse();
			}
		}else{
			len = get(15);
			int cur_idx = idx;
			while(idx < cur_idx + len){
				version +=parse();
			}
		}
	}
	return version;
}
