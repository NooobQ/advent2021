#include <iostream>

using namespace std;
int main(){
	int posa, posb;
	cin >> posa >> posb;
	int scorea = 0, scoreb = 0, time = 0, dice = 1;
	auto roll = [&](){
		int res = 0;
		if(dice < 99){
			res = (dice + 1) * 3;
			dice = dice + 3;
			if(dice > 100)
				dice -= 100;
		}
		else{
			for(int i = 0; i < 3; i++){
				/* cout << dice << endl; */
				res +=dice;
				dice++;
				if(dice > 100)
					dice -= 100;
			}
		}
		return res;
	};
	int acnt = 10,bcnt = 10;
	while(scorea < 1000 && scoreb < 1000){
		if(time % 2 == 0){
			posa = (posa + (roll() % 10)) % 10;
			if(!posa)
				posa += 10;
			scorea += posa;
			if(acnt){
				/* cout << "posa = " << posa << ", scroe = " << scorea << endl; */
			}
		}
		else{
			posb = (posb + (roll() % 10)) % 10;
			if(!posb)
				posb += 10;
			scoreb += posb;
			if(bcnt){
				/* cout << "posb = " << posb << endl; */
			}
		}
		time++;
	}
	/* cout << min(scorea, scoreb) << '\t' << max(scorea, scoreb) << endl;; */
	/* cout << time *3 << endl;; */
	cout << "Result I: " << min(scorea, scoreb) * time * 3 << endl;
}
