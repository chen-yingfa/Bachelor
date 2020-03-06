#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
using namespace std;

class Student {
public:
	int studID;
	float gpa;
public:
	showData(){
		cout << studID << ": " << gpa << endl;
	}
};

#endif 
