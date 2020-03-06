#include "donList.h"
#include <cstdio>
#include <iostream>

using namespace std;

inline int max(int a, int b){
    return a > b ? a : b;
}

class Node{
public:
    //represent as binary tree where rc is oldest younger brother
    Node* p;
    List<int>* ch = new List<int>;
    int id;
    int h = -1;
    int size = -1;
    
    Node(){}
    Node(int id){
        this->id = id;
    }
    void show(){
		cout << "id: " << id << ", size: " << 
		size << ", h: " << h 
		<< ", p: " << p->id << endl;
		cout << "ch: ";
		for (int i = 0; i < ch->size(); i++){
			cout << ch->at(i) << " ";
		}
		cout << endl;
	}
};

Node** nodes;

class Tree {
public:
    Node* root;

    int genSize(Node* cur){
        cur->size = 1;
        ListNode<int>* lNode = cur->ch->getHead()->next;
        while (lNode != cur->ch->getTail()){
			cur->size += genSize( nodes[lNode->val()] );
			lNode = lNode->next;
		}
		
        return cur->size;
    }
    int genH(Node* cur){
		if (cur->ch->size() == 0){
			cur->h = 0;
			return cur->h;
		}
		else {
			cur->h = 1;
		}
		ListNode<int>* lNode = cur->ch->getHead()->next;
    	while (lNode != cur->ch->getTail()) {
			cur->h = max(cur->h, genH( nodes[lNode->val()] ) + 1);
			lNode = lNode->next;
		}

        return cur->h;
    }
    
    Node* getNode(){
    	//cout << "getNode()\n";
		int idx = 1, n;
		int cur = 1;
		
		scanf("%d", &n);
		//printf("n = %d\n", n);
		int j = 0;
		for (; j < n;){
			scanf("%d", &idx);
			j++;
			//cout << "idx = " << idx << endl;
			if (nodes[cur]->ch->size() <= 0 || nodes[cur]->ch->size() <= idx){
				//printf("j = %d break\n", j);
				break;
			}
			cur = nodes[cur]->ch->at(idx);
			//cout << "cur at " << nodes[cur]->id << endl;
		}
		
		while (j < n) {
			scanf("%d", &idx);
			j++;
		}
		
		//printf("got node %d\n", cur);
		
		return nodes[cur];
	}
	
	void updateAllSize(Node* n, int size){
		//printf("updating all size %d %d\n", n->id, size);
		while (n->id != 1){
			n->size += size;
			//printf("new size of %d: %d\n", n->id, n->size);
			n = n->p;
		}
		n->size += size;
		
		//printf("new size of %d: %d\n", n->id, n->size);
	}
	
	void updateAllH(Node* n){
		
		//printf("updating all h\n");
		while (n != root){
			updateH(n);
			n = n->p;
		}
		updateH(n);
	}
	
	void updateH(Node* n){
		if (n->ch->size() == 0)
			n->h = 0;
		else 
			n->h = 1;
		
		ListNode<int>* lNode = n->ch->getHead()->next;
    	while (lNode != n->ch->getTail()) {
			n->h = max(n->h, nodes[lNode->val()]->h + 1 );
			lNode = lNode->next;
		}
		//printf("new h of %d: %d\n", n->id, n->h);
	}
	
	void remove(Node* n, int idx){
		//printf("removing %d %d\n", n->id, idx);
		Node* parent = n->p;
		parent->ch->remove(idx);

		updateAllSize(parent, -1 *  n->size);
		updateAllH(parent);
	}
	
	void insert(Node* n, Node* target, int k){
		//printf("inserting %d %d %d\n", n->id, target->id, k);
		
		target->ch->insertB(n->id, k);
		n->p = target;
		
		updateAllSize(target, n->size);
		updateAllH(target); 
	}
};

int main(){
    int n, m, numC, tmpId, idx, tmp, pathLen;
    bool *leaf;
    Node *oldestC, *cur;
    Tree tree;

    scanf("%d %d", &n, &m);

    nodes = new Node*[n + 1];
    
    for (int i = 0; i <= n; i++){
        nodes[i] = new Node(i);
    }

    tree.root = nodes[1];
    nodes[1]->p = nodes[1];

    //build tree
    for (int i = 1; i <= n; i++){
        scanf("%d", &numC);

        //set children
        for (int j = 0; j < numC; j++){
            scanf("%d", &tmpId);
            
            nodes[i]->ch->pushBack(tmpId);
            nodes[tmpId]->p = nodes[i];
        }
    }
	
    //set height and size
    tree.genSize(tree.root);
    //cout << "gened size\n";
    tree.genH(tree.root);
    //cout << "gened h\n";

	for (int i = 1; i <= n; i++){
		//nodes[i]->show();
	}
    
    for (int i = 0; i < m; i++){
		scanf("%d", &tmpId);
		if (tmpId == 0){

			//get to be removed
			int lastI;
			int cur = 1;
			
			scanf("%d", &pathLen);
			//printf("n = %d\n", n);
			int j = 0;
			for (; j < pathLen;){
				scanf("%d", &idx);
				j++;
				//cout << "idx = " << idx << endl;
				if (nodes[cur]->ch->size() <= 0 || nodes[cur]->ch->size() <= idx){
					break;
				}
				cur = nodes[cur]->ch->at(idx);
				//cout << "cur at " << nodes[cur]->id << endl;
				lastI = idx;
			}
			
			while (j++ < pathLen) {
				scanf("%d", &idx);
			}

			Node* start = nodes[cur];
			//cout << "got node " << start->id << endl;
			tree.remove(start, lastI);

			Node* target = tree.getNode();
			
			scanf("%d", &idx);
			
			tree.insert(start, target, idx);
			
			//cout << " --- tree --- \n";
			for (int i = 1; i <= n; i++){
				nodes[i]->show();
			}
		}
		else if (tmpId == 1){
			Node* cur = tree.getNode();
			//printf("height: ");
			printf("%d\n", cur->h);
		} 
		else if (tmpId == 2){
			Node* cur = tree.getNode();
			//printf("size: ");
			printf("%d\n", cur->size);
		}
	}
	
	delete nodes;

    return 0;
}


