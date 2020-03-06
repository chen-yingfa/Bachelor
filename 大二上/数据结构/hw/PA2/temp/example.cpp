#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "temperature.h"

using namespace std;


struct Node
{
	int x;
	int y;
	int t;
	int x_index;
	int y_index;
};
int compy(const void* x, const void* b)
{
	return (*(Node*)x).y > (*(Node*)b).y ? 1 : -1;
}
int compx(const void* x, const void* b)
{
	return (*(Node*)x).x > (*(Node*)b).x ? 1 : -1;
}

Node a[200005];
int an = 0;

class Range
{
public:
	int fromx;
	int fromy;
	int tox;
	int toy;
	int isx;

	int maxt;
	int mint;

	Range* left_child;
	Range* right_child;
	Range(int fromx, int fromy, int tox, int toy, int isx)
	{
		this->fromx = fromx;
		this->fromy = fromy;
		this->tox = tox;
		this->toy = toy;
		this->isx = isx;
		this->left_child = NULL;
		this->right_child = NULL;
		this->maxt = -1;
		this->mint = -1;
		/*
		if (this->fromx == this->tox)
		{
			this->isx = 0;
		}
		if (this->fromy == this->toy)
		{
			this->isx = 1;
		}
		*/
	}
};

Range* root = NULL;
int cnt = 0;

void insert(Range * cur, int x, int y, int t)
{
	if (cur == NULL)
	{
		return;
	}
	if (cur->mint == -1 || cur->mint > t)
	{
		cur->mint = t;
	}
	if (cur->maxt == -1 || cur->maxt < t)
	{
		cur->maxt = t;
	}
	if (cur->fromx == x && cur->tox == x && cur->fromy == y && cur->toy == y)
	{
		return;
	}
	if (cur->isx)
	{
		if (cur->fromx == cur->tox)
		{
			if (cur->left_child == NULL)
			{
				cur->left_child = new Range(cur->fromx, cur->fromy, cur->tox, cur->toy, (cur->isx + 1) % 2);
				cur->right_child = cur->left_child;
			}
			insert(cur->left_child, x, y, t);
		}
		else
		{
			//int midx = ((long long)cur->tox - (long long)cur->fromx) / 2 + (long long)cur->fromx;
			int midx = (cur->fromx + cur->tox) / 2;
			if (cur->fromx <= x && x <= midx)
			{
				if (cur->left_child == NULL)
				{
					cur->left_child = new Range(cur->fromx, cur->fromy, midx, cur->toy, (cur->isx + 1) % 2);
				}
				insert(cur->left_child, x, y, t);
			}
			else
			{
				if (cur->right_child == NULL)
				{
					cur->right_child = new Range(midx + 1, cur->fromy, cur->tox, cur->toy, (cur->isx + 1) % 2);
				}
				insert(cur->right_child, x, y, t);
			}
		}
	}
	else
	{
		if (cur->fromy == cur->toy)
		{
			if (cur->left_child == NULL)
			{
				cur->left_child = new Range(cur->fromx, cur->fromy, cur->tox, cur->toy, (cur->isx + 1) % 2);
				cur->right_child = cur->left_child;
			}
			insert(cur->left_child, x, y, t);
		}
		else
		{
			//int midy = ((long long)cur->toy - (long long)cur->fromy) / 2 + (long long)cur->fromy;
			int midy = (cur->fromy + cur->toy) / 2;
			if (cur->fromy <= y && y <= midy)
			{
				if (cur->left_child == NULL)
				{
					cur->left_child = new Range(cur->fromx, cur->fromy, cur->tox, midy, (cur->isx + 1) % 2);
				}
				insert(cur->left_child, x, y, t);
			}
			else
			{
				if (cur->right_child == NULL)
				{
					cur->right_child = new Range(cur->fromx, midy + 1, cur->tox, cur->toy, (cur->isx + 1) % 2);
				}
				insert(cur->right_child, x, y, t);
			}
		}
	}
}

int xs[600005] = { 0 };
int x_n = 0;
int ys[600005] = { 0 };
int y_n = 0;

