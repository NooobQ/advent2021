#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main(){
	int index;
	long long laternfish[10];
	for(int i = 0; i < 10; i++)
		laternfish[i] = 0;
	while(scanf("%d",&index)!=EOF){
		laternfish[index]++;
		getchar();
	}
	
	vector<long long> sum;
	for(int i = 0; i < 300; i++){
		long long res = 0;
		for(int j = 0; j < 9; j++)
			res += laternfish[j];
		sum.push_back(res);

		long long zero = laternfish[0];
		laternfish[0] = laternfish[1];
		laternfish[1] = laternfish[2];
		laternfish[2] = laternfish[3];
		laternfish[3] = laternfish[4];
		laternfish[4] = laternfish[5];
		laternfish[5] = laternfish[6];
		laternfish[6] = zero + laternfish[7];
		laternfish[7] = laternfish[8];
		laternfish[8] = zero;
	}
	cout<<"Part I answer :\n"<<sum[80]<<'\n';//>>>>>>
	cout<<"Part II answer:\n"<<sum[256]<<'\n';//>>>
}
