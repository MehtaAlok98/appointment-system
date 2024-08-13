// Lecturer.h
#ifndef LECTURER_HPP
#define LECTURER_HPP

#include "People.hpp"
#include <string>

class Lecturer : public People
{
private:
    std::string chair;

public:
    Lecturer();
    Lecturer(std::string *_temp);

    std::string getChair() const;
    void setChair(std::string _chair);
    
    void display() const;
};

#endif
