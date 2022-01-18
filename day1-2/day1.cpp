#include<iostream>
int main(){
	int prev = -1, cur, cnt = 0;
	int a = -1, b = -1, c = -1, ans2 = 0;
	while(std::cin>>cur){
		//Part 1:
		if(prev != -1 && cur > prev)
			cnt++;
		prev = cur;
		
		//Part 2:
		if(a != -1 && cur > a)
			ans2++;
		a = b;b = c; c = cur;
	}
	std::cout<<"Part One's answer is: "<< cnt << std::endl;
	std::cout<<"Part Two's answer is: "<< ans2 << std::endl;
	return 0;
}
