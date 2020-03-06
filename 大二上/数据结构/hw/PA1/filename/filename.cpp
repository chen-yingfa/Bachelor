#include <iostream>
#include <iomanip>
#include <string> //usable
using namespace std;

int main(){
    int maxN = 501000;
    int INF = 99;
    int dp[maxN + 1];
    string a, b;
    int n, m, k;
    cin >> n >> m >> k;
    cin >> a >> b;

    for (int i = 0; i <= k; i++){
        dp[i] = i;
    }
    dp[k+1] = INF;

    int prev;
    /*
    cout << "   n/a";
    for (int j = 0; j < m; j++){
        cout << setw(3) << b[j];
    }
    cout << endl << "n/a";
    for (int j = 0; j <= m; j++){
        cout << setw(3) << dp[j];
    }
    cout << endl;
    */

    for (int i = 1; i <= n; i++){
        //cout << setw(3) << a[i-1];
        int j = i - k;
        if (j <= 0){
            prev = dp[0]++;
            j = 1;
        } else {
            prev = dp[j - 1];
            dp[j - 1] = INF;
        }
        /*
        for (int k = 0; k < j; k++){
            cout << setw(3) << dp[k];
        }
        */
        while(j <= m && j <= i + k){
            if (a[i-1] == b[j-1]){
                int tmp = dp[j];
                dp[j] = prev;
                prev = tmp;
            } else {
                prev = dp[j];
                dp[j] = (dp[j-1] < dp[j]? dp[j-1] : dp[j]) + 1;
            }
            //cout << setw(3) << dp[j];
            j++;
        }
        if (j <= m){
            dp[j] = INF;
            //cout << setw(3) << dp[j];
        }
        //cout << "\n";
    }
    if (dp[m] > k)
        cout << "-1\n";
    else
        cout << dp[m] << "\n";
    return 0;
}
