#include "Manager.h"

Manager::Manager() {

}

Manager::~Manager() {
    subordinates.clear();
}

Manager::Manager(const Manager &m) : Employee(m){
    subordinates = m.subordinates;
}

Manager& Manager::operator=(const Manager &m){
    f_name = m.f_name;
    l_name = m.l_name;
    age = m.age;
    department = m.department;
    id = m.id;
    salary = m.salary;
    subordinates = m.subordinates; //test itself assignment

    return *this;
}

void Manager::Display(){
    cout<<"Employment type: manager\n";
    cout<<"id: "<<id<<endl;
    cout<<f_name<<' '<<l_name<<" age: "<<age<<" salary: "<<salary<<endl;
    cout<<"department: "<<department<<endl;
    cout<<"Subordinates: "<<endl<<endl;

    if (subordinates.size() != 0) {
        DisplaySubordinates();
    }
    else {
        cout<<setw(10)<<"none"<<endl<<endl;
    }
}
//add an employee to the subordinates list
Person* Manager::AddSubordinate(Person *p){
    if (p != 0) {
        subordinates.push_back(p);
        return p;
    }
    return 0;
}

void Manager::DisplaySubordinates(){
    cout<<"------------------------------------"<<endl;
    for (list<Person *>::iterator it = subordinates.begin(); it != subordinates.end(); ++it) {
        cout<<"        ";
        (*it)->Display();
    }
    cout<<"------------------------------------"<<endl;
}

list<Person *> & Manager::GetSubordinatesList() {
    return subordinates;
}
