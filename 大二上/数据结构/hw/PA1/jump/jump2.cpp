#include <iostream>
#include <cstdio>

using namespace std;

int main(){
    const long long int inf = 10e15;
    const int N = 10e6 +1;
    long long int* dp = new long long int[N];
    dp[1] = 0;
    for (int i = 2; i < N; i++)
        dp[i] = inf;
    int n, l, r, t, prevL = 2;

    scanf("%d", &n);

    for (int i = 1; i < n; i++){
        scanf("%d %d %d", &l, &r, &t);
        for (int j = l; j <= r; j++){
            if (dp[i] + t < dp[j]){
                dp[j] = dp[i] + t;
            }
        }
        for (int j = 1; j <= n; j++){
            printf("%d ", dp[j]);
        }
        printf("\n");
    }
    printf("%lld\n", dp[n]);

    return 0;
}