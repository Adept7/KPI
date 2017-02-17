/*!
* file: Employee.cpp
* written: 09/05/2016
* synopsis: Employee class implementation
*/
#include "Employee.h"

Employee::Employee(const Employee &e) {
	if (&e != NULL) {
		f_name = e.f_name;
		l_name = e.l_name;
		age = e.age;
		salary = e.salary;
		department = e.department;
		id = e.id;
	};
};

Employee& Employee::operator=(const Employee &e) {
		f_name = e.f_name;
		l_name = e.l_name;
		age = e.age;
		salary = e.salary;
		department = e.department;
		id = e.id;
	return *this;
};

void Employee::SetSalary(int s) {
	salary = s;
};

void Employee::SetDepartment(string dept) {
	department = dept;
};

void Employee::SetId(int n) {
	id = n;
};

int Employee::GetId() {
	return this->id;
};

string Employee::GetDepartment() {
	return department;
};

void Employee::Display(bool b) {
	if (!b) {
		cout << "Employment type: employee" << endl;
		cout << "id: " << id << endl;
		cout << f_name << " " << l_name << "    age: " << age << "    salary " << salary << endl;
		cout << "department: " << department << endl << endl << endl;
	}
	else {
		cout << "\t" << "Employment type: employee" << endl;
		cout << "\t" << "id: " << id << endl;
		cout << "\t" << f_name << " " << l_name << "    age: " << age << "    salary " << salary << endl;
		cout << "\t" << "department: " << department << endl << endl << endl;
	}
};