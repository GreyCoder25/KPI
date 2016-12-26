#ifndef MANAGER_H
#define MANAGER_H

/*!
* file: Manager.h
* written: 24/03/2016
* synopsis: Manager class declaration
* Copyright (c) 2016 by Se.Latyuk
*/
//#pragma once
#include "Employee.h"
#include <list>

class Manager : public Employee {

public:
    Manager();
    ~Manager();
    Manager(string _f_name, string _l_name, int _age, int _id) :
        Employee(_f_name, _l_name, _age, _id){};
    Manager(const Manager &m);
    Manager& operator=(const Manager &m);
    virtual void Display();
    //add an employee to the subordinates list
    Person* AddSubordinate(Person *p);
    void DisplaySubordinates();
    list<Person *> & GetSubordinatesList();
    //Add here whatever you need

private:
    list<Person *> subordinates;//список подчиненных

};

#endif // MANAGER_H
