#include <cstdio>

template<class T> T max(T a, T b){
    return a < b ? b : a;
}
int max(int a, int b){
    return a < b ? b : a;
}
double max(double a, double b){
    return a < b ? b : a;
}
template<class T> T min(T a, T b){
    return a > b ? b : a;
}
int min(int a, int b){
    return a > b ? b : a;
}
double min(double a, double b){
    return a > b ? b : a;
}

bool isPrime(int n){
    if (n % 2 == 0) return false;
    for (int i = 3; i*i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

int gcd(int a, int b){
    return a ? gcd(b % a, a) : b;
}
int lcm(int a, int b){
    return a / gcd(a, b) * b;
}
int binToDec(int n){
    
}
int decToBin(int n){
    
}


void print(int a[], int l, int r, bool endl = true){
    printf("{");
    for (int i = l; i < r - 1; i++){
        printf("%d, ", a[l + i]);
    }
    printf("%d}, size=%d\n", a[r-1], r - l);
}
template<class T> void swap(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}

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
