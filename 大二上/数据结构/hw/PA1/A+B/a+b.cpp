#include <cstdio>
#include <cstring>
#include <cmath>

const double PI = 3.1415926536;
const int LOGLEN = 14;
const int LEN = 1 << LOGLEN;
int rev[LEN];

class Z {
public:
	double x, y; //x = re, y = im
	Z(double xx = 0, double yy = 0){
		x = xx;
		y = yy;
	}
	Z operator-(Z &c){
		return Z(x - c.x, y - c.y);
	}
	Z operator+(Z &c){
		return Z(x + c.x, y + c.y);
	}
	Z operator*(Z &c){
		return Z(x * c.x - y * c.y, x * c.y + y * c.x);
	}
};

void change(Z arr[], int len){
	int i, j, k;
    for (i = 1, j = len >> 1; i < len - 1; i++){
        if (i < j){
            Z tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
        }
        k = len >> 1;
        while (j >= k){
            j -= k;
            k >>= 1;
        }
        if (j < k)
            j += k;
    }
}

void fft(Z a[], int len, int inv){
	change(a, len);
	
	for (int size = 1; size < len; size <<= 1){
		Z wn(cos(PI / size), inv * sin(PI / size)); // e ^(PI * i / size)
		
		for (int i = 0; i < len; i += size << 1){
			Z wnk(1, 0);
			
			for (int j = i; j < i + size; j++){
				Z a1 = a[j];
				Z a2 = wnk * a[j + size];
				
				a[j] = a1 + a2;
				a[j + size] = a1 - a2;
				
				wnk = wnk * wn;
			}
		}
	}
	
	if (inv == -1){
		for (int i = 0; i < len; i++){
			a[i].x /= len;
		}
	}
}

int main(){
	int n;
	Z a[LEN];
	Z b[LEN];
	int F[LEN + 1];
	scanf("%d", &n);
	
	while (n--){
		char aStr[LEN], bStr[LEN];
		scanf("%s %s", aStr, bStr);
		int lenA = strlen(aStr);
		int lenB = strlen(bStr);
		int curLen = 1;
		while (curLen < lenA << 1 || curLen < lenB << 1)
			curLen <<= 1;
		
		for (int i = 0; i < lenA; i++) 
			a[i] = Z(aStr[lenA - 1 - i] - '0');
		for (int i = lenA; i < curLen; i++)
			a[i] = Z(0, 0);
		for (int i = 0; i < lenB; i++)
			b[i] = Z(bStr[lenB - 1 - i] - '0');
		for (int i = lenB; i < curLen; i++)
			b[i] = Z(0, 0);
		
		fft(a, curLen, 1);
		fft(b, curLen, 1);
		
		for (int i = 0; i < curLen; i++){
			a[i] = a[i] * b[i];
		}
		
		fft(a, curLen, -1);
		
		F[0] = 0;
		for (int i = 0; i < curLen; i++){
			F[i] += (int) (a[i].x + 0.5);
			F[i + 1] = F[i] / 10;
			F[i] %= 10;
		}
		
		int i = lenA + lenB - 1;
		while (F[i] <= 0 && i >= 0) i--;
		if (i < 0) {
			printf("0");
		}
		
		for (; i >= 0; i--){
			printf("%d", F[i]);
		}
		printf("\n");
	}
	
	return 0;
}
