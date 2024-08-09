// Lecturer.cpp
#include "Lecturer.h"
#include <iostream>

Lecturer::Lecturer() {}

Lecturer::Lecturer(string *_temp)
{
    setNumber(_temp[0]);
    setName(_temp[1]);
    setSurname(_temp[2]);
    setDepartment(_temp[3]);
    setEmail(_temp[4]);
    setPhone(_temp[5]);
    setChair(_temp[6]);
}

string Lecturer::getChair() { return this->chair; }
void Lecturer::setChair(string _chair) { this->chair = _chair; }

void Lecturer::display()
{
    cout << getNumber() << " - ";
    cout << getName() << " - ";
    cout << getSurname() << " - ";
    cout << getDepartment() << " - ";
    cout << getEmail() << " - ";
    cout << getPhone() << " - ";
    cout << getChair() << endl;
}
