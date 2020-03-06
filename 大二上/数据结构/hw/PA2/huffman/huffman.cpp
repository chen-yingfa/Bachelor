#include <cstdio>

//Huffman 树中的节点
class Node {
public:
    int f = 0, r = 0; //freqency (of the char) and rank (of the node in the tree)
    //NB: rank is also the length of path
    Node *lc = nullptr, *rc = nullptr;
    Node *par = nullptr;

    ~Node(){
        if (lc) delete lc;
        if (rc) delete rc;
    }

    //用于输出答案
    void showPath(){
        if (r == 0) return;
        par->showPath();
        printf("%d", isLc() ? 0 : 1);
    }

    //此节点是否一个左孩子
    bool isLc(){
        return par->lc == this;
    }

    void incrR(){
        if (lc && rc) { 
            lc->incrR();
            rc->incrR();
        }
        r++;
    }
};

class HuffTree {
public:
    Node* nodes[26]; //其实是字符对应的（叶子）节点
    Node* heap[30]; //直接用数组即可，因为这个程序要求很简陋
    int heapK = 0; //堆的大小

    //推进堆
    void pushHeap(Node* n){
        for (int i = 0; i < heapK; i++){
            if (n->f > heap[i]->f){
                for (int j = heapK; j > i; j--){
                    heap[j] = heap[j-1];
                }
                heap[i] = n;
                heapK++;
                return;
            }
        }
        heap[heapK++] = n;
    }

    //合并两个节点
    void merge(){
        Node* a = heap[heapK-2];
        Node* b = heap[heapK-1];
        Node* tmp = new Node;
        tmp->lc = a;
        tmp->rc = b;
        a->par = tmp;
        b->par = tmp;
        tmp->f = a->f + b->f;
        a->incrR(); //被合并的节点的rank++
        b->incrR();
        tmp->r = 0;
        heapK-=2;
        //合并完就重新推进堆里
        pushHeap(tmp);
    }

    //输出每个字符的编码答案
    void showAns(){
        int sum = 0;
        for (int i = 0; i < 26; i++){
            sum += nodes[i]->f * nodes[i]->r;
        }
        printf("%d\n", sum);
        for (int i = 0; i < 26; i++){
            if (nodes[i]->f) {
                printf("%c ", 'a' + i);
                nodes[i]->showPath();
                printf("\n");
            }
        }
    }
};

int main(){
    int len = 0; //the length of the string
    int existChar[26] = {}; //all different existing characters stored in a stack
    int existK = 0; //num of different characters existing in the string
    char c = getchar();
    HuffTree ht;

    for (int i = 0; i < 26; i++){
        ht.nodes[i] = new Node;
    }

    //getting input
    while ('a' <= c && c <= 'z'){
        if (ht.nodes[c - 'a']->f == 0) {
            existChar[existK++] = c - 'a';
        }
        ht.nodes[c - 'a']->f++;
        len++;
        c = getchar();
    }

    if (existK == 1){ //if string contains only one type of character
        //只有一个字符时，构建树会有错误
        printf("%d\n", len);
        printf("%c 0", existChar[0] + 'a');
    }
    else {
        for (int i = 0; i < 26; i++){
            if (ht.nodes[i]->f) ht.pushHeap(ht.nodes[i]); //将所有叶子推进堆里
        }
        //构建 huffman 树
        while (ht.heapK > 1) {
            ht.merge();
        }
        ht.showAns();
    }

    //释放空间
    delete ht.heap[0];

    return 0;
}
