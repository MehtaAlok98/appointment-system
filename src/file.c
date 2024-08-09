// main.cpp
#include <iostream>
#include <fstream>
#include <cstring>
#include <sqlite3.h>
#include "Student.h"
#include "Lecturer.h"
#include "Appointment.h"

using namespace std;

// Global variable for array sizes
int count[3];

void countFile(const char *filename, int filenum);
void readFromFile(Student _s[], Lecturer _l[], Appointment _a[], const char *f1, const char *f2, const char *f3);
void saveToFile(Student _s[], Lecturer _l[], Appointment _a[], int x, int y, int z, const char *resourceFile);
void loadFromFile(Student _s[], Lecturer _l[], Appointment _a[], int &x, int &y, int &z, const char *resourceFile);

void countFile(const char *filename, int filenum)
{
  ifstream file;
  file.open(filename);
  string str;

  while (getline(file, str))
  {
    count[filenum]++;
  }

  file.close();
}

void readFromFile(Student _s[], Lecturer _l[], Appointment _a[], char *f1, char *f2, char *f3)
{
  ifstream file;
  file.open(f1);
  string str;
  int i = 0;

  while (getline(file, str))
  {
    string arr[7];
    int index = 0;
    char *token = strtok(&str[0], ",");

    while (token != NULL)
    {
      arr[index++] = token;
      token = strtok(NULL, ",");
    }

    Student temp(arr);
    _s[i] = temp;
    i++;
  }

  file.close();

  file.open(f2);
  i = 0;

  while (getline(file, str))
  {
    string arr[7];
    int index = 0;
    char *token = strtok(&str[0], ",");

    while (token != NULL)
    {
      arr[index++] = token;
      token = strtok(NULL, ",");
    }

    Lecturer temp(arr);
    _l[i] = temp;
    i++;
  }

  file.close();

  file.open(f3);
  i = 0;

  while (getline(file, str))
  {
    string arr[5];
    int index = 0;
    char *token = strtok(&str[0], ",");

    while (token != NULL)
    {
      arr[index++] = token;
      token = strtok(NULL, ",");
    }

    Appointment temp(arr);
    _a[i] = temp;
    i++;
  }

  file.close();
}

void saveToFile(Student _s[], Lecturer _l[], Appointment _a[], int x, int y, int z, const char *resourceFile)
{
  ofstream file;
  file.open(resourceFile);

  // Save students
  file << "Students:" << endl;
  for (int i = 0; i < x; i++)
  {
    file << _s[i].getNumber() << ","
         << _s[i].getName() << ","
         << _s[i].getSurname() << ","
         << _s[i].getDepartment() << ","
         << _s[i].getYear() << ","
         << _s[i].getEmail() << ","
         << _s[i].getPhone() << endl;
  }

  // Save lecturers
  file << "Lecturers:" << endl;
  for (int i = 0; i < y; i++)
  {
    file << _l[i].getNumber() << ","
         << _l[i].getName() << ","
         << _l[i].getSurname() << ","
         << _l[i].getDepartment() << ","
         << _l[i].getEmail() << ","
         << _l[i].getPhone() << ","
         << _l[i].getChair() << endl;
  }

  // Save appointments
  file << "Appointments:" << endl;
  for (int i = 0; i < z; i++)
  {
    file << _a[i].S.getNumber() << ","
         << _a[i].L.getNumber() << ","
         << _a[i].getDate() << ","
         << _a[i].getStart() << ","
         << _a[i].getEnd() << endl;
  }

  file.close();
}

void loadFromFile(Student _s[], Lecturer _l[], Appointment _a[], int &x, int &y, int &z, const char *resourceFile)
{
  ifstream file;
  file.open(resourceFile);
  string str;

  while (getline(file, str))
  {
    if (str == "Students:")
    {
      x = 0;
      while (getline(file, str) && str != "Lecturers:")
      {
        string arr[7];
        int index = 0;
        char *token = strtok(&str[0], ",");

        while (token != NULL)
        {
          arr[index++] = token;
          token = strtok(NULL, ",");
        }

        Student temp(arr);
        _s[x] = temp;
        x++;
      }
    }
    if (str == "Lecturers:")
    {
      y = 0;
      while (getline(file, str) && str != "Appointments:")
      {
        string arr[7];
        int index = 0;
        char *token = strtok(&str[0], ",");

        while (token != NULL)
        {
          arr[index++] = token;
          token = strtok(NULL, ",");
        }

        Lecturer temp(arr);
        _l[y] = temp;
        y++;
      }
    }
    if (str == "Appointments:")
    {
      z = 0;
      while (getline(file, str))
      {
        string arr[5];
        int index = 0;
        char *token = strtok(&str[0], ",");

        while (token != NULL)
        {
          arr[index++] = token;
          token = strtok(NULL, ",");
        }

        Appointment temp(arr);
        _a[z] = temp;
        z++;
      }
    }
  }

  file.close();
}