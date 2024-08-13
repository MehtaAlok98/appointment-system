// People.h
#ifndef PEOPLE_HPP
#define PEOPLE_HPP

#include <string>

class People
{
private:
    std::string number;
    std::string name;
    std::string surname;
    std::string department;
    std::string email;
    std::string phone;

public:
    std::string getNumber() const;
    std::string getName() const;
    std::string getSurname() const;
    std::string getDepartment() const;
    std::string getEmail() const;
    std::string getPhone() const;

    void setNumber(std::string _number);
    void setName(std::string _name);
    void setSurname(std::string _surname);
    void setDepartment(std::string _department);
    void setEmail(std::string _email);
    void setPhone(std::string _phone);
};

#endif
