

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Node {
public:
    char* arr;
    Node* next = nullptr;
    Node* prev = nullptr;
    int cap = 0;
    int size = 0;
public:
    ~Node(){
        delete arr;
    }
    Node(int _cap){
        cap = _cap;
        arr = new char[_cap];
    }

    char at(int n){
        if (n < 0){
            if (prev->cap == 0)
                return '!';
            return prev->at(prev->size + n);
        }
        if (size <= n){
            if (next->cap == 0)
                return '!';
            return next->at(n - size);
        }
        // 0 <= n < size
        return arr[n];
    }

    void pushBack(char c){
        insert(c, size);
    }

    void insert(char c, int n){
        // cout << "inserting " << c << " into pos " << n << " in ";
        // show();
        char prev = c, tmp;
        int i = n;
        for (; i < size; i++){
            tmp = arr[i];
            arr[i] = prev;
            prev = tmp;
        }
        arr[i] = prev;
        size++;
    }

    void pop(int n){
        // cout << "popping(" << n << "), ";
        // show();
        if (size <= n){
            next->pop(n - size);
        } else if (n < 0){
            prev->pop(prev->size + n);
        } else {
            // 0 <= n < size
            for (int i = n; i < size - 1; i++){
                arr[i] = arr[i+1];
            }

            size--;
        }
        // cout << "popped(" << n << "),  ";
        // show();
    }

    void delArr(){
        delete arr;
    }

    void show(){
        // cout << "cap = " << cap << ", size = " << size << endl;
        if (size == 0){
			cout << "[empty]" << endl;
			return;
		}
        cout << "[";
        for (int i = 0; i < size; i++){
            cout << arr[i] << ", ";
        }
        cout << "], size = " << size << endl;
        
    }

    void showStr(){
        for (int i = 0; i < size; i++){
            cout << arr[i];
        }
    }
};

class List{
private:
    Node* head = new Node(0);
    Node* tail = new Node(0);
    int cap = 0;
    int size = 0;
    int nodeCap = 1000;
    int nNode = 0;
public:
    List(int _cap){
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;

        // nodeCap = 2 * sqrt(_cap);

        while (0 < _cap){
            Node* tmpNode = new Node(nodeCap);
            pushBack(tmpNode);
            _cap -= nodeCap;
        }
    }

    List(string s){
        int _cap = s.size();

        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;

        // nodeCap = 2 * sqrt(_cap);

        int i = 0;

        while (0 < _cap){
            Node* tmpNode = new Node(nodeCap);

            for (int k = 0; k < nodeCap / 2 && i < s.size(); k++){
                tmpNode->pushBack(s[i++]);
            }

            pushBack(tmpNode);
            _cap -= nodeCap / 2;
        }
    }

    void pushBack(Node* n){
        insertNode(n, tail->prev);
    }

    void insertNode(Node* node, int n){
        Node* pt = head;
        for (int i = 0; i < n; i++){
            pt = pt->next;
        }
        insertNode(node, pt);
    }

    void insertNode(Node* node, Node* pt){
        node->prev = pt;
        node->next = pt->next;
        pt->next->prev = node;
        pt->next = node;
        nNode++;
        cap += node->cap;
        size += node->size;
    }

    void pushBack(char c){
        insert(c, size);
    }

    void pop(Node* &pt, int n){
        char target = pt->at(n);
        int i = n;
        while (pt->at(--i) == target);
        i++;
        // show();
        // cout << "pop(" << n << ") in ";
        // pt->show();
        Node* popper = pt;

        while (i < 0){
            popper = popper->prev;
            i += popper->size;
        }

        while(popper->at(i) == target){
            if (popper->size == 0){
                popper = popper->next;
                popNode(popper->prev);
            }

            // cout << "i=" << i << ", n=" << n << ", popper=";
            // popper->show();

            popper->pop(i);
            size--;
        }

        while (popper->size == 0 && popper != tail){
            popper = popper->next;
            popNode(popper->prev);
        }
        pt = popper;

        // cout << "done popping\n\n";
        // show();
    }

    void checkPop(Node* pt, int n){
        if (size < 3)
            return;
        //at this point, n < pt->size
        // cout << "checkPop() in ";
        // pt->show();
        if (pt->at(n) == pt->at(n+1) && pt->at(n) == pt->at(n+2)) {
            pop(pt, n+1);
            checkPop(pt, n);
        }
        else if (pt->at(n) == pt->at(n-1) && pt->at(n) == pt->at(n+1)){
            pop(pt, n);
            checkPop(pt, n-1);
        }
        else if (pt->at(n) == pt->at(n-2) && pt->at(n) == pt->at(n-1)){
            pop(pt, n-1);
            checkPop(pt, n-2);
        }
    }

    void insert(char c, int n){

        if (size == 0){
            Node* pt = new Node(nodeCap);
            pt->pushBack(c);
            insertNode(pt, head);
            return;
        }
        Node* pt = head->next;
        while (pt->size < n){
            n -= pt->size;
            pt = pt->next;
        }

        // now we have, pt->size <= n
        if (pt->size == pt->cap){  
            divNode(pt);
            if (pt->size <= n){
                n -= pt->size;
                pt = pt->next;
            }
        }
        pt->insert(c, n);
        size++;

        checkPop(pt, n);
    }

    void divNode(Node* node){
        Node* newNode = new Node(nodeCap);
        for (int i = 0; i < nodeCap / 2.0 + 0.5; i++){
            newNode->pushBack(node->arr[nodeCap / 2]);
            node->pop(nodeCap / 2);
            size--;
        }
        insertNode(newNode, node);
    }

    Node* getPt(int n){
        Node* pt = head->next;
        while (pt->size <= n){
            n -= pt->size;
            pt = pt->next;
        }
        return pt;
    }

    void popNode(int n){
        Node* pt = getPt(n);
        pt->delArr();
        if (pt->size == 0){
            popNode(pt);
        }
    }

    void popNode(Node* node){
        node->next->prev = node->prev;
        node->prev->next = node->next;
        node->delArr();
        nNode--;
        cap -= nodeCap;
        // cout << "popNode result:\n";
        // show();
    }

    void show(){
        Node* pt= head->next;
        cout << "-----------\n";
        cout << "cap = " << cap << ", nNode = " << nNode << ", size = " << size << endl;
        for (int i = 0; i < nNode; i++){
            pt->show();
            pt = pt->next;
        }
        showStr();
        cout << "----------\n";
    }

    void showStr(){
        Node* pt= head->next;
        for (int i = 0; i < nNode; i++){
            pt->showStr();
            pt = pt->next;
        }
        cout << endl;
    }
};


int main(){
    std::string s = "ABCDEFGHIJ";
    int m, n, x;
    char c;
    std::getline(std::cin, s);
    m = s.size();

    scanf("%d", &n);
    List list(s);
    // list.show();
    while (n--){
        scanf("%d %c", &x, &c);
        list.insert(c, x);
        // list.show();
    }

    list.showStr();

    return 0;
}

/*
example

ACCBAABCBCB
5
1 B
0 A
2 B
4 C
0 A


4
0 A
1 B
2 B
1 B

*/
