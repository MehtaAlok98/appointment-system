// Student.h
#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "People.hpp"
#include <string>

class Student : public People
{
private:
    std::string year;

public:
    Student();
    Student(std::string *_temp);
    std::string getYear() const;
    void setYear(std::string _year);
    void display() const;
};

#endif
