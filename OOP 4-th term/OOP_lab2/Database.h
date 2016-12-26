#ifndef DATABASE_H
#define DATABASE_H

/*!
* file: Database.h
* written: 24/03/2016
* synopsis: Database class definition
* Copyright (c) 2016 by Se.Latyuk
*
*/
//#pragma once

#include "Manager.h"

class Database{

public:
    Database();
    ~Database();//no need in destructor
    //creates “flat” database
    bool LoadFromFile(const char *file);
    //arranges "flat" database after loading from the file
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


#endif // DATABASE_H
