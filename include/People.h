// People.h
#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>
using namespace std;

class People
{
private:
    string number;
    string name;
    string surname;
    string department;
    string email;
    string phone;

public:
    string getNumber();
    void setNumber(string _number);
    string getName();
    void setName(string _name);
    string getSurname();
    void setSurname(string _surname);
    string getDepartment();
    void setDepartment(string _department);
    string getEmail();
    void setEmail(string _email);
    string getPhone();
    void setPhone(string _phone);
};

#endif
