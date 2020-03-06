#include <iostream>
using namespace std;
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
private:
	int individualEmpNo;
	int grade;
	int accumPay;
public:
	void displayData() {
		cout << "Employee No.: " << individualEmpNo << endl;
		cout << "Grade:        " << grade << endl;
		cout << "Accum. Pay:   " << accumPay << endl;
	}

	void setInidividualEmpNo(int n) {
		individualEmpNo = n;
	}
	int getIndividualEmpNo() {
		return individualEmpNo;
	}

	void setGrade(int n) {
		grade = n;
	}
	int getGrade() {
		return grade;
	}

	void setAccumPay(int n) {
		accumPay = n;
	}
	int getAccumPay() {
		return accumPay;
	}
};

#endif