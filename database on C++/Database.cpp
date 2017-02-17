/*!
* file: Database.cpp
* written: 09/05/2016
* synopsis: Database class implementation
*/
#include "Database.h"
#include <fstream>
#include <string>
bool Database::LoadFromFile(const char *file) {
	ifstream fread(file);
	char *f__name, *l__name, *dep;
	int i=1,
		j=0, age, id, salary, emp;
	
		f__name = (char*)malloc(sizeof(char) * 256);
		l__name = (char*)malloc(sizeof(char) * 256);
		dep = (char*)malloc(sizeof(char) * 256);

		if (fread.is_open()) {
			while (!fread.eof()) {
				fread >> emp;
				fread.get();
				fread >> id;
				fread.get();
				fread.getline(f__name, 256, ';');
				fread.getline(l__name, 256, ';');
				fread >> age;
				fread.get();
				fread.getline(dep, 256, ';');
				fread >> salary;
				if (emp == 0) {
					Employee* b = new Employee(f__name, l__name, age, id);
					b->SetDepartment(dep);
					b->SetSalary(salary);
					employees.push_back(b);
				}
				if (emp == 1) {
					Manager* b = new Manager(f__name, l__name, age, id);
					b->SetDepartment(dep);
					b->SetSalary(salary);
					employees.push_back(b);
				}
			};
		}
		else
			cout << "Error reading from file" << endl;
	free(f__name);
	free(l__name);
	free(dep);

	return true;
};

void Database::ArrangeSubordinates() {
	for (vector<Person*>::iterator(it) = employees.begin(); it != employees.end(); ++it) 
		if (typeid(**it) == typeid(Manager)) {

			for (vector<Person*>::iterator(it2) = employees.begin(); it2 != employees.end(); ++it2)
				if (typeid(**it2) == typeid(Employee)) {
					
					if (dynamic_cast<Manager*>(*it)->GetDepartment() == dynamic_cast<Employee*>(*it2)->GetDepartment())
						dynamic_cast<Manager*>(*it)->AddSubordinate(*it2);
				};
		};
};

Person* Database::HireEmployee(Person *p) {
	employees.push_back(p);
	return employees.back();
};

void Database::DisplayDepartmentEmployees(string _department) {
	cout << "---------Department: " << _department << endl << endl;

	for (vector<Person*>::iterator(it) = employees.begin(); it != employees.end(); ++it) {
		if (typeid(**it) == typeid(Manager))
			if (dynamic_cast<Manager*>(*it)->GetDepartment() == _department) {
				dynamic_cast<Manager*>(*it)->Display(false);
				dynamic_cast<Manager*>(*it)->DisplaySubordinates();
			}

		if (dynamic_cast<Employee*>(*it)->GetDepartment() == _department) {
			if (typeid(**it) == typeid(Employee))
				dynamic_cast<Employee*>(*it)->Display(false);
		};
	}
};

bool Database::FireEmployee(int id) { //delete first element with the same id. 
	bool ret = false;
	for (vector<Person*>::iterator(it) = employees.begin(); it != employees.end(); it++) {
		if (typeid(**it) == typeid(Manager)) {
			if (dynamic_cast<Manager*>(*it)->GetId() == id) {
				it = employees.erase(it);
				return true;
			}
				dynamic_cast<Manager*>(*it)->Fire(id);
		}
		if (typeid(**it) == typeid(Employee))
			if (dynamic_cast<Employee*>(*it)->GetId() == id) {
				it = employees.erase(it);
				ret = true;
			}
	};
	return ret;
};

void Database::DisplayAll() {
	for (vector<Person*>::iterator (it) = employees.begin(); it != employees.end(); ++it) {
		if (typeid(**it) == typeid(Manager)) {
			dynamic_cast<Manager*>(*it)->Display(false);
			dynamic_cast<Manager*>(*it)->DisplaySubordinates();
		}

		if (typeid(**it) == typeid(Employee))
			dynamic_cast<Employee*>(*it)->Display(false);
	}
};
