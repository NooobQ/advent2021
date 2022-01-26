#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
#include <vector>

using namespace std;
constexpr int NODE = 0;
constexpr int REGNUM = 1;
class node{
public:
	bool type;
	int reg_num;
	node *l, *r;
	node *prev, *next;//useless...
	node(int type, int num): type(type), reg_num(num), l(nullptr), r(nullptr) {};
	node(int type): type(type), reg_num(-1), l(nullptr), r(nullptr){};
	static void print(node *root);
};

//test print using in-order-tree-travesal should be equal to input string.
void node::print(node *root){
	if(!root)
		return;
	if(root -> type){
		cout << root ->reg_num;
		return;
	}
	cout << '[';
	print(root -> l);
	cout << ',';
	print(root -> r);
	cout << ']';
}

node* buildTree(string &);
node* add(node *a, node *b);
void reduce(node *);
bool explode(node *);
bool split(node *);
bool Split(node *);
long long magnitude(node *);
void deleteTree(node *);

int main(){
	string str;
	vector<string> vecstr;
	vector<node *> vec;
	while(cin >> str){
		vecstr.push_back(str);
		node *r = buildTree(str);
		vec.push_back(r);
		reduce(r);
	}
	int n = vecstr.size();
	//Part I
	node *prev = vec[0];
	for(int i = 1; i < n; i++){
		node *cur = new node(NODE);
		cur -> l = prev;
		cur -> r = vec[i];
		reduce(cur);
		prev = cur;
	}
	cout << "Part I answer:\n" << magnitude(prev) << endl;
	deleteTree(prev);

	//Part II
	long long ans = 0;
	for(int i = 0; i < n - 1; i++){
		for(int j = i + 1; j < n; j++){
			string tmp = "[" + vecstr[i] + "," + vecstr[j] + "]";
			node *cur = buildTree(tmp);
			reduce(cur);
			ans = max(ans, magnitude(cur));
			deleteTree(cur);
			tmp.clear();
			tmp = "[" + vecstr[j] + "," + vecstr[i] + "]";
			cur = buildTree(tmp);
			reduce(cur);
			ans = max(ans, magnitude(cur));
			deleteTree(cur);
		}
	}
	cout << "Part II answer:\n" << ans << endl;
}

//Build Tree from input string 
node* buildTree(string &str){
	int num = 0;
	node *root = new node(NODE);
	node *tmp = root;
	stack<node*> ancestor;
	int slen = str.length();
	for(int i = 0; i < slen; i++){
		char ch = str[i];
		if(ch == '['){
			//push into stack
			ancestor.push(tmp);
			tmp -> l = new node(NODE);
			tmp = tmp -> l;
			num = 0;
		}else if(ch == ','){
			if(str[i - 1] != ']'){
				tmp ->type = REGNUM;
				tmp ->reg_num = num;
			}

			//Poping from stack
			tmp = ancestor.top();
			//transfer to right
			tmp -> r = new node(NODE);
			tmp = tmp -> r;

			//Clear num
			num = 0;
		}else if(ch == ']'){
			if(str[i - 1] != ']'){
				tmp ->type = REGNUM;
				tmp ->reg_num = num;
			}

			//Poping from stack
			tmp = ancestor.top();
			ancestor.pop();
			num = 0;
		}else{
			//Cases '0' ~ '9'
			num = num * 10 + ch - '0';
		}
	}
	/* node::print(root); */
	/* cout << endl; */
	return root;
}

//Recursive sum up the magnitude.
long long magnitude(node *root){
	if(!root)
		return 0;
	if(root -> type == REGNUM)
		return root ->reg_num;
	return 3LL * magnitude(root -> l) + 2LL * magnitude(root -> r);
}

//Reducing
void reduce(node *root){
	while(explode(root))
		;
	int retry = Split(root);
	//Re-reduce if explode & reduce;
	if(retry)
		reduce(root);
	return;
}

//Exploding in-order-traveral with loop 
bool explode(node *root){
	int exploded = 0;
	node *L = nullptr;
	int R = 0, flag = 0;
	stack<pair<node *, int>> nodepthStack;
	nodepthStack.push({root, 0});
	//Use stack to simulate the recursive call, transfer recuresive to iterative
	//tracing the depth of direct pair and explode it.
	while(!nodepthStack.empty()){
		node *cur = nodepthStack.top().first;
		int depth = nodepthStack.top().second;
		nodepthStack.pop();
		if(cur -> type == REGNUM){
			L = cur;
			if(exploded){
				cur -> reg_num += R;
				exploded = 0;
				break;
			}
		}
		else{
			if(depth > 3 && cur -> l ->type == REGNUM
					&& cur -> r -> type == REGNUM && !exploded){	//!exploded to avoid 2nd explode
				//explode point;
				exploded = 1;
				cur -> type = REGNUM;
				cur -> reg_num = 0;
				flag = 1;
				if(L)
					L -> reg_num += cur -> l -> reg_num;
				R = cur -> r -> reg_num;
				//TO-DO: uncomment the code If OOM ,clean up cur -> l & cur -> r
				/* delete cur->l; */
				/* delete cur->r; */
				/* cur -> l = cur -> r = nullptr; */
			}
			else{
				nodepthStack.push({cur -> r, depth + 1});
				nodepthStack.push({cur -> l, depth + 1});
			}
		}
	}
	/* if(flag){ */
	/* 	cout << "after explode:\t"; */
	/* 	node::print(root); */
	/* 	cout << endl; */
	/* } */
	return flag;
}

bool split(node *root){
	if(!root)
		return false;
	if(root -> type == REGNUM && root ->reg_num >= 10){
		int val = root -> reg_num;
		root -> type = NODE;
		root -> l = new node(REGNUM, val / 2);
		root -> r = new node(REGNUM, (val + 1) / 2);
		return true;
	}
	return split(root->l) || split(root ->r);
}

bool Split(node *root){
	int ans = split(root);
	/* if(ans){ */
	/* 	cout << "after split:\t"; */
	/* 	node::print(root); */
	/* 	cout << endl; */
	/* } */
	return ans;
}

void deleteTree(node *root){
	if(!root)
		return;
	deleteTree(root -> l);
	deleteTree(root -> r);
	delete root;
}
