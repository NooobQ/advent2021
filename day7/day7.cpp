/* Using Binary Search and compute including precision ±1  */
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int main(){
	int num;
	int crabs[1005];
	int n = 0;
	while(scanf("%d", &num)!=EOF){
		crabs[n++] = num;
		getchar();
	}

	/* static_assert(n!=1000, "scanf get wrong number.") */
	sort(crabs, crabs + n);

	/* for(int i = 0; i < n; i++){ */
	/* 	cout<<crabs[i]<<'\t'; */
	/* } */ 
	/* cout<<endl;//> */

	
	int l = crabs[0], r = crabs[n - 1] + 1;
	auto calc = [&](const int x){
		int res = 0;
		for(int i = 0; i < n; i++)
			res += abs(crabs[i] - x);
		return res;
	};
	//cout<<calc(1)<<'\t'<<calc(2)<<'\t'<<calc(4)<<endl;
	while(l < r){
		int mid = (l + r) / 2;
		int l_fuel = calc(l), r_fuel = calc(r);
		if(l_fuel <= r_fuel)
			r = mid;
		else {
			l = mid + 1;
		}
		/* cout<<l_fuel<<'\t'<<r_fuel<<endl;//>>>> */
		/* cout<<l<<'\t'<<r<<endl;//>>> */
	}
	cout<<"Part I answer:\n";
	cout<<min(calc(l-1),calc(l))<<'\n';
}
