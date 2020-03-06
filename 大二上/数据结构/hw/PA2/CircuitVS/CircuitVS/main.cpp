#include <cstdio>
#include <iostream>
#include "donList.h"

using namespace std;

class TTNode {
public:
	TTNode* lc = nullptr;
	TTNode* rc = nullptr;
	List<int> list;

	~TTNode() {
		delete lc;
		delete rc;
	}

	bool isLeaf() {
		return (!lc && !rc);
	}
};

class TrieTree {
public:
	TTNode* root;
	TTNode* vine[64];
public:
	TrieTree() {
		root = new TTNode;
	}
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
		cur->list.pushBack(id);
	}

	void pop(bool* a) {
		if (a[0]) vine[0] = root->rc;
		else vine[0] = root->lc;

		for (int i = 1; i < 64; i++) {
			if (a[i]) vine[i] = vine[i - 1]->rc;
			else vine[i] = vine[i - 1]->lc;
		}
		vine[63]->list.popFront();
		if (vine[63]->list.size() == 0) {
			delete vine[63];
		}
		for (int i = 62; i > 0; i--) {
			if (!vine[i]->isLeaf()) {
				break;
			}
			if (a[i]) vine[i - 1]->rc = nullptr;
			else vine[i - 1]->lc = nullptr;
			delete vine[i];
		}
		if (vine[0]->isLeaf()) {
			if (a[0]) root->rc = nullptr;
			else root->lc = nullptr;
			delete vine[0];
		}
	}

	int query(bool* a) {
		TTNode* cur = root;
		for (int i = 0; i < 64; i++) {
			if (!a[i])
				cur = cur->rc ? cur->rc : cur->lc;
			else
				cur = cur->lc ? cur->lc : cur->rc;
		}
		return cur->list.first();
	}
};

int main() {
	int n, k, left, right;
	char c;
	char str[100];
	bool** a = new bool*[500005];
	for (int i = 0; i < 500005; i++)
		a[i] = new bool[64];

	TrieTree tt;

	scanf_s("%d %d", &n, &k);

	//c = getchar();

	for (int i = 0; i < n; i++) {
		//while (c != '0' && c != '1') c = getchar();
		scanf_s("%s", &str[0]);
		for (int j = 0; j < 64; j++) {
			//a[i][j] = (c == '1' ? true : false);
			a[i][j] = (str[j] == '1' ? true : false);
			//c = getchar();
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 64; j++) {
			cout << a[i][j];
		}
		cout << endl;
	}



	for (int i = 0; i < k + 1; i++) {
		tt.push(a[i], i);
	}

	for (int i = 0; i < n; i++) {
		left = i - k - 2;
		right = i + k + 1;
		if (left >= 0)
			tt.pop(a[left]);
		if (right < n)
			tt.push(a[right], i + k + 1);

		printf("%d\n", tt.query(a[i]));
	}

	for (int i = 0; i < 500000; i++) {
		delete[] a[i];
	}
	delete[] a;


	system("pause");
	return 0;
}
