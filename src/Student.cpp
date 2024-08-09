// Student.cpp
#include "Student.h"
#include <iostream>

Student::Student() {}

Student::Student(string *_temp)
{
    setNumber(_temp[0]);
    setName(_temp[1]);
    setSurname(_temp[2]);
    setDepartment(_temp[3]);
    setYear(_temp[4]);
    setEmail(_temp[5]);
    setPhone(_temp[6]);
}

string Student::getYear() { return this->year; }
void Student::setYear(string _year) { this->year = _year; }

void Student::display()
{
    cout << getNumber() << " - ";
    cout << getName() << " - ";
    cout << getSurname() << " - ";
    cout << getDepartment() << " - ";
    cout << getYear() << " - ";
    cout << getEmail() << " - ";
    cout << getPhone() << endl;
}
