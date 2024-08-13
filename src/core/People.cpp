// People.cpp
#include "core/People.hpp"

std::string People::getNumber() const { return this->number; }
std::string People::getName() const { return this->name; }
std::string People::getSurname() const { return this->surname; }
std::string People::getDepartment() const { return this->department; }
std::string People::getEmail() const { return this->email; }
std::string People::getPhone() const { return this->phone; }

void People::setNumber(std::string _number) { this->number = _number; }
void People::setName(std::string _name) { this->name = _name; }
void People::setSurname(std::string _surname) { this->surname = _surname; }
void People::setDepartment(std::string _department) { this->department = _department; }
void People::setEmail(std::string _email) { this->email = _email; }
void People::setPhone(std::string _phone) { this->phone = _phone; }
