/*!
* file: Employee.cpp
* written: 24/03/2016
* synopsis: Employee class implementation
* Copyright (c) 2016 by Se.Latyuk
*/
#include "Employee.h"
//Classes Implemantation

Employee::Employee(){

}

Employee::Employee(string _f_name, string _l_name, int _age, int _id) :
    Person(_f_name, _l_name, _age), id(_id){

}

Employee::Employee(const Employee &e) : Person(e.f_name, e.l_name, e.age),
    id(e.id), department(e.department), salary(e.salary){

}

Employee& Employee::operator=(const Employee &e){
    f_name = e.f_name;
    l_name = e.l_name;
    age = e.age;
    department = e.department;
    id = e.id;
    salary = e.salary;

    return *this;
}

void Employee::SetSalary(int s){
    salary = (s > 0) ? s : 0;
}

void Employee::SetDepartment(string dept){
    department = dept;
}

void Employee::SetId(int n){
    id = n;
}

int Employee::GetId(){
    return id;
}

string Employee::GetDepartment(){
    return department;
}

void Employee::Display(){
    cout<<"Employment type: employee\n";
    cout<<"id: "<<id<<endl;
    cout<<f_name<<' '<<l_name<<" age: "<<age<<" salary: "<<salary<<endl;
    cout<<"department: "<<department<<endl<<endl;
}
