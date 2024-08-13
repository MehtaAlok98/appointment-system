// Appointment.h
#ifndef APPOINTMENT_HPP
#define APPOINTMENT_HPP

#include "Student.hpp"
#include "Lecturer.hpp"
#include <string>

class Appointment
{
private:
    std::string date;
    std::string start;
    std::string end;

public:
    Lecturer L;
    Student S;
    Appointment();
    Appointment(std::string *_temp);
    std::string getDate() const;
    std::string getStart() const;
    std::string getEnd() const;
    void setDate(std::string _date);
    void setStart(std::string _start);
    void setEnd(std::string _end);
    void display() const;
};

#endif
