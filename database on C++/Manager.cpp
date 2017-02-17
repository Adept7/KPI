/*!
* file: Manager.cpp
* written: 09/05/2016
* synopsis: Manager class implementation
*/
#include "Manager.h"
#include <iterator>
#include <iomanip> 

Manager::Manager(const Manager &m) {
	f_name = m.f_name;
	l_name = m.l_name;
	age = m.age;
	salary = m.salary;
	department = m.department;
	id = m.id;
	subordinates = m.subordinates;
};

Manager& Manager::operator=(const Manager &m) {
	f_name = m.f_name;
	l_name = m.l_name;
	age = m.age;
	salary = m.salary;
	department = m.department;
	id = m.id;
	subordinates = m.subordinates;
	return *this;
};

void Manager::Display(bool b) {
	if (!b) {
		cout << "Employment type: manager" << endl;
		cout << "id: " << id << endl;
		cout << f_name << " " << l_name << "    age: " << age << "    salary " << salary << endl;
		cout << "department: " << department << endl;
	}
	else {
		cout << "\t" << "Employment type: manager" << endl;
		cout << "\t" << "id: " << id << endl;
		cout << "\t" << f_name << " " << l_name << "    age: " << age << "    salary " << salary << endl;
		cout << "\t" << "department: " << department << endl;
	}
};

void Manager::AddSubordinate(Person *p) {
	bool uniq = true;
	if (dynamic_cast<Employee*>(p)->GetDepartment() != "")
		if ((typeid(*p) == typeid(Employee)) &&
			(dynamic_cast<Employee*>(p)->GetDepartment() == this->GetDepartment())) {
			for (list<Person *>::iterator it = subordinates.begin(); it != subordinates.end(); ++it)
				if (dynamic_cast<Employee*>(*it) == p) {
					uniq = false;
					break;
				}
		}
		else
			uniq = false;

	if (uniq == true)
		subordinates.push_back(p);
};

void Manager::DisplaySubordinates() {
	cout << "Subordinates:" << endl;
	if (subordinates.size() != 0)
		for (list<Person *>::iterator it = subordinates.begin(); it != subordinates.end(); ++it)
			(*it)->Display(true);
	else
		cout << "\t none" << endl << endl << endl;
};

void Manager::Fire(int b) {
	for (list<Person *>::iterator it = subordinates.begin(); it != subordinates.end(); ++it)
		if (dynamic_cast<Employee*>(*it)->GetId() == b) {
			subordinates.remove(*it);
			break;
		}
};