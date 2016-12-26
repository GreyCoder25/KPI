/*!
* file: Database.cpp
* written: 24/03/2016
* synopsis: Database class implementation
* Copyright (c) 2016 by Se.Latyuk
*/

#include "Database.h"

Database::Database(){

}

Database::~Database(){
    for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it)
        delete (*it);
    employees.clear();
}

bool Database::LoadFromFile(const char *file){

    ifstream inpFile(file);
    if (!inpFile) {
        cerr<<"File could not be opened"<<endl;
        exit(1);
    }
    int typeOfEmpl;
    while (inpFile>>typeOfEmpl) {
        char t;
        //cout<<"typeOfEmpl: "<<typeOfEmpl<<' ';
        int id;
        inpFile>>t;
        inpFile>>id;
        //cout<<"id: "<<id<<' ';
        string fn;
        inpFile>>t;
        getline(inpFile, fn, ';');
        //cout<<"fn: "<<fn<<' ';
        string ln;
        getline(inpFile, ln, ';');
        //cout<<"ln: "<<ln<<' ';
        int age;
        inpFile>>age;
        //cout<<"age: "<<age<<' ';
        string dep;
        inpFile>>t;
        getline(inpFile, dep, ';');
        //cout<<"dep: "<<dep<<' ';
        int s;
        //inpFile>>t;
        inpFile>>s;
        //cout<<"salary: "<<s<<' '<<endl;

        if (typeOfEmpl == 0) {
            Employee* e = new Employee(fn, ln, age, id);
            e->SetDepartment(dep);
            e->SetSalary(s);
            employees.push_back(e);
        }
        else if (typeOfEmpl == 1) {
            Manager* m = new Manager(fn, ln, age, id);
            m->SetDepartment(dep);
            m->SetSalary(s);
            employees.push_back(m);
        }
    }


    inpFile.close();
}

//arranges "flat" database after loading from the file
void Database::ArrangeSubordinates() {

    for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it)
        if (typeid(**it) == typeid(Manager)) {
            for (vector<Person*>::iterator it2 = employees.begin(); it2 != employees.end(); ++it2)
                if (typeid(**it2) == typeid(Employee) && (dynamic_cast<Employee *>(*it2)->GetDepartment() == dynamic_cast<Manager *>(*it)->GetDepartment()))
                    dynamic_cast<Manager *>(*it)->GetSubordinatesList().push_back(*it2);
        }
}

//hire a new employee
Person* Database::HireEmployee(Person *p) {
    if (p != 0) {
        employees.push_back(p);

        if (typeid(*p) == typeid(Employee)) {
            for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it)
                if (typeid(**it) == typeid(Manager) && (dynamic_cast<Employee *>(p)->GetDepartment() == dynamic_cast<Manager *>(*it)->GetDepartment()))
                    dynamic_cast<Manager *>(*it)->GetSubordinatesList().push_back(p);
        }
        return p;
    }
    return 0;
}

void Database::DisplayDepartmentEmployees(string _department) {
    for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it)
        if (dynamic_cast<Employee *>(*it)->GetDepartment() == _department)
            (*it)->Display();
}

//fire the employee
bool Database::FireEmployee(int id) {
    string fireEmplDep;
    for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it)
        if (dynamic_cast<Employee *>(*it)->GetId() == id) {
            fireEmplDep = dynamic_cast<Employee *>(*it)->GetDepartment();
            if (typeid(**it) == typeid(Manager)) {
                it = employees.erase(it);
                return true;
            }
            it = employees.erase(it);
        }
    for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it)
        if (typeid(**it) == typeid(Manager) && (fireEmplDep == dynamic_cast<Manager *>(*it)->GetDepartment())) {
            for (list<Person*>::iterator subIt = dynamic_cast<Manager *>(*it)->GetSubordinatesList().begin(); subIt != dynamic_cast<Manager *>(*it)->GetSubordinatesList().end(); ++subIt)
                if (dynamic_cast<Employee *>(*subIt)->GetId() == id) {
                    dynamic_cast<Manager *>(*it)->GetSubordinatesList().erase(subIt);
                    return true;
                }
        }
    return false;
}

void Database::DisplayAll(){
    for (vector<Person*>::iterator it = employees.begin(); it != employees.end(); ++it)
        (*it)->Display();
}
