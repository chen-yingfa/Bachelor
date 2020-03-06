#include <iostream>
using namespace std;

class Queue{
private:
	int* arr;
	int head = 0;
	int tail = 0;
	int cap;
	int size = 0;
public:
	Queue(int _cap){
		cap = _cap;
		arr = new int[cap];
	}
	bool has(int n){
		int cur = head;
		for (int i = 0; i < size; i++){
			if (arr[cur] == n)
				return true;
			incr(cur);
		}
		return false;
	}
	void push(int n){
		arr[tail] = n;
		incr(tail);
		if (size < cap)
			size++;
		else
			incr(head);
	}

	void incr(int& id){ id = (id + 1) % cap; }
};

int main(){
	int n, m, tmp, ans = 0;
	cin >> n >> m;
	Queue q(n);
	while (m--){
		cin >> tmp;
		if (!q.has(tmp)){
			ans++;
			q.push(tmp);
		}
	}
	cout << ans << endl;
	return 0;
}
