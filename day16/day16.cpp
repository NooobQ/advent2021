#include <cstdint>
#include<iostream>
#include<vector>

using namespace std;
int idx = 0;
string hexStr;
pair<int, long long> parse();
long long calc(int id, vector<long long> &nums);
int main(){
	cin >> hexStr;
	int versionSum = 0;
	auto res =parse();
	cout << "Part I answer:\n" << res.first << endl;
	cout << "Part II answer:\n" << res.second << endl;
	return 0;
}
int get(int n){
	string num = hexStr.substr(idx / 4, (idx % 4 != 0) + (n + 3) / 4);
	int blen = num.length() * 4;
	int res = stoi(num, nullptr, 16);
	res = (res >> (blen - n - (idx % 4))) % (1 << n);
	/* cout << num << endl; */
	/* cout << "blen :" << blen << '\t' << "idx % 4:" << idx % 4 << '\n'; */
	/* cout << "GET " << n << ":\t" << res << endl; */
	idx += n;
	return res;
}
pair<int, long long> parse(){
	pair<int, long long> ans;
	long long val = 0;
	int version = get(3);
	int Typeid = get(3);
	/* cout << "version: " << version << " | type: " << Typeid << endl; */
	if(Typeid == 4){
		long long lit;
		while((lit = get(5)) & 16){
			val =  (val << 4) + lit % 16 * 1LL;
		}
		val = (val << 4) + lit % 16 * 1LL;
	}
	else{
		//Sub-packet parse:
		int I = get(1);
		int len;
		vector<long long> packet;
		if(I){
			len = get(11);
			for(int i = 0; i < len; i++){
				auto p = parse();
				version += p.first;
				packet.push_back(p.second);
			}
			val = calc(Typeid, packet);
		}else{
			len = get(15);
			int cur_idx = idx;
			while(idx < cur_idx + len){
				auto p = parse();
				version += p.first;
				packet.push_back(p.second);
			}
			val = calc(Typeid, packet);
		}
	}
	if(val < 0)
		cout << val << endl;
	return {version, val};
}
long long calc(int id, vector<long long> &nums){
	if(id == 0){
		long long sum = 0;
		for(auto num: nums)
			sum += num;
		return sum;
	}
	if(id == 1){
		long long product = 1;
		for(auto num: nums)
			product *= num;
		return product;
	}
	if(id == 2){
		long long min_num = INT64_MAX;
		for(auto num: nums)
			min_num = min(min_num, num);
		if(min_num == INT64_MAX)
			cout <<"????\n";
		return min_num;
	}
	if(id == 3){
		long long max_num = INT64_MIN;
		for(auto num: nums)
			max_num = max(max_num, num);
		if(max_num == INT32_MIN)
			cout << "????\n";
		return max_num;
	}
	if(id == 5)
		return nums[0] > nums[1];
	if(id == 6)
		return nums[0] < nums[1];
	if(id == 7)
		return nums[0] == nums[1];
	cout << "Errrrro\n";
	return 0;
}
