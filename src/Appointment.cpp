// Appointment.cpp
#include "Appointment.h"
#include <iostream>

Appointment::Appointment() {}

Appointment::Appointment(string *_temp)
{
    S.setNumber(_temp[0]);
    L.setNumber(_temp[1]);
    setDate(_temp[2]);
    setStart(_temp[3]);
    setEnd(_temp[4]);
}

string Appointment::getDate() { return this->date; }
void Appointment::setDate(string _date) { this->date = _date; }
string Appointment::getStart() { return this->start; }
void Appointment::setStart(string _start) { this->start = _start; }
string Appointment::getEnd() { return this->end; }
void Appointment::setEnd(string _end) { this->end = _end; }

void Appointment::display()
{
    cout << S.getNumber() << " - ";
    cout << L.getNumber() << " - ";
    cout << getDate() << " - ";
    cout << getStart() << " - ";
    cout << getEnd() << endl;
}
