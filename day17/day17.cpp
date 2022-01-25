#include <iostream>
#include <cstdio>
#include <set>
#include <vector>

using namespace std;
int main(){
	int x_min, x_max, y_min, y_max;
	cin >> x_min >> x_max >> y_min >> y_max;
	auto test = [x_min, x_max, y_min, y_max](int vx, int vy){
		int x = 0, y = 0;
		while(1){
			x += vx;
			y += vy;
			if(vx)
				vx--;
			vy--;
			if(x_min <= x && x <= x_max
					&& y_min <=y && y <= y_max){
				return true;
			}
			if(y < y_min)
				break;
		}
		return false;
	};
	int cnt = 0;
	set<pair<int, int>> allPairs;
	for(int i = 0; i <= x_max; i++){
		for(int j = y_min; j < -y_min;j++){
			if(test(i, j)){
				allPairs.insert({i, j});
				cnt++;
			}
		}
	}
	for(auto p:allPairs){
		printf("(%d, %d)\n", p.first, p.second);	
	}
}
