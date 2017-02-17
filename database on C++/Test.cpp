/*!
* file: Test.cpp
* written: 09/05/2016
* synopsis: Database class test
*/
#include "Database.h"

int main() {
	Database db;

	/*Employee *b = new Employee();
	b->Display(false);
	b->GetDepartment();
	
	Employee *k = new Employee("Sub2222222222222222", "Employee", 19, 0);
	k->Display(false);

	Employee *e1 = new Employee(*b);
	e1->Display(false);
	e1->SetDepartment("Web");

	Manager *e2 = new Manager("Op3333333333333333kl", "Manager", 19, 0);
	e2->Display(false);
	e2->AddSubordinate(e1); 
	e2->DisplaySubordinates();
	*/
	Manager *e3 = new Manager("Fr4444444444444444444a", "Manager", 19, 0);
	e3->Display(false);
	e3->DisplaySubordinates();
	//e3 = e2;
	//e3->Display(false);
	

	cout << "--------------------------LOAD FROM FILE-----------------------" << endl;
	db.LoadFromFile("input.csv");
	db.DisplayAll();
	cout << "--------------------------ArrangeSubordinates-----------------------" << endl;
	db.ArrangeSubordinates();
	db.DisplayAll();
	cout << "--------------------------HIRE SOME EMPLOYEE-----------------------" << endl;
	db.HireEmployee(e3);

	db.ArrangeSubordinates();
	db.DisplayAll();
	cout << "------------------------------------------FIRE SOME EMPLOYEE-----------------------------------------------" << endl;
	db.FireEmployee(0);
	db.DisplayAll();
	db.DisplayDepartmentEmployees("IT");
};
