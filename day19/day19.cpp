#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <string>
#include <tuple>
#include <cstdio>
#include <chrono>

using namespace boost::numeric::ublas;
void search(
	std::vector<matrix<int>> &rotate_mat,
	std::vector<std::vector<vector<int>>> &scaner,
	std::set<int> &finished,
	std::vector<std::set<std::tuple<int, int, int>>> &valided_set,
	std::set<std::tuple<int, int, int>> &point_sets,
	std::vector<std::tuple<int, int, int>> &scaner_pos,
	int i);
int main(){

	/*
	 * Matrix combination
	 * | 1 0 0 dx |  x     x+dx
	 * | 0 1 0 dy |  y --  y+dy
	 * | 0 0 1 dz |  z --  z+dz
	 * | 0 0 0 1  |  1      1
	 */
	auto start = std::chrono::high_resolution_clock::now();
	//Step 1: iterate all 24 kind of rotation 2^3 * 3
	matrix<int> R = zero_matrix<int>(4, 4);
	R(0, 0) = 1; R(1, 2) = -1; R(2, 1) = 1;
	matrix<int> T = zero_matrix<int>(4, 4);
	T(0, 1) = 1; T(1, 0) = -1; T(2, 2) = 1;
	matrix<int> B = zero_matrix<int>(4, 4);
	B(0, 0) = 1; B(1, 1) = 1; B(2, 2) = 1;
	std::vector<matrix<int>> rotate_mat;
	auto cmp = [](const matrix<int> &a,const matrix<int> &b){
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++)
				if(a(i, j) != b(i, j))
					return a(i, j) < b(i, j);
		}
		return false;
	};
	std::set<matrix<int>, decltype(cmp)> stmp(cmp);
	stmp.insert(B);
	while(stmp.size() < 24){
		for(auto m:stmp){
			matrix<int> tmp = prod(R, m);
			//std::cout << tmp << std::endl;
			//avoiding iterator fail.
			if(!stmp.count(tmp)){
				stmp.insert(tmp);
				break;
			}
			tmp = prod(T, m);
			if(!stmp.count(tmp)){
				stmp.insert(tmp);
				break;
			}
		}
	}

	/* std::cout << "---------------------" << stmp.size() <<std::endl; */
	/* int neg[2] = {-1, 1}; */
	/* for(int i = 0; i < 2; i++){ */
	/* 	for(int j = 0; j < 2; j++){ */
	/* 		for(int k = 0; k < 2; k++){ */
	/* 			for(int kk = 0; kk < 3; kk++){ */
	/* 				matrix<int> m = zero_matrix<int>(4, 4); */
	/* 				m(0, kk) = neg[i]; */
	/* 				m(1, (kk + 1) % 3) = neg[j]; */
	/* 				m(2, (kk + 2) % 3) = neg[k]; */
	/* 				rotate_mat.push_back(m); */
	/* 			} */
	/* 		} */
	/* 	} */
	/* } */
	for(auto m:stmp)
		rotate_mat.push_back(m);

	std::vector<std::vector<vector<int>>> scaner;
	std::vector<matrix<int>> vec;
	int scaner_id = 0;
	std::string bak;

	/* for(auto mat: rotate_mat) */
	/* 	std::cout << mat <<std::endl; */
	//Step 2: deall with Input
	while(1){
		if(!std::getline(std::cin, bak))
			break;
		/* std::cout << "Input: " << bak << std::endl; */
		/* std::cout << "Id:" << scaner_id << std::endl; */
		scaner.push_back(std::vector<vector<int>>());
		int px, py, pz;char dot;
		while(std::cin >> bak){
			/* std::cout << bak << std::endl; */
			if(sscanf(bak.c_str(), "%d,%d,%d", &px, &py, &pz)!=3)
				break;
			vector<int> vtmp = vector<int>(4);
			vtmp(0) = px; vtmp(1) = py; vtmp(2) = pz; vtmp(3) = 1;
			scaner[scaner_id].push_back(vtmp);
		}
		/* for(auto v: scaner[scaner_id]) */
		/* 	std::cout << v << std::endl; */
		scaner_id++;
	}
	//Step 3: calculate the (dx, dy, dz) and traverse to encounter 12 other points.
	std::vector<std::set<std::tuple<int, int, int>>> valided_set(scaner_id);
	std::set<std::tuple<int, int, int>> point_sets;
	std::set<int> finished;
	std::vector<std::tuple<int, int, int>> scaner_pos(scaner_id);
	

	finished.insert(0);
	for(auto _vec:scaner[0]){
		point_sets.insert(std::make_tuple(_vec(0), _vec(1), _vec(2)));
		valided_set[0].insert(std::make_tuple(_vec(0), _vec(1), _vec(2)));
	}

	int loop = scaner_id;
	while(loop--){
		//Randomize
		for(int i = 1; i < scaner_id; i++){
			if(finished.count(i))
				continue;
			search(rotate_mat, scaner, finished, valided_set, point_sets, scaner_pos, i);
		}
	}

	/* std::cout <<"--------Ending-------\n"; */
	/* for(int i = 0; i < scaner_id; i++){ */
	/* 	for(auto v: scaner[i]) */
	/* 		std::cout << v << std::endl; */
	/* 	std::cout << "-------\n"; */
	/* } */
	/* for(int i = 0; i < scaner_id; i++){ */
	/* 	for(auto v:scaner[i]){ */
	/* 		point_sets.insert(std::make_tuple(v(0), v(1), v(2))); */
	/* 	} */
	/* } */
	/* for(int i = 0; i < scaner_id; i++){ */
	/* 	std::cout << "val:" << valided_set[i].size() << '\n'; */
	/* } */
	/* std::cout << "\nAns: " << point_sets.size() << '\n'; */
	/* std::cout << "-------------\n"; */
	/* for(auto _v:point_sets){ */
	/* 	printf("(%d,%d,%d)\n", std::get<0>(_v), std::get<1>(_v), std::get<2>(_v)); */
	/* } */
	//std::cout << prod(rotate_mat[0], X) << std::endl;
	int res = 0;
	for(int i = 0; i < scaner_pos.size() - 1; i++){
		for(int j = i + 1; j < scaner_pos.size(); j++){
			res = std::max(res,
				abs(std::get<0>(scaner_pos[i]) - std::get<0>(scaner_pos[j])) + 
				abs(std::get<1>(scaner_pos[i]) - std::get<1>(scaner_pos[j])) + 
				abs(std::get<2>(scaner_pos[i]) - std::get<2>(scaner_pos[j]))
					);
		}
	}
	std::cout << "PartI answer:\n" << point_sets.size() << std::endl;
	std::cout << "PartII answer:\n" << res << std::endl;

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time Cost: " << duration.count() << "ms.\n";

}
//TO-DO: NOT-CACHE-FRIENDLY Can be optimized by randomize
void search(
	std::vector<matrix<int>> &rotate_mat,
	std::vector<std::vector<vector<int>>> &scaner,
	std::set<int> &finished,
	std::vector<std::set<std::tuple<int, int, int>>> &valided_set,
	std::set<std::tuple<int, int, int>> &point_sets,
	std::vector<std::tuple<int, int, int>> &scaner_pos,
	int i
		){
	for(int type_mat = 0; type_mat < 24; type_mat++){
		//Traverse each point
		for(auto veca: scaner[i]){
			/* vector<int> veca */
			//From Create all matrix
			for(auto idx: finished){
				for(auto vecb: scaner[idx]){
					matrix<int> m(rotate_mat[type_mat]);
					//Modify the matrix
					vector<int> tmp = prod(m, veca);
					m(0, 3) = vecb(0) - tmp(0);
					m(1, 3) = vecb(1) - tmp(1);
					m(2, 3) = vecb(2) - tmp(2);
					m(3, 3) = 1;
					//Try cuting search tree.
					/* if( */
					/* 		abs(m(0, 3) - std::get<0>(scaner_pos[idx])) > 2000 || */
					/* 		abs(m(1, 3) - std::get<1>(scaner_pos[idx])) > 2000 || */
					/* 		abs(m(2, 3) - std::get<2>(scaner_pos[idx])) > 2000 */ 
					/* 	) */
					/* 	continue; */

					/* if(i == 2) */
					/* 	std::cout << "mod matrix: " << m << '\n'; */
					int same_cnt = 0;
					//Valiation check
					for(auto V:scaner[i]){
						vector<int> verified = prod(m, V);
						if(valided_set[idx].count(std::make_tuple(verified(0), verified(1), verified(2))))
						//if(point_sets.count(std::make_tuple(verified(0), verified(1), verified(2))))
							same_cnt++;
					}
					if(same_cnt >= 12){
						finished.insert(i);
						
						//Transfer matrix
						for(auto iter = scaner[i].begin(); iter != scaner[i].end(); iter++){
							*iter = prod(m, *iter);
							valided_set[i].insert(std::make_tuple((*iter)(0), (*iter)(1), (*iter)(2)));
							point_sets.insert(std::make_tuple((*iter)(0), (*iter)(1), (*iter)(2)));
						}
						/* std::cout << "Found Matrix: " << m << "successfully\n"; */
						scaner_pos[idx] = std::make_tuple(m(0, 3), m(1, 3), m(2, 3));
						//scaner_pos.push_back(std::make_tuple(m(0, 3), m(1, 3), m(2, 3)));
						return;
					}
				}
			}
		}
	}
}
