#include<string>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<bitset>
int main(){
	int part1_ans, part2_ans;
	std::string bit_string;
	std::unordered_map<int, int> mask;
	int n, cnt = 0;
	std::vector<int> nums;
	while(std::cin>>bit_string){
		cnt++;
		n = bit_string.length();
		//bitset<n> bs;
		for(int i = 0; i < n; i++){
			if(bit_string[i] == '1')
				mask[i]++;
		}
		
		//Part 2:
		std::bitset<64> temp(bit_string);
		nums.push_back(temp.to_ulong());
		
	}
	//Part 1:
	std::string gamma, esp;
	for(int i = 0; i < n; i++){
		if(mask[i] > cnt / 2){
			esp += "0";
			gamma += "1";
		}
		else{
			esp += "1";
			gamma += "0";
		}
	}
	
	std::bitset<64> Gamma(gamma), Esp(esp);
	std::cout<<"Part One's answer is: "<<Gamma.to_ulong() * Esp.to_ulong()<<'\n';

	//std::cout<<"Part Two's answer is: "<< ans2 << std::endl;
	//TO-DO: Use Huffman Tree to calculate the res
	return 0;
}
