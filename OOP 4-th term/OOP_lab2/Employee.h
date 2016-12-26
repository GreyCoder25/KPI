#ifndef EMPLOYEE_H
#define EMPLOYEE_H

/*!
* file: Employee.h
* written: 24/03/2016
* synopsis: Employee class declaration
* Copyright (c) 2016 by Se.Latyuk
*/

//#pragma once
//#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <vector>

using namespace std;

//An abstract class
class Person{

public:
    Person(){};
    Person(string _f_name, string _l_name, int _age) : age(_age),
 f_name(_f_name), l_name(_l_name){}
    virtual void Display() = 0;
protected:
    string f_name;//first name
    string l_name;//last name
    int age;

};

class Employee : public Person{

public:
    Employee();
    Employee(string _f_name, string _l_name, int _age, int _id);
    Employee(const Employee &e);
    Employee& operator=(const Employee &e);
    void SetSalary(int s);
    void SetDepartment(string dept);
    void SetId(int n);
    int GetId();
    string GetDepartment();
    virtual void Display();
    //Add here whatever you need

protected:
    string department;
    int salary;
    int id;

};

#endif // EMPLOYEE_H
