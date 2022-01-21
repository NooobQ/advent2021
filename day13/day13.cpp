#include<unordered_set>
#include<set>
#include<unordered_map>
#include<iostream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<string>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
#include<cstdio>
#include<ctype.h>
using namespace std;

auto cmp = [](const pair<int, int> &lhs, const pair<int, int> &rhs){
			if(lhs.second != rhs.second)
				return lhs.second < rhs.second;
			return lhs.first < rhs.first;
			};
void FoldX(set<pair<int, int>> &seta,
		set<pair<int, int>, decltype(cmp)> &setb, int flag, int pos);
void FoldY(set<pair<int, int>> &seta,
		set<pair<int, int>, decltype(cmp)> &setb, int flag, int pos);
int main(){
	//Close Sync with stdio, Faster cin
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int res = 0;
	string cin_string;
	set<pair<int, int>> seta;
	set<pair<int, int>, decltype(cmp)> setb(cmp);
	queue<pair<char, int>> sequence;
	/* while(getline(cin, cin_string)){ */
	/* 	stringstream sin(cin_string); */
			
	/* } */
	int a, b, line_num;
	int xmax = 0, ymax = 0;
	char axis;

	//Handling Input
	//Break meet empty line
	while(scanf("%d,%d\n", &a, &b)!=0){
		xmax = max(xmax, a);
		ymax = max(ymax, b);
		seta.insert({a, b});
		setb.insert({a, b});
	}
	while(scanf("fold along %c=%d\n", &axis, &line_num)!=EOF){
		sequence.push({axis, line_num});
	}

	/* printf("Point count: %d, max(x, y) = (%d, %d)\n", (int)Points.size(), xmax, ymax); */
	/* for(auto point: Points) */
	/* 	printf("(%d, %d)\n", point.first, point.second); */

	/* while(!sequence.empty()){ */
	/* 	auto seq = sequence.front(); */
	/* 	sequence.pop(); */
	/* 	printf("Folding %c at position %d\n", seq.first, seq.second); */
	/* } */
	auto testFoo = [&](){
		puts("Part II answer:");
		for(int j = 0; j <= ymax; j++){
			for(int i = 0; i <= xmax; i++){
				if(seta.count({i, j}))
					printf("#");
				else {
					printf(".");
				}
			}
			puts("");
		}
		puts("");
	};

	while(!sequence.empty()){
		//testFoo();
		auto curAxis = sequence.front().first == 'x';
		auto curPos = sequence.front().second;
		sequence.pop();
		//Fold (flag, pos)
		if(curAxis)
			FoldX(seta, setb, curAxis, curPos);
		else {
			FoldY(seta, setb, curAxis, curPos);
		}
		if(!res)
			res = seta.size();
		if(curAxis)
			xmax = curPos - 1;
		else {
			ymax = curPos - 1;
		}
	}

	cout << "Part I answer:\n";//>
	cout << res << '\n';//>>
	testFoo();
	//cout<<matrix[99][0][0].first<<'\n';
	return 0;
}
void FoldX(set<pair<int, int>> &seta, set<pair<int, int>, decltype(cmp)> &setb, int flag, int pos){
	//set<pair<int, int>, decltype(cmp)> &curSet = flag? seta: setb;
	//set<pair<int, int>> &anotherSet = !flag? seta: setb;
	vector<pair<int, int>> to_add, to_remove;

	//Binary Search
	auto curSet = seta;
	auto midIter = curSet.lower_bound(flag ?make_pair(pos, 0): make_pair(0, pos));
	//Compute
	for(auto curIter = midIter; curIter != curSet.end(); curIter++){
		int x = curIter->first , y = curIter -> second;
		to_remove.push_back({x, y});
		if(flag)
			x = 2 * pos - x;
		else {
			y = 2 * pos - y;
		}
		to_add.push_back({x, y});
	}
	
	//Insert
	for(auto elem: to_add){
		seta.insert(elem);
		setb.insert(elem);
	}
	//Remove
	for(auto elem: to_remove){
		seta.erase(elem);
		setb.erase(elem);
	}
}
void FoldY(set<pair<int, int>> &seta, set<pair<int, int>, decltype(cmp)> &setb, int flag, int pos){
	//set<pair<int, int>, decltype(cmp)> &curSet = flag? seta: setb;
	//set<pair<int, int>> &anotherSet = !flag? seta: setb;
	vector<pair<int, int>> to_add, to_remove;

	//Binary Search
	auto curSet = setb;
	auto midIter = curSet.lower_bound({0, pos});
	//Compute
	for(auto curIter = midIter; curIter != curSet.end(); curIter++){
		int x = curIter->first , y = curIter -> second;
		to_remove.push_back({x, y});
		if(flag)
			x = 2 * pos - x;
		else {
			y = 2 * pos - y;
		}
		to_add.push_back({x, y});
	}
	
	//Insert
	for(auto elem: to_add){
		seta.insert(elem);
		setb.insert(elem);
	}
	//Remove
	for(auto elem: to_remove){
		seta.erase(elem);
		setb.erase(elem);
	}
}
