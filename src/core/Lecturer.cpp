// Lecturer.cpp
#include "core/Lecturer.hpp"
#include <iostream>

Lecturer::Lecturer() {}

Lecturer::Lecturer(std::string *_temp)
{
    setNumber(_temp[0]);
    setName(_temp[1]);
    setSurname(_temp[2]);
    setDepartment(_temp[3]);
    setEmail(_temp[4]);
    setPhone(_temp[5]);
    setChair(_temp[6]);
}

std::string Lecturer::getChair() const { return this->chair; }
void Lecturer::setChair(std::string _chair) { this->chair = _chair; }

void Lecturer::display() const
{
    std::cout << getNumber() << " - ";
    std::cout << getName() << " - ";
    std::cout << getSurname() << " - ";
    std::cout << getDepartment() << " - ";
    std::cout << getEmail() << " - ";
    std::cout << getPhone() << " - ";
    std::cout << getChair() << std::endl;
}
