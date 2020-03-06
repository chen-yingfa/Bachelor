#include <iostream>
#include "prism.h"
using namespace std;

int main() {
	Prism a, b, c;
	a.getData();
	cout << a.getVolume() << endl;
	b.getData();
	cout << b.getVolume() << endl;
	c.getData();
	cout << c.getVolume() << endl;
	
	system("pause");
	return 0;
}
