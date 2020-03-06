#include <iostream> 
using namespace std;
#ifndef PRISM_H
#define PRISM_H

class Prism {
private:
	int length, height, width;
public:
	void getData(){
		cout << "请输入 <长> <宽> <高>（空格隔开)：";
		cin >> length >> width >> height;
	}
	int	getVolume(){
		return length * width * height;
	}
};

#endif
