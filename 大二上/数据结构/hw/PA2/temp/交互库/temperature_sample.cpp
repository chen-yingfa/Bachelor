#include <cstdlib>
#include <cstdio>
#include <math.h>
#include "temperature.h"

using namespace std;

class Pos {
public:
    int x, y;

};

bool isEq(Pos a, Pos b){
    return (a.x == b.x && a.y == b.y);
}

class Node {
public:
    Node(){}
    Node(int x, int y){
        
    }
    Pos p;
    int t;
    int max, min;
    int left, right;
    int r;
    Node *lc = nullptr;
    Node *rc = nullptr;
};

Node* insert(Node* root, Pos p, int rank){
    if (!root){
        Node* newNode = new Node;
        newNode->p = p;
        newNode->r = 0;
        return newNode;
    }

    bool isX = !(rank & 1); //if rank is even, divide by x coord

    if (isX){
        if (p.x < root->p.x){
            root->lc = insert(root->lc, p, rank + 1);
        } else {
            root->rc = insert(root->rc, p, rank + 1);
        }
    } else {
        if (p.y < root->p.y){
            root->lc = insert(root->lc, p, rank + 1);
        } else {
            root->rc = insert(root->rc, p, rank + 1);
        }
    }

    return root;
}

int queryMin(Node* root, Pos low, Pos high, int rank){
    if (!root)
        return INT_MAX;
    
    bool isX = !(rank & 1); //if rank is even, is handling x coord

    if (isX){
        if (root->right < low.x || high.x < root->left) {
            // root is outside of query region
            return INT_MAX;
        } else if (low.x < root->left && root->right < high.x) {
            return 
        }
        int lcMin, rcMin;
        if (root->p.x < low.x){
            //if root is on left side of region
            return min(root->t, queryMin(query(root*)));
        } else {
            //root is within the query region
            return 
        }
        
    } else {

    }
}

const int maxN;
Node** nodes;

void init(int n, const int *x, const int *y, const int *t) {
    // nothing to init

}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax) {
    *tmin = rand();
    *tmax = rand();
}
