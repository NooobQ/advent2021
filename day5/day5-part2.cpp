#include<iostream>
#include<cstdio>
#include<cstring>
#include<unordered_set>
using namespace std;
int checkDiagonal(int x1, int y1, int x2, int y2);
int main(){
	int n = 500;
	int matrix[1050][1050];
	int res =0;
	unordered_set<int> overlapPoints;

	memset(matrix, 0, sizeof(matrix));
	for(int i = 0; i < n; i++){
		int x1, y1, x2, y2;

		//Input Format
		scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
		//Ignore non-horizontal or vertical-line
		int checkFlag = checkDiagonal(x1, y1, x2, y2);
		if(x1 != x2 && y1 != y2 && !checkFlag)
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
		if(checkFlag){
			int xdir = (x2-x1)/abs(x2-x1);
			int ydir = (y2-y1)/abs(y2-y1);
			//cout<<xdir<<'\t'<<ydir<<'\n';//>>>
			while(x1 != x2 + xdir){
				//cout<<x1<<'\t'<<y1<<'\n';//>>>

				if(matrix[x1][y1] && !overlapPoints.count(1000 * x1 + y1))
					overlapPoints.insert(1000 * x1 + y1);
				else {
					matrix[x1][y1] = 1;
				}
				x1 += xdir;
				y1 += ydir;
			}
		}
	}
	
	cout<<"Part II answer:\n"; //>
	cout<<overlapPoints.size()<<'\n';

}

inline int checkDiagonal(int x1, int y1, int x2, int y2){
	if(abs(x1 - y1) == abs(x2 - y2))
		return true;
	if(abs(x1 - y2) == abs(x2 - y1))
		return true;
	return false;
}
