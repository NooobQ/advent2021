#include <iostream>
#include <vector>

using namespace std;

vector<long long> multi_factors(10, 0);
void dfs(int a_pos, int b_pos, int a_sco, int b_sco, int turn, vector<long long> &wina, vector<long long> &winb, int depth, long long multi){
	if(a_sco >= 21){
		/* cout << depth <<endl; */
		wina[depth] += multi;
		return;
	}
	if(b_sco >= 21){
		/* cout << depth <<endl; */
		winb[depth] += multi;
		return;
	}
	if(turn){
		for(int i = 3; i < 10; i++){
			int tmp_pos = (a_pos + i) % 10;
			if(!tmp_pos)
				tmp_pos = 10;
			dfs(tmp_pos, b_pos, a_sco + tmp_pos, b_sco, !turn, wina, winb, depth + 1, multi * multi_factors[i]);
		}
/* 		for(int i = 0; i < 3; i++){ */
/* 			a_pos = (a_pos + 1) % 10; */
/* 			if(!a_pos) */
/* 				a_pos = 10; */
/* 			dfs(a_pos, b_pos, a_sco + a_pos, b_sco, !turn, wina, winb, depth + 1, multi); */
/* 		} */
	}else{
		for(int i = 3; i < 10; i++){
			int tmp_pos = (b_pos + i) % 10;
			if(!tmp_pos)
				tmp_pos = 10;
			dfs(a_pos, tmp_pos, a_sco, b_sco + tmp_pos, !turn, wina, winb, depth + 1, multi * multi_factors[i]);
		}
	}
}
int main(){
	int posa, posb;
	cin >> posa >> posb;
	long long wina = 0, winb = 0;
	for(int i = 1; i <= 3; i++){
		for(int j = 1; j <= 3; j++)
			for(int k = 1; k <= 3; k++)
				multi_factors[i + j + k]++;
	}
	/* for(auto foo: multi_factors) */
	/* 	cout << foo << '\t'; */
	/* cout << endl; */
	vector<long long> vecA(50, 0), vecB(50, 0);
	dfs(posa, posb, 0, 0, 1, vecA, vecB, 0, 1);
	long long res = 0;
	for(auto foo:vecA){
		/* cout << foo << endl; */
		res += foo;
	}
	long long resB = 0;
	for(auto foo:vecB){
		resB += foo;
	}
	cout << "Part II Result: " <<  endl;
	cout << max(res, resB) << endl;
}