int binary_search(int aa[], int aan, int aim)
{
	int l = 0;
	int r = aan - 1;
	int mid = ((l + r) >> 1);
	while (1)
	{
		if (l >= r)
			break;
		mid = ((l + r) >> 1);
		if (aa[mid] > aim)
		{
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	l -= 2;
	for (; l < aan; l++)
	{
		if (l >= 0)
		{
			if (aa[l] > aim)
			{
				return l - 1;
			}
		}
	}
	return l;
}

void init(int n, const int* x, const int* y, const int* t) {
	// nothing to init
	an = n;
	x_n = 0;
	y_n = 0;
//	root = new Range(-2147483647, -2147483647, 2147483647, 2147483647, 1);
	for (int i = 0; i < n; i++)
	{
		a[i].x = x[i];
		a[i].y = y[i];
		a[i].t = t[i];
	}
	
	qsort(a, an, sizeof(Node), compx);
	xs[x_n++] = -2147483647;
	for (int i = 0; i < an; i++)
	{
		if (xs[x_n - 1] != a[i].x)
		{
			xs[x_n] = a[i].x;
			a[i].x_index = x_n;
			x_n++;
		}
		else
		{
			a[i].x_index = a[i - 1].x_index;
		}
	}
	xs[x_n++] = 2147483647;

	ys[y_n++] = -2147483647;
	qsort(a, an, sizeof(Node), compy);
	for (int i = 0; i < an; i++)
	{
		if (ys[y_n - 1] != a[i].y)
		{
			ys[y_n] = a[i].y;
			a[i].y_index = y_n;
			y_n++;
		}
		else
		{
			a[i].y_index = a[i - 1].y_index;
		}
	}
	ys[y_n++] = 2147483647;

	root = new Range(0, 0, x_n, y_n, 1);
	for (int i = 0; i < n; i++)
	{
		insert(root, a[i].x_index, a[i].y_index, a[i].t);
	}
	

}

void search(Range * cur, int fromx, int fromy, int tox, int toy, int* tmin, int* tmax)
{
	if (cur == NULL)
		return;
	if (cur->mint >= *tmin && cur->maxt <= *tmax)
		return;
	if (cur->fromx == fromx && cur->fromy == fromy && cur->tox == tox && cur->toy == toy)
	{
		if (*tmin == -1 || *tmin > cur->mint)
		{
			*tmin = cur->mint;
		}
		if (*tmax == -1 || *tmax < cur->maxt)
		{
			*tmax = cur->maxt;
		}
	}
	else
	{
		if (cur->isx)
		{
			//int midx = ((long long)cur->tox - (long long)cur->fromx) / 2 + (long long)cur->fromx;
			int midx = (cur->fromx + cur->tox) / 2;
			if (tox <= midx)
			{
				search(cur->left_child, fromx, fromy, tox, toy, tmin, tmax);
			}
			else if (midx < fromx)
			{
				search(cur->right_child, fromx, fromy, tox, toy, tmin, tmax);
			}
			else
			{
				search(cur->left_child, fromx, fromy, midx, toy, tmin, tmax);
				search(cur->right_child, midx + 1, fromy, tox, toy, tmin, tmax);
			}
		}
		else
		{
			//int midy = ((long long)cur->toy - (long long)cur->fromy) / 2 + (long long)cur->fromy;
			int midy = (cur->fromy + cur->toy) / 2;
			if (toy <= midy)
			{
				search(cur->left_child, fromx, fromy, tox, toy, tmin, tmax);
			}
			else if (midy < fromy)
			{
				search(cur->right_child, fromx, fromy, tox, toy, tmin, tmax);
			}
			else
			{
				search(cur->left_child, fromx, fromy, tox, midy, tmin, tmax);
				search(cur->right_child, fromx, midy + 1, tox, toy, tmin, tmax);
			}
		}
	}
}

void query(int x1, int x2, int y1, int y2, int* tmin, int* tmax) {

	*tmin = -1;
	*tmax = -1;

	int x1_index = binary_search(xs, x_n, x1);
	if (xs[x1_index] != x1)
		x1_index++;
	int x2_index = binary_search(xs, x_n, x2);
	int y1_index = binary_search(ys, y_n, y1);
	if (ys[y1_index] != y1)
		y1_index++;
	int y2_index = binary_search(ys, y_n, y2);

	search(root, x1_index, y1_index, x2_index, y2_index, tmin, tmax);

	//search(root, x1, y1, x2, y2, tmin, tmax);


	/*
	*tmin = rand();
	*tmax = rand();
	*/
}


/*
5
3 3 4000
0 0 100
1 2 200
1 2 3000
2 5 200
0 0 0 0
-1 -1 -1 -1
0 2 0 2
1 3 2 3


*/
