/*!
* file: Test.cpp
* written: 24/03/2016
* synopsis: Database class test
* Copyright (c) 2016 by Se.Latyuk
*/

#include "Database.h"

int main(){
    Database db;
    db.LoadFromFile("/home/serhiy/OOP_lab2/input.csv");
    db.DisplayAll();
    db.ArrangeSubordinates();
    db.DisplayAll();

    Employee *e = new Employee("Vasya", "Ivanov", 20, 5);
    e->SetDepartment("QA");
    e->SetSalary(2000);

    db.HireEmployee(e);
    db.DisplayAll();
    db.DisplayDepartmentEmployees("IT");

    db.FireEmployee(0);
    db.DisplayAll();

    //db.DisplayDepartmentEmployees("QA");
}
