#include <iostream>
#include "student.h"
using namespace std;


int main(){
	Student students[5];
	float gpa[] = {3.423, 3.136, 4.0, 2.9587, 2.364};
	for (int i = 0; i < 5; i++){
		students[i].studID = 2018080073 + i;
		students[i].gpa = gpa[i];
	}
	
	Student* s = &(students[0]);
	
	s->showData();
	(s+2)->showData();
	(s+4)->showData();
	
	
	return 0;
}
