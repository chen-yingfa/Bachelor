#include <iostream>
#include "employee.h"
using namespace std;

int main() {
	Employee employees[4];

	employees[0].setInidividualEmpNo(1);
	employees[0].setGrade(8);
	employees[0].setAccumPay(12000);

	employees[1].setInidividualEmpNo(2);
	employees[1].setGrade(7);
	employees[1].setAccumPay(8000);

	employees[2].setInidividualEmpNo(3);
	employees[2].setGrade(6);
	employees[2].setAccumPay(10000);

	employees[3].setInidividualEmpNo(4);
	employees[3].setGrade(10);
	employees[3].setAccumPay(1000000);

	for (int i = 0; i < 4; i++) {
		employees[i].displayData();
	}

	system("pause");
	return 0;
}