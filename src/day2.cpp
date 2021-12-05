#include<iostream>
int main(){
	std::string s;
	int x, totalX = 0, totalY = 0;
	int aim = 0, y2 = 0;
	while(std::cin>>s>>x){
		//Part 1:
		if(s == "forward"){
			totalX += x;
			y2 += aim * x;
		}else if(s == "down"){
			totalY += x;
			aim += x;
		}else{
			totalY -= x;
			aim -= x;
		}
		
		//Part 2:
	}
	
	std::cout<<"Part One's answer is: "<< totalX * totalY << std::endl;
	std::cout<<"Part Two's answer is: "<< totalX * y2 << std::endl;
	return 0;
}
