// Appointment.cpp
#include "core/Appointment.hpp"
#include <iostream>

Appointment::Appointment() {}

Appointment::Appointment(std::string *_temp)
{
    S.setNumber(_temp[0]);
    L.setNumber(_temp[1]);
    setDate(_temp[2]);
    setStart(_temp[3]);
    setEnd(_temp[4]);
}

std::string Appointment::getDate() const { return this->date; }
std::string Appointment::getStart() const { return this->start; }
std::string Appointment::getEnd() const { return this->end; }

void Appointment::setDate(std::string _date) { this->date = _date; }
void Appointment::setStart(std::string _start) { this->start = _start; }
void Appointment::setEnd(std::string _end) { this->end = _end; }

void Appointment::display() const
{
    std::cout << S.getNumber() << " - ";
    std::cout << L.getNumber() << " - ";
    std::cout << getDate() << " - ";
    std::cout << getStart() << " - ";
    std::cout << getEnd() << std::endl;
}
