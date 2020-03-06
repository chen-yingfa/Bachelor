#include <cstdio>

//位置坐标
class Pos {
public:
    int x, y; //x = 行（上往下），y = 列（左往右）
    Pos add(Pos b) {
        return {x + b.x, y + b.y};
    }
};

Pos adj[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //上下左右的相对坐标
const int maxN = 1010, maxM = 1010; //m 和 n 的上限
int n, m;

//队列，用于BFS
class Q {
public:
    int *qx, *qy; //x和y坐标分成两个数组是为了避免数组太大，申请空间失败
    int qa = 0, qb = 0; //队列的前后坐标 [qa, ..., qb), 注：不包含qb

    Q (int n) {
        qx = new int[n];
        qy = new int[n];
    }

    void push(Pos p) { //insert
        qx[qb] = p.x;
        qy[qb] = p.y;
        qb++;
    }
    Pos pop() { //remove
        qa++;
        return {qx[qa-1], qy[qa-1]};
    }
    bool empty() {
        return qa == qb;
    }
};

int main() {
    int** mat = new int*[maxN];
    for (int i = 0; i < maxN; i++) {
        mat[i] = new int[maxM];
    }
    bool vis[maxN][maxM];
    Q qu(maxN * maxM);
    long long int sum = 0;
    char line[1010];
    char c = '\n';
    
    //存储输入，比较复杂是为了鲁棒性
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        while (c != '1' && c != '0') c = getchar(); //跳过所有非‘1’，‘0’字符（为了鲁棒性）
        int j = 0;
        while (c == '1' || c == '0') {
            if (c == '0') {
                qu.push({i, j});
                mat[i][j] = 0;
                vis[i][j] = true;
            }
            else {
                mat[i][j] = 1;
                vis[i][j] = false;
            }
            c = getchar();
            j++;
        }
    }

    while (!qu.empty()) {
        Pos cur = qu.pop();
        // 循环上下左右四个坐标
        for (int i = 0; i < 4; i++) {
            Pos next = cur.add(adj[i]);
            if (next.x < 0 || n <= next.x || next.y < 0 || m <= next.y) continue; //若出界
            if (vis[next.x][next.y]) continue; //已经访问过
            vis[next.x][next.y] = true;               //设为已访问
            mat[next.x][next.y] = mat[cur.x][cur.y] + 1;//步数+1
            sum += mat[next.x][next.y];               //添加至总步数
            qu.push(next);                            //推进队列
        }
    }

    printf("%d\n", sum); //输出结果

    //释放空间
    for (int i = 0; i < maxN; i++){
        delete[] mat[i];
    }
    delete[] mat;

    return 0;
}







