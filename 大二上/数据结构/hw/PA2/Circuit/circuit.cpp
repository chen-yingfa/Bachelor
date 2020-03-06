#include <cstdio>
#include "donList.h"

//Trie Tree Node
class TTNode {
public:
	TTNode* lc = nullptr;
	TTNode* rc = nullptr;
	List<int>* list = nullptr; //List to store multiple nodes with same number
	
	//using this, when the root node of the tree is deleted,
	//this function will be called recursively to delete all
	//nodes in the tree
	~TTNode(){
		delete lc;
		delete rc;
		delete list; 
	}
	
	bool isLeaf(){
		return (!lc && !rc);
	}
};

//字典树
class TrieTree {
public:
	TTNode* root;
	TTNode* vine[64];
public:
	TrieTree() {
		root = new TTNode;
	}

	//insert new node of 64 bit number into the tree
	void push(bool* a, int id) {
		TTNode* cur = root;
		for (int i = 0; i < 64; i++) {
			if (a[i]) {
				if (!cur->rc) cur->rc = new TTNode;
				cur = cur->rc;
			}
			else {
				if (!cur->lc) cur->lc = new TTNode;
				cur = cur->lc;
			}
		}
		if (cur->list == nullptr){
			cur->list = new List<int>;
		}
		cur->list->pushBack(id);
	}

	//removing a node whose path is describing by a 64 bit array bool* a
	void pop(bool* a) {
		//handle the root node separately
		if (a[0]) vine[0] = root->rc;
		else vine[0] = root->lc;
		

		for (int i = 1; i < 64; i++) {
			if (a[i]) vine[i] = vine[i-1]->rc;
			else vine[i] = vine[i-1]->lc;
		}
		vine[63]->list->popFront();
		
		if (vine[63]->list->size() == 0){
			if (a[63]) vine[62]->rc = nullptr;
			else vine[62]->lc = nullptr;
			delete vine[63];
		}
		for (int i = 62; i > 0; i--){
			if (!vine[i]->isLeaf()){
				break;
			}
			if (a[i]) vine[i-1]->rc = nullptr;
			else vine[i-1]->lc = nullptr;
			delete vine[i];
		}
		if (vine[0]->isLeaf()){
			if (a[0]) root->rc = nullptr;
			else root->lc = nullptr;
			delete vine[0];
		}
	}

	//逆其道而行
	int query(bool* a) {
		TTNode* cur = root;
		for (int i = 0; i < 64; i++) {
			if (!a[i])
				cur = cur->rc ? cur->rc : cur->lc;
			else
				cur = cur->lc ? cur->lc : cur->rc;
		}
		return cur->list->first();
	}
};

int main() {
	int n, k, left, right;
	char str[70]; //the 64 bit
	bool** a = new bool*[500005];
	for (int i = 0; i < 500005; i++)
		a[i] = new bool[64];

	TrieTree tt;

	//get and store all input first
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		for (int j = 0; j < 64; j++) {
			a[i][j] = (str[j] == '1' ? true : false); //store as bool array
		}
	}
	
	//insert k+1 nodes into Trie Tree so that the query applies to 
	//numbers with less than k distance away from current number 
	for (int i = 0; i < k + 1; i++) {
		tt.push(a[i], i);
	}

	//start querying
	for (int i = 0; i < n; i++) {
		left = i - k - 2;
		right = i + k + 1;
		if (left >= 0)
			tt.pop(a[left]);
		if (right < n)
			tt.push(a[right], i + k + 1);

		printf("%d\n", tt.query(a[i]));
	}

	//free up memory
	for (int i = 0; i < 500000; i++) {
		delete[] a[i];
	}
	delete[] a;

	return 0;
}

