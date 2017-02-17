/*!
* file: Database.h
* written: 09/05/2016
* synopsis: Database class definition
*/
#pragma once
#include "Manager.h"
#include <vector>

class Database {

public:
	Database() {};
	~Database() {};
	bool LoadFromFile(const char *file);
	void ArrangeSubordinates();
	//hire a new employee
	Person* HireEmployee(Person *p);
	void DisplayDepartmentEmployees(string _department);
	//fire the employee
	bool FireEmployee(int id);
	void DisplayAll();
	//Add here whatever you need

private:
	vector<Person*> employees;
};

