#include <cstdint>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>
#include<regex>

using namespace std;
int main(){
	const std::regex reg("target area: x=([0-9]+)..([0-9]+), y=(-[0-9]+)..(-[0-9]+)");
	string inputStr;
	
	int x1, x2, y1, y2;
	cin >> x1 >> x2 >> y1 >> y2;
	int l = -y2 - 1, r = -y1;
	/* auto test = [&](int v){ */
	/* 	int pos = 0, t = 0; */
	/* 	while(pos > y2){ */
	/* 		pos += v; */
	/* 		v -= 1; */
	/* 		t ++; */
	/* 	} */
	/* 	cout << "Time: " << t << endl; */
	/* 	if(pos >= y1) */
	/* 		return true; */
	/* 	return false; */
	/* }; */
	unordered_map<int, int> heatMap;
	set<pair<int, int>> allAns;
	vector<vector<int>> t_vy_map(200);
	long long ans = 0;
	for(int i = y1; i < -y1; i++){
		int pos = 0, y = i, t = 0;
		while(pos > y2){
			pos += y;
			y -= 1;
			t++;
		}
		while(pos >= y1){
			heatMap[t]++;
			t_vy_map[t].push_back(i);
			pos += y;
			y -= 1;
			t++;
		}
	}
	//Calculate the limit of vx which fall to [x_min, x_max] when t is big enough t -> INF
	int x_l = INT32_MAX, x_r = INT32_MIN;
	for(int i = 0; i < x2; i++){
		int tmp = i * (i + 1) / 2;
		if(tmp > x2)
			break;
		if(x2 >= tmp && tmp >= x1){
			x_l = min(i, x_l);
			x_r = max(i, x_r);
		}
	}
	auto calc = [x1, x2, x_l, x_r](const int t){
		if(t > x_l) {
			//equal should be fail down to linear situation
			//cout << "t :" << t << ", vx's range [ " << x_l << " , " << min(t, x_r) << "]\n";
			return make_pair(x_l, min(t, x_r) + 1);//(min(t, x_r) - x_l + 1);
		}
		int l = 0, r = 0;
		l = ((2 * x1) / t + t - 1) / 2;
		r = ((2 * x2) / t + t - 1) / 2;
		while(t * (2 * l - t + 1) / 2 >= x1)
			l--;
		l++;
		int resl = t * (2 * l - t + 1) / 2; 
		/* cout << "t :" << t << ", vx's range ( " << l << " , " << r << "]\n"; */
		/* if(t * (2 * l - t) / 2 < x1) */
		/* 	cout << "L too small \n"; */
		if(resl < x1 || resl > x2)
			cout << "L out of range \n";
		if(t * (2 * (r + 1) - t + 1) / 2 < x2)
			cout << "R too small \n";
		return make_pair(l, r + 1);
	};
	for(auto p:heatMap){
		//cout << p.first << '\t' << p.second << endl;
		int t = p.first, freq = p.second;
		//Binary search?
		auto lr = calc(t);
		/* cout << "Vy: \t"; */
		for(auto vy: t_vy_map[t]){
			/* cout << vy << '\t'; */
			for(int vx = lr.first; vx < lr.second; vx++)
				allAns.insert({vx, vy});
		}
		/* cout << endl; */
		//cout << " | freq:" << freq * calc(t) << endl;
		ans += 1LL * freq * (lr.second - lr.first);
	}
	/* for(auto foo: allAns) */
	/* 	cout << "(" << foo.first << ", " << foo.second << ")\n"; */

	int res1 = abs(y1) - 1;
	cout << "Part I answer:\n" << res1 * (res1 + 1) / 2 << endl;
	cout << "Part II answer:\n" << allAns.size() << endl;
}

