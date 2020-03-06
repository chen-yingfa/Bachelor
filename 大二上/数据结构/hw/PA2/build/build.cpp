#include <cstdio>
#include <iostream>
using namespace std;

inline int max(int a, int b){
    return a > b ? a : b;
}

class Node{
public:
    //represent as binary tree where rc is oldest younger brother
    Node* p = nullptr;
    Node* lc = nullptr;
    Node* rc = nullptr;
    int id;
    int h;
    int size;
    
    Node(){}
    Node(int id){
        this->id = id;
    }
};

class Tree {
public:
    Node* root;

    int genSize(Node* cur){
        cur->size = 1;
        if (cur->lc) 
            cur->size += genSize(cur->lc);
        if (cur->rc)
            cur->size += genSize(cur->rc);
        return cur->size;
    }
    int genH(Node* cur){
		cur->h = 0;	
    	if (cur->lc){
			cur->h = genH(cur->lc) + 1;
		}
		if (cur->rc){
			cur->h = max(cur->h, genH(cur->rc));
		}
        return cur->h;
    }
    
    Node* getNode(){
    	
		//get height
		int idx, n;
		Node* cur = root;
		
		scanf("%d", &n);
		for (int j = 0; j < n; j++){
			scanf("%d", &idx);
			if (cur->lc == nullptr) continue;
			
			cur = cur->lc;
			while(idx--) {
				if (cur->rc)
					cur = cur->rc;
			}
		}
		//printf("got node %d\n", cur->id);
		
		return cur;
	}
	
	void updateAllSize(Node* n, int size){
		//printf("updating all size %d %d\n", n->id, size);
		while (n != root){
			updateSize(n);
			//printf("new size of %d: %d\n", n->id, n->size);
			n = n->p;
		}
		updateSize(n);
		
		//printf("new size of %d: %d\n", n->id, n->size);
	}
	
	void updateSize(Node* n){
		n->size = 1;
        if (n->lc) 
            n->size += n->lc->size;
        if (n->rc)
            n->size += n->rc->size;
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
		
		n->h = 0;	
    	if (n->lc)
			n->h = n->lc->h + 1;
		if (n->rc)
			n->h = max(n->h, n->rc->h);
	}
	
	void remove(Node* n){
		//printf("removing %d\n", n->id);
		if (n == n->p->lc){ //if n is the left child
			if (n->rc)
				n->p->lc = n->rc; 
			else 
				n->p->lc = nullptr;
		}
		else {  //else (n is right child)
			if (n->rc)
				n->p->rc = n->rc;
			else 
				n->p->rc = nullptr;
		}
		
		updateAllH(n);
		updateAllSize(n, -1 *  n->size);
		
	}
	
	void insert(Node* n, Node* target, int k){
		//printf("inserting %d %d %d\n", n->id, target->id, k);
		
		if (k == 0){
			if (target->lc){
				target->lc->p = n;
				n->rc = target->lc;
			}
			n->p = target;
			target->lc = n;
		}
		else {
			
			Node* cur = target->lc;
			for (int i = 0; i < k - 1; i++){
				if (cur->rc)
					cur = cur->rc;
			}
			
			if (cur->rc){
				cur->rc->p = n;
				n->rc = cur->rc;
			}
			n->p = cur;
			cur->rc = n;
			
		}
		
		
		//printf("parent: %d, size: %d\n", n->p->id, n->p->size);
		
		//updateAllSize(n, n->size);
		//updateAllH(n); 
	}
};

int main(){
    int n, m, numC, tmpId;
    bool *leaf;
    Node *oldestC, *cur;
    Tree tree;

    scanf("%d %d", &n, &m);

    Node** nodes = new Node*[n + 1];
    
    for (int i = 0; i <= n; i++){
        nodes[i] = new Node(i);
    }

    tree.root = nodes[1];

    //build tree
    for (int i = 1; i <= n; i++){
        scanf("%d", &numC);
        if (numC == 0)
            continue;
        
        //get oldest child and set as lc
        scanf("%d", &tmpId);
        nodes[i]->lc = nodes[tmpId];
        nodes[tmpId]->p = nodes[i];
        cur = nodes[tmpId];

        //get the other children and set as rc of oldestC
        for (int j = 1; j < numC; j++){
            scanf("%d", &tmpId);
            
            cur->rc = nodes[tmpId];
            nodes[tmpId]->p = cur;
            cur = cur->rc;
        }
    }


	int idx;
	
    //set height and size
    tree.genSize(tree.root);
    tree.genH(tree.root);

	for (int i = 2; i <= n; i++){
		//cout << "id: " << nodes[i]->id << ", size: " << nodes[i]->size << ", h: " << nodes[i]->h << ", p: " << nodes[i]->p->id << endl;
	}
    
    for (int i = 0; i < m; i++){
		scanf("%d", &tmpId);
		if (tmpId == 0){
			Node* start = tree.getNode();
			Node* goal = tree.getNode();
			
			int idx = 0;
			scanf("%d", &idx);
			
			tree.remove(start);
			tree.insert(start, goal, idx);
			
			for (int i = 2; i <= n; i++){
				//cout << "id: " << nodes[i]->id << ", size: " << nodes[i]->size << ", h: " << nodes[i]->h << ", p: " << nodes[i]->p->id << endl;
			}
		}
		else if (tmpId == 1){
			//get node
			Node* cur = tree.getNode();
			
			//get height
			if (!cur->lc){
				//height = 0
				printf("0\n");
			} else {
				printf("%d\n", cur->lc->h + 1);
			}
		} 
		else if (tmpId == 2){
			//get node
			Node* cur = tree.getNode();
			//get size
			if (!cur->lc){
				printf("1\n");
			} else {
				printf("%d\n", cur->lc->size + 1);
			}
		}
	}
	
	delete nodes;

    return 0;
}
