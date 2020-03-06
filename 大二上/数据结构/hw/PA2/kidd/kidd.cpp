#include <cstdio>

typedef long long int ll;

//merge sort algorithm, copied from a small library written by myself for reuse,
//pasted here to avoid having to zip files everytime I submit a new code.
template<class T> void merge(T a[], int l, int m, int r){
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

template<class T> void mergeSort(T a[], int l, int r){
    if (r - l > 1){
        int m = (l + r) >> 1;
        mergeSort(a, l, m);
        mergeSort(a, m, r);
        merge<T>(a, l, m, r);
    }
}

//线段树的节点
class Node{
public:
    ll cnt = 0; //count of number of times this interval has been flipped
    ll left, right; //the left and right side index of this interval, inclusive

    Node(ll l = 0, ll r = 0){
        left = l;
        right = r;
    }
    
    void set(ll l, ll r){
        left = l;
        right = r;
    }

    void h(){
        cnt += len();
    }

    ll len(){
        return right - left + 1;
    }
};

//stores binary tree in a 1d array
Node** nodes; //stores all nodes as pointers, just for convenience
ll* lazy; //懒惰标记

//线段树 (segment tree)
class IntTree{
public:
    ll two;

    //query 查询, 直接用课上讲解的方法
    ll q(int idx, ll left, ll right){
        if (right < nodes[idx]->left || nodes[idx]->right < left)
            return 0;
        else if (left <= nodes[idx]->left && nodes[idx]->right <= right)
            return nodes[idx]->cnt;

        if (lazy[idx] > 0) pushDown(idx);

        ll ret = 0;
        return q(2*idx, left, right) + q(2*idx + 1, left, right);
    }

    // 挥手，翻 [left, right] 的牌子,注：包含
    void h(int idx, ll left, ll right){
        if (right < nodes[idx]->left || nodes[idx]->right < left)
            return;

        //printf("updating [%d, %d]\n", nodes[idx]->left, nodes[idx]->right);
        if (left <= nodes[idx]->left && nodes[idx]->right <= right) {
            nodes[idx]->h(); //this will stop at leaf
            lazy[idx]++;
            return;
        } 
        if (lazy[idx] > 0) pushDown(idx);
        h(2*idx, left, right);
        h(2*idx+1, left, right);
        nodes[idx]->cnt = nodes[2*idx]->cnt + nodes[2*idx+1]->cnt;
    }

    //懒惰标记的一部分，挥手或者查询时，如果经过某节点有懒惰标记非零，就将标记往下推
    void pushDown(int k){
        if (lazy[k] > 0){
            lazy[2*k] += lazy[k];
            lazy[2*k+1] += lazy[k];
            nodes[2*k]->cnt += nodes[2*k]->len() * lazy[k];
            nodes[2*k+1]->cnt += nodes[2*k+1]->len() * lazy[k];
            lazy[k] = 0;
        }
    }

    //using 1d array to store the binary tree, and this function is computing
    //the length of the array requires to store the nodes, which is 2 
    //multiplied with the a power of two that is larger than 2 * m
    ll getTwo(int m){
        two = 1;
        while (two < 2 * m) two *= 2;
        return two*=2;
    }
};

int main(){
    IntTree tree;
    ll n, m;
    scanf("%d %d", &n, &m);
    char* op = new char[m];
    ll* L = new ll[m];
    ll* R = new ll[m];
    ll* l = new ll[m];
    ll* r = new ll[m];
    int leafStart, leafEnd;

    ll two = tree.getTwo(m);

    nodes = new Node*[two]; //store binary tree in a 1d array
    lazy = new ll[two];

    for (int i = 0; i < two; i++) lazy[i] = 0;
    leafStart = two / 2;

    //getting all input
    for (int i = 0; i < m; i++){
        scanf(" %c %d %d", &op[i], &l[i], &r[i]);
        L[i] = l[i];
        R[i] = r[i];
    }
    //sort the input in order to find elementary intervals
    mergeSort<ll>(l, 0, m);
    mergeSort<ll>(r, 0, m);

    //now set the leaves of the segment tree as the elementary intervals
    int i = 0, j = 0;
    leafEnd = leafStart;
    ll left = 0, right;
    while (i < m && j < m){
        if (l[i] <= r[j]) right = l[i++] - 1;
        else right = r[j++];
        
        nodes[leafEnd++] = new Node(left, right);

        left = right+1;
        while (l[i] <= left) i++;
        while (r[j] < left) j++;
    }
    while (i < m){
        while (l[i] <= left) i++;
        right = l[i++] - 1;
        nodes[leafEnd++] = new Node(left, right);
        left = right + 1;
    }
    while (j < m){
        while (r[j] < left) j++;
        right = r[j++];
        nodes[leafEnd++] = new Node(left, right);
        left = right +1;
    }
    //tree might now be exactly a power of two, meaning some nodes are 
    //still not initiated, so add dummy nodes to fill in to make sure
    //all leaves are on the same level
    while (leafEnd < two){
        nodes[leafEnd++] = new Node(left, left);
    }

    //now that we have all leaves set, contruct the segment tree by merging
    //two and two nodes upwards
    for (int lvlEnd = leafStart; lvlEnd > 1; lvlEnd /= 2){
        int lvlStart = lvlEnd / 2;
        for (int i = lvlStart; i < lvlEnd; i++){
            nodes[i] = new Node(nodes[i * 2]->left, nodes[2*i + 1]->right);
        }
    }

    //now, process the different operations, 挥手 and 查询
    for (int i = 0; i < m; i++){
        if (op[i] == 'H'){ // 挥手
            tree.h(1, L[i], R[i]);
        }
        else if (op[i] == 'Q'){ //查询
            printf("%lld\n", tree.q(1, L[i], R[i]));
        }
    }

    //释放空间
    delete l;
    delete r;
    delete L;
    delete R;
    delete op;
    delete nodes;
    delete lazy;
    return 0;
}
