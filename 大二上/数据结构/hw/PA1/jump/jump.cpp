#include <cstdio>
#define ll unsigned long long int

using namespace std;

int main(){
	int n;
	scanf("%d", &n);

	ll* l;
	ll* r;
	ll* t;
	ll* sol;
	bool* visited;

	l = new ll[n];
	r = new ll[n];
	t = new ll[n];
	sol = new ll[n];
	visited = new bool[n];

	for (int i = 1; i < n; i++){
		scanf("%d %d %d", &l[i], &r[i], &t[i]);
		visited[i] = false;
	}
	visited[1] = true;
	sol[1] = 0;

	for (int i = 1; i < n; i++){
		if (!visited[i])
			continue;

		ll time = sol[i] + t[i];

		for (int j = l[i]; j <= r[i]; j++){
			if (!visited[j] || sol[j] > time){
				sol[j] = time;
			}
			visited[j] = true;
		}
		/*
		for (int k = 1; k <= n; k++){
			printf("%u ", sol[k]);
		}
		printf("\n");
		for (int k = 1; k <= n; k++){
			printf("%u ", visited[k]);
		}
		printf("\n");
		*/
}

	printf("%lld\n", sol[n]);

	delete l;
	delete r;
	delete t;
	delete sol;

	return 0;
}
