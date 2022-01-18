#include<string>
#include<vector>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<iostream>
#include<bitset>
int main(){
	int ans;
	std::string bit_string;
	std::vector<std::string> vec;
	std::unordered_map<int, int> mask;
	int n, cnt = 0;
	std::vector<int> nums;
	while(std::cin>>bit_string){
		vec.push_back(bit_string);
	}


	std::unordered_set<int> L, R, NextS;
	for(int i = 0; i < 1000; i++)
		L.insert(i);

	for(int j = 0; j < 12; j++){
		for(auto index: L){
			if(vec[index][j]!='0'){
				R.insert(index);
			}
		}

		for(auto index: R){
			L.erase(index);
		}

		//Swap if L.size <= R.size
		if(L.size() <= R.size())
			swap(L, R);

		if(j == 0)
			swap(NextS, R);

		R.clear();
	}
	for(auto index: L){
		std::cout<<"O2 val in binary:\n";
		std::cout<<vec[index]<<'\n';
	}

	//std::cout<<"Part Two's answer is: "<< ans2 << std::endl;
	//TO-DO: Use Huffman Tree to calculate the res
	return 0;
}
