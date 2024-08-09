// Appointment.h
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Student.h"
#include "Lecturer.h"
#include <string>
using namespace std;

class Appointment
{
private:
    string date;
    string start;
    string end;

public:
    Lecturer L;
    Student S;
    Appointment();
    Appointment(string *_temp);
    string getDate();
    void setDate(string _date);
    string getStart();
    void setStart(string _start);
    string getEnd();
    void setEnd(string _end);
    void display();
};

#endif
