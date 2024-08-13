// Student.cpp
#include "core/Student.hpp"
#include <iostream>

Student::Student() {}

Student::Student(std::string *_temp)
{
    setNumber(_temp[0]);
    setName(_temp[1]);
    setSurname(_temp[2]);
    setDepartment(_temp[3]);
    setYear(_temp[4]);
    setEmail(_temp[5]);
    setPhone(_temp[6]);
}

std::string Student::getYear() const { return this->year; }
void Student::setYear(std::string _year) { this->year = _year; }

void Student::display() const
{
    std::cout << getNumber() << " - ";
    std::cout << getName() << " - ";
    std::cout << getSurname() << " - ";
    std::cout << getDepartment() << " - ";
    std::cout << getYear() << " - ";
    std::cout << getEmail() << " - ";
    std::cout << getPhone() << std::endl;
}
