// Lecturer.h
#ifndef LECTURER_H
#define LECTURER_H

#include "People.h"
#include <string>
using namespace std;

class Lecturer : public People
{
private:
    string chair;

public:
    Lecturer();
    Lecturer(string *_temp);
    string getChair();
    void setChair(string _chair);
    void display();
};

#endif
