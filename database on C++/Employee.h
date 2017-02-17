#define _CRT_SECURE_NO_WARNINGS
#pragma once
/*!
* file: Employee.h
* written: 09/05/2016
* synopsis: Employee class declaration
*/

#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

//An abstract class
class Person {
public:
	Person() {};
	Person(string _f_name, string _l_name, int _age) : age(_age),
		f_name(_f_name), l_name(_l_name) {	}
	virtual void Display(bool) = 0;
protected:
	string f_name;//first name
	string l_name;//last name
	int age;
};


class Employee : public Person {
public:
	Employee() { id = -1; };
	Employee(string _f_name, string _l_name, int _age, int _id) :
		Person(_f_name, _l_name, _age), id(_id) {};
	Employee(const Employee &e);
	Employee& operator=(const Employee &e);
	void SetSalary(int s);
	void SetDepartment(string dept);
	void SetId(int n);
	int GetId();
	string GetDepartment();
	virtual void Display(bool);
	//Add here whatever you need
protected:
	string department;
	int salary;
	int id;
};


