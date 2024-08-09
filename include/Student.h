// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include "People.h"
#include <string>
using namespace std;

class Student : public People
{
private:
    string year;

public:
    Student();
    Student(string *_temp);
    string getYear();
    void setYear(string _year);
    void display();
};

#endif
