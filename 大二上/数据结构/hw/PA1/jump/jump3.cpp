#include <cstdio>

#define inf 10e15

int main(){
    int maxN = 10e6+1;
    int n, head = 0, tail = 0, next = 1, left, right, prevLeft = 1;
    int *l, *r, *L, *R, *t, *cnt;


    scanf("%d", &n);
    maxN = n + 1;
    
    long long int* dp = new long long int[maxN];
    long long int* q = new long long int[maxN];
    cnt = new int[maxN];

    r = new int[maxN];
    l = new int[maxN];
    t = new int[maxN];


    for (int i = 1; i < n; i++)
        scanf("%lld %lld %lld", &l[i], &r[i], &t[i]);
    t[n] = 0;


    for (int i = 0; i <= n; i++){
        dp[i] = inf;
        cnt[i] = 0;
    }

    dp[1] = t[1];
    cnt[0] = 1;
    q[0] = t[1];
    head = tail = 0;

    int jl = 1, jr = 1;
    for (int i = 2; i <= n; i++){
        while (r[jr] < i && jr < n) jr++;
        left = jr;
        while (l[jl] <= i && jl < n) jl++;
        right = jl - 1;

        if (right < left) continue;


        while (next < right){
            next++;
            if (q[tail] < dp[next]){
                cnt[++tail] = 1;
                q[tail] = dp[next];
            }
            else if (q[tail] == dp[next]){
                cnt[tail]++; 
            }
            else {
                int newCnt = 1;
                while (q[tail] > dp[next] && tail >= head){
                    newCnt += cnt[tail--];
                }
                cnt[++tail] = newCnt;
                q[tail] = dp[next];
            }
        }
        
        for (int j = prevLeft; j < left; j++){
            if (cnt[head] > 1)
                cnt[head]--;
            else 
                head++;
        }
        prevLeft = left;
        

        dp[i] = q[head] + t[i];


    }
    printf("%lld\n", dp[n]);

    delete l;
    delete r;
    delete t;
    delete q;
    delete cnt;
    delete dp;

    return 0;
}