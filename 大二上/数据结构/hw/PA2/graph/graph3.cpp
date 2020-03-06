#include <cstdio>
#include "donList.h"

using namespace std;

//merge sort for sorting answer
void merge(int a[], int l, int m, int r){
    //merge a[l...m-1] and a[m...r-1]
    int bk = m - l;
    int ck = r - m;

    int* b = new int[bk];
    int* c = new int[ck];

    for (int i = 0; i < bk; i++) 
        b[i] = a[l + i];
    for (int i = 0; i < ck; i++)
        c[i] = a[m + i];
        
    int i = 0, j = 0, k = l;
    while (i < bk && j < ck)
		b[i] < c[j] ? a[k++] = b[i++] : a[k++] = c[j++];
    while (i < bk) a[k++] = b[i++];
    while (j < ck) a[k++] = c[j++];
}

void mergeSort(int a[], int l, int r){
    if (r - l > 1){
        int m = (l + r) >> 1;
        mergeSort(a, l, m);
        mergeSort(a, m, r);
        merge(a, l, m, r);
    }
}

inline int swap(int& a, int& b){
    if (b < a){
        int tmp = a;
        a = b;
        b = tmp;
    }
}
inline int min(int a, int b) { return a < b ? a : b; }

/* above class and functions are utilities, directed copied 
from my library (to avoid wasting time trying to upload 
the library header file) */

//init all global var
#define maxN 100050

int* disc = new int[maxN];
int* low = new int[maxN];
List<int> **adj = new List<int>*[maxN]; //stores all edges
int* stA = new int[maxN]; //stack a
int* stB = new int[maxN]; //stack b, using two stacks to record bridges
int* path = new int[maxN]; //is the answer essentially
int lastBcc;

int stK = 0; // (index of last element in stA) + 1 == stA.size()
int pathK = 0;  // == path.size()
int curTime = 0;  
int n, m;

//print the stack, for debugging
void showStack(){
    printf("stack:\n# ");
    for (int i = 0; i < stK; i++){
        printf("%d ", stA[i]);
    }
    printf("\n# ");
	for (int i = 0; i < stK; i++){
        printf("%d ", stB[i]);
    }
    printf("\n");
}

//push into stack
void stPush(int a, int b){
	stA[stK] = a;
	stB[stK++] = b;
}

void tarjan(int cur, int dest, int prev){
    disc[cur] = low[cur] = ++curTime;

    ListNode<int>* adjNode = adj[cur]->getFirst();
    for (; adjNode != adj[cur]->getTail(); adjNode = adjNode->next){
        int next = adjNode->val();
        if (next == prev) continue;

        if (!disc[next]){ //undiscovered
            stPush(cur, next);
			//showStack();
            tarjan(next, dest, cur);

            low[cur] = min(low[cur], low[next]);

            //if cur is articulation point
            if (disc[cur] <= low[next]) {
				bool flag = false; //used to check if lastBcc is a part of the BCC found
				if (stB[stK-1] == lastBcc) 
					flag = true;
                while (stA[--stK] != cur){
                    if (stA[stK] == lastBcc || stB[stK] == lastBcc) 
						flag = true;
                }
				if (flag){
                	path[pathK++] = cur;
					lastBcc = cur;
				}
            }
        }
        else { //discovered
            low[cur] = min(low[cur], disc[next]);
        }
    }
}

//set initial values for tarjan
void tarjanInit(int start, int end){
    pathK = 0;
    curTime = 1;
    stK = 1;
    stA[0] = stB[0] = 0;
	lastBcc = end;
    for (int i = 0; i < maxN; i++) {
        disc[i] = 0;
        low[i] = 0;
    }
}

//for printing out the answer that was returned by tarjan in int* path
void showAns(){
    mergeSort(path, 0, pathK);
    printf("%d ", path[0]);
    for (int i = 1; i < pathK; i++){ 
        while (path[i] == path[i-1] && i < pathK) i++;
        if (i >= pathK) break;
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main(){
    int a, b, q;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++){
        low[i] = disc[i] = stA[i] = 0;
        adj[i] = new List<int>;
    }

    for (int i = 0; i < m; i++){
        scanf("%d %d", &a, &b);
        adj[a]->pushBack(b);
        adj[b]->pushBack(a);
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++){
        scanf("%d %d", &a, &b);
        tarjanInit(a, b); 
        tarjan(a, b, -1); //O(n + m)

        //add the start and destination to path
        path[pathK++] = a;
        path[pathK++] = b;
        showAns(); // O(nlogn), print out art. nodes stored in path
    }

	//free up memory
    delete adj;
    delete disc;
    delete low;
    delete stA;

    return 0;
}
