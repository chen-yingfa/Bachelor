#pragma once
#include <iostream>
#include <cstdio>

template<class T>
class ListNode {
public:
	ListNode<T>* prev = nullptr;
	ListNode<T>* next = nullptr;
	T _val;
public:
	ListNode() {}
	ListNode(T val) {
		_val = val;
	}
	T val() { return _val; }
};

template<class T> class List {
private:
	ListNode<T> *head;
	ListNode<T> *tail;
	int _size;
public:
	~List() {
		ListNode<T>* looper = head;
		while (looper != tail) {
			looper = looper->next;
			delete looper->prev;
		}
		delete looper;
	}
	List() {
		head = new ListNode<T>;
		tail = new ListNode<T>;
		head->next = tail;
		tail->prev = head;
		_size = 0;
	};
	int size() { return _size; }
	ListNode<T>* getHead() { return head; }
	ListNode<T>* getTail() { return tail; }
	ListNode<T>* getFirst() { return head->next; }
	ListNode<T>* getLast() { return tail->prev; }
	T first() { return head->next->val(); }
	T at(int n) {
		ListNode<T>* ret = this->head->next;
		while (n--)
			ret = ret->next;
		return ret->_val;
	}
	ListNode<T>* nodeAt(int n) {
		ListNode<T>* ret = head->next;
		while (n--)
			ret = ret->next;
		return ret;
	}
	T set(T a, int n) {
		nodeAt(n)->_val = a;
		return a;
	}
	T insertB(T a, int n) {
		return insertB(a, nodeAt(n));
	}
	T insertB(T a, ListNode<T>* ptr) {
		ListNode<T>* nodeA = new ListNode<T>(a);
		nodeA->next = ptr;
		nodeA->prev = ptr->prev;
		ptr->prev->next = nodeA;
		ptr->prev = nodeA;
		_size++;
		return a;
	}
	T insertA(T a, int n) {
		return insertB(a, n + 1); //won't overflow because of the existence of tail
	}
	T insertA(T a, ListNode<T>* ptr) {
		return insertB(a, ptr->next); //won't overflow because of the existence of tail
	}
	T remove(ListNode<T>* n) {
		n->prev->next = n->next;
		n->next->prev = n->prev;
		T tmp = n->_val;
		delete n;
		_size--;
		return tmp;
	}
	T remove(int n) {
		return remove(nodeAt(n));
	}
	T pushBack(T a) {
		return insertB(a, tail);
	}
	T pushFront(T a) {
		return insertA(a, head);
	}
	T popFront() {
		return remove(head->next);
	}
	void show() {
		ListNode<T>* looper = head->next;
		while (looper != tail) {
			std::cout << looper->_val << " ";
			looper = looper->next;
			//printf("%d", looper->_val);
		}
		std::cout << "    end\n";
	}
};