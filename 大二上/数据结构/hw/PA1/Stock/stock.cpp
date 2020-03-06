#include <cstdio>
const int MAX = 1000050;

class Queap {
private:
    long long int* arr = nullptr;
    long long int* cnt = nullptr;
    int size = 0;
    int head = 0;
    int tail = 0;
public:
	Queap(int len){
		arr = new long long int[MAX];
		cnt = new long long int[MAX];
        for (int i = 0; i < MAX; i++){
            arr[i] = 0;
            cnt[i] = 0;
        }
	}
    void pop(){
    	//printf("pop()\n");
        if (size == 0)
            throw 1;

        if (cnt[head] == 1)
            head++;
        else if (cnt[head] > 1)
            cnt[head]--;

        size--;
    }

    void push(int n){
    	//printf("push(%d)\n", n);
        if (size == 0){
            head = 0;
            tail = 1;
            cnt[head] = 1;
            arr[head] = n;
        } else {
            if (arr[tail-1] <= n){
                int tmpCnt = 1;
                while (head < tail && arr[tail-1] <= n){
                    tmpCnt += cnt[tail-1];
                    tail--;
                }
                arr[tail] = n;
                cnt[tail] = tmpCnt;
                tail++;
            } else {
                arr[tail] = n;
                cnt[tail] = 1;
                tail++;
            }
        }
        size++;
    }

    int getMax(){
        return (size ? arr[head] : 0);
    }

    void show(){
        printf("{");
        for (int i = head; i < tail; i++){
            printf("(%d, %d),", cnt[i], arr[i]);
        }
        printf("}\n");
    }
};

int main(){
    long long int n = 0, d = 0, x = 0, ans = 0;
    char c = getchar();
    while ('0' <= c && c <= '9'){
        n = n * 10  + c -'0';
        c = getchar();
	}

    Queap queap(n);
    for (int i = 0; i < 2 * n; i++){
        d = 0;
        c = getchar();
        while ('0' <= c && c <= '9'){
            d = d * 10 + c - '0';
            c = getchar();
        }

        if (c == ' '){
            x = 0;
            c = getchar();
            while ('0' <= c && c <= '9'){
                x = x * 10 + c - '0';
                c = getchar();
			}
            ans += d * queap.getMax();
            //printf("ans += %d\n", d * queap.getMax());
            queap.push(x);
        } else {
            ans += d * queap.getMax();
            //printf("ans += %d\n", d * queap.getMax());
            queap.pop();
        }
        //queap.show();
    }

    printf("%lld\n", ans);
    return 0;
}
