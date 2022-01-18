#include<iostream>
#include<cstdio>
#include<cstring>
#include<unordered_set>
using namespace std;
int main(){
	int n = 500;
	int matrix[1050][1050];
	int res =0;
	auto hashFunc = [](const pair<int, int> &lhs){
		return 1000*lhs.first + lhs.second;
	};
	unordered_set<int> overlapPoints;

	memset(matrix, 0, sizeof(matrix));
	for(int i = 0; i < n; i++){
		int x1, y1, x2, y2;

		//Input Format
		scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
		//Ignore non-horizontal or vertical-line
		if(x1 != x2 && y1 != y2)
			continue;
		
		if(x1 > x2 || y1 > y2){
			swap(x1, x2);
			swap(y1, y2);
		}
		
		if(x1 == x2){
			for(int i = y1; i <= y2; i++){
				if(matrix[x1][i] && !overlapPoints.count(1000 * x1 + i)){
					overlapPoints.insert(1000 * x1 + i);
					//cout<<x1<<'\t'<<i<<'\n';
				}
				else {
					matrix[x1][i] = 1;
				}
			}
		}
		if(y1 == y2){
			for(int i = x1; i <= x2; i++){
				if(matrix[i][y1] && !overlapPoints.count(1000 * i + y1))
					overlapPoints.insert(1000 * i + y1);
				else {
					matrix[i][y1] = 1;
				}
			}
		}
	}
	
	cout<<"Part I answer:\n"; //>
	cout<<overlapPoints.size()<<'\n';


}
