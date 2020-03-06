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
	Employee(int individualEmpNo = 0, int grade = 0, int accumPay = 0){
		this->individualEmpNo = individualEmpNo;
		this->grade = grade;
		this->accumPay = accumPay;
	}
	
	~Employee(){
		cout << "欢迎使用，再见" << individualEmpNo << endl; 
	}
	
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
