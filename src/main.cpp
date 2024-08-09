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

// Function declarations
void saveStudentsToDB(Student _s[], int count);
void loadStudentsFromDB(Student _s[], int &count);
void saveLecturersToDB(Lecturer _l[], int count);
void loadLecturersFromDB(Lecturer _l[], int &count);
void saveAppointmentsToDB(Appointment _a[], int count);
void loadAppointmentsFromDB(Appointment _a[], int &count);

// Function to save students to the database
void saveStudentsToDB(Student _s[], int count)
{
    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("appointments.db", &db);

    if (rc)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Create table if it doesn't exist
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS STUDENT("
                                 "ID TEXT PRIMARY KEY NOT NULL,"
                                 "NAME TEXT NOT NULL,"
                                 "SURNAME TEXT NOT NULL,"
                                 "DEPARTMENT TEXT NOT NULL,"
                                 "YEAR TEXT NOT NULL,"
                                 "EMAIL TEXT NOT NULL,"
                                 "PHONE TEXT NOT NULL);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    for (int i = 0; i < count; i++)
    {
        std::string insertSQL = "INSERT OR REPLACE INTO STUDENT (ID, NAME, SURNAME, DEPARTMENT, YEAR, EMAIL, PHONE) VALUES ('" +
                                _s[i].getNumber() + "','" +
                                _s[i].getName() + "','" +
                                _s[i].getSurname() + "','" +
                                _s[i].getDepartment() + "','" +
                                _s[i].getYear() + "','" +
                                _s[i].getEmail() + "','" +
                                _s[i].getPhone() + "');";
        rc = sqlite3_exec(db, insertSQL.c_str(), 0, 0, &errMsg);

        if (rc != SQLITE_OK)
        {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    sqlite3_close(db);
}

// Function to load students from the database
void loadStudentsFromDB(Student _s[], int &count)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int rc = sqlite3_open("appointments.db", &db);

    if (rc)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char *sql = "SELECT ID, NAME, SURNAME, DEPARTMENT, YEAR, EMAIL, PHONE FROM STUDENT";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    count = 0;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        std::string id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string surname = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        std::string department = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        std::string year = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        std::string email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
        std::string phone = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));

        _s[count].setNumber(id);
        _s[count].setName(name);
        _s[count].setSurname(surname);
        _s[count].setDepartment(department);
        _s[count].setYear(year);
        _s[count].setEmail(email);
        _s[count].setPhone(phone);

        count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Function to save lecturers to the database
void saveLecturersToDB(Lecturer _l[], int count)
{
    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("appointments.db", &db);

    if (rc)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Create table if it doesn't exist
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS LECTURER("
                                 "ID TEXT PRIMARY KEY NOT NULL,"
                                 "NAME TEXT NOT NULL,"
                                 "SURNAME TEXT NOT NULL,"
                                 "DEPARTMENT TEXT NOT NULL,"
                                 "EMAIL TEXT NOT NULL,"
                                 "PHONE TEXT NOT NULL,"
                                 "CHAIR TEXT NOT NULL);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    for (int i = 0; i < count; i++)
    {
        std::string insertSQL = "INSERT OR REPLACE INTO LECTURER (ID, NAME, SURNAME, DEPARTMENT, EMAIL, PHONE, CHAIR) VALUES ('" +
                                _l[i].getNumber() + "','" +
                                _l[i].getName() + "','" +
                                _l[i].getSurname() + "','" +
                                _l[i].getDepartment() + "','" +
                                _l[i].getEmail() + "','" +
                                _l[i].getPhone() + "','" +
                                _l[i].getChair() + "');";
        rc = sqlite3_exec(db, insertSQL.c_str(), 0, 0, &errMsg);

        if (rc != SQLITE_OK)
        {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    sqlite3_close(db);
}

// Function to load lecturers from the database
void loadLecturersFromDB(Lecturer _l[], int &count)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int rc = sqlite3_open("appointments.db", &db);

    if (rc)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char *sql = "SELECT ID, NAME, SURNAME, DEPARTMENT, EMAIL, PHONE, CHAIR FROM LECTURER";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    count = 0;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        std::string id = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string surname = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        std::string department = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        std::string email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        std::string phone = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
        std::string chair = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));

        _l[count].setNumber(id);
        _l[count].setName(name);
        _l[count].setSurname(surname);
        _l[count].setDepartment(department);
        _l[count].setEmail(email);
        _l[count].setPhone(phone);
        _l[count].setChair(chair);

        count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Function to save appointments to the database
void saveAppointmentsToDB(Appointment _a[], int count) {
    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("appointments.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Create table if it doesn't exist
    const char *sql = "CREATE TABLE IF NOT EXISTS APPOINTMENT("
                      "STUDENT_ID TEXT NOT NULL,"
                      "LECTURER_ID TEXT NOT NULL,"
                      "DATE TEXT NOT NULL,"
                      "START_TIME TEXT NOT NULL,"
                      "END_TIME TEXT NOT NULL,"
                      "PRIMARY KEY (STUDENT_ID, LECTURER_ID, DATE, START_TIME));";

    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    for (int i = 0; i < count; i++) {
        std::string insertSQL = "INSERT OR REPLACE INTO APPOINTMENT (STUDENT_ID, LECTURER_ID, DATE, START_TIME, END_TIME) VALUES ('" +
                                _a[i].S.getNumber() + "','" +
                                _a[i].L.getNumber() + "','" +
                                _a[i].getDate() + "','" +
                                _a[i].getStart() + "','" +
                                _a[i].getEnd() + "');";
        rc = sqlite3_exec(db, insertSQL.c_str(), 0, 0, &errMsg);

        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

    sqlite3_close(db);
}

// Function to load appointments from the database
void loadAppointmentsFromDB(Appointment _a[], int &count) {
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int rc = sqlite3_open("appointments.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char *sql = "SELECT STUDENT_ID, LECTURER_ID, DATE, START_TIME, END_TIME FROM APPOINTMENT";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to fetch data: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    count = 0;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string studentId = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        std::string lecturerId = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        std::string date = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        std::string startTime = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        std::string endTime = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));

        _a[count].S.setNumber(studentId);
        _a[count].L.setNumber(lecturerId);
        _a[count].setDate(date);
        _a[count].setStart(startTime);
        _a[count].setEnd(endTime);

        count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main()
{
    // Define arrays for students, lecturers, and appointments
    const int maxSize = 100; // Adjust based on expected number of entries
    Student students[maxSize];
    Lecturer lecturers[maxSize];
    Appointment appointments[maxSize];

    int studentCount = 0;
    int lecturerCount = 0;
    int appointmentCount = 0;

    // Load data from database
    loadStudentsFromDB(students, studentCount);
    loadLecturersFromDB(lecturers, lecturerCount);
    loadAppointmentsFromDB(appointments, appointmentCount);

    int menuLoop = 0;
    int menu = 0;
    int i;

    while (menuLoop != 5)
    {
        cout << endl
             << "Student - Lecturer Appointment System" << endl
             << endl;
        cout << "Menu:" << endl;
        cout << "1 - Student Menu" << endl;
        cout << "2 - Lecturer Menu" << endl;
        cout << "3 - Appointment Menu" << endl;
        cout << "4 - Get Final Lists" << endl;
        cout << "5 - Save and Exit" << endl;
        cin >> menuLoop;

        if (menuLoop == 1)
        {
            cout << "1 - Add Student" << endl;
            cout << "2 - List Students" << endl;
            cout << "3 - Remove Student" << endl;
            cout << "4 - Update Student" << endl;
            cin >> menu;

            if (menu == 1)
            {
                string temp_;
                Student newS;
                cout << "Student No:" << endl;
                cin >> temp_;
                newS.setNumber(temp_);
                cout << "Student Name:" << endl;
                cin >> temp_;
                newS.setName(temp_);
                cout << "Student Surname:" << endl;
                cin >> temp_;
                newS.setSurname(temp_);
                cout << "Student Department:" << endl;
                cin >> temp_;
                newS.setDepartment(temp_);
                cout << "Student Year:" << endl;
                cin >> temp_;
                newS.setYear(temp_);
                cout << "Student Email:" << endl;
                cin >> temp_;
                newS.setEmail(temp_);
                cout << "Student Phone:" << endl;
                cin >> temp_;
                newS.setPhone(temp_);

                students[studentCount] = newS;
                studentCount++;
                count[0]++;
            }
            else if (menu == 2)
            {
                for (i = 0; i < studentCount; i++)
                {
                    students[i].display();
                }
            }
            else if (menu == 3)
            {
                // student deletion is chosen
                string temp_;
                int deleted;
                cout << "Enter the Student No to remove:" << endl;
                cin >> temp_;
                i = 0;
                while (i < studentCount)
                {
                    if (students[i].getNumber() == temp_)
                        deleted = i;
                    i++;
                }
                for (i = deleted; i < studentCount; i++)
                {
                    students[i] = students[i + 1];
                }
            }
            else if (menu == 4)
            {
                // student update is chosen
                string temp_;
                int updated;
                cout << "Enter the Student No to update:" << endl;
                cin >> temp_;
                i = 0;
                while (i < studentCount)
                {
                    if (students[i].getNumber() == temp_)
                        updated = i;
                    i++;
                }
                cout << "Updated Student Name:" << endl;
                cin >> temp_;
                students[updated].setName(temp_);
                cout << "Updated Student Last Name:" << endl;
                cin >> temp_;
                students[updated].setSurname(temp_);
                cout << "Updated Student Department:" << endl;
                cin >> temp_;
                students[updated].setDepartment(temp_);
                cout << "Updated Student Starting Year:" << endl;
                cin >> temp_;
                students[updated].setYear(temp_);
                cout << "Updated Student E-Mail:" << endl;
                cin >> temp_;
                students[updated].setEmail(temp_);
                cout << "Updated Student Phone Number:" << endl;
                cin >> temp_;
                students[updated].setPhone(temp_);
            }
            else
            {
                cout << "Error." << endl;
            }
        }
        else if (menuLoop == 2)
        {
            cout << "1 - Add Lecturer" << endl;
            cout << "2 - List Lecturers" << endl;
            cout << "3 - Remove Lecturer" << endl;
            cout << "4 - Update Lecturer" << endl;
            cin >> menu;

            if (menu == 1)
            {
                string temp_;
                Lecturer newL;
                cout << "Lecturer No:" << endl;
                cin >> temp_;
                newL.setNumber(temp_);
                cout << "Lecturer Name:" << endl;
                cin >> temp_;
                newL.setName(temp_);
                cout << "Lecturer Surname:" << endl;
                cin >> temp_;
                newL.setSurname(temp_);
                cout << "Lecturer Department:" << endl;
                cin >> temp_;
                newL.setDepartment(temp_);
                cout << "Lecturer Email:" << endl;
                cin >> temp_;
                newL.setEmail(temp_);
                cout << "Lecturer Phone:" << endl;
                cin >> temp_;
                newL.setPhone(temp_);
                cout << "Lecturer Chair:" << endl;
                cin >> temp_;
                newL.setChair(temp_);

                lecturers[lecturerCount] = newL;
                lecturerCount++;
                count[1]++;
            }
            else if (menu == 2)
            {
                for (i = 0; i < lecturerCount; i++)
                {
                    lecturers[i].display();
                }
            }
            else if (menu == 3)
            {
                // lecturer deletion is chosen
                string temp_;
                int deleted;
                cout << "Enter the Lecturer No to remove:" << endl;
                cin >> temp_;
                i = 0;
                while (i < lecturerCount)
                {
                    if (lecturers[i].getNumber() == temp_)
                        deleted = i;
                    i++;
                }
                for (i = deleted; i < lecturerCount; i++)
                {
                    lecturers[i] = lecturers[i + 1];
                }
            }
            else if (menu == 4)
            {
                // lecturer update is chosen
                string temp_;
                int updated;
                cout << "Enter the Lecturer No to update:" << endl;
                cin >> temp_;
                i = 0;
                while (i < lecturerCount)
                {
                    if (lecturers[i].getNumber() == temp_)
                        updated = i;
                    i++;
                }
                cout << "Updated Lecturer Name:" << endl;
                cin >> temp_;
                lecturers[updated].setName(temp_);
                cout << "Updated Lecturer Last Name:" << endl;
                cin >> temp_;
                lecturers[updated].setSurname(temp_);
                cout << "Updated Lecturer Department:" << endl;
                cin >> temp_;
                lecturers[updated].setDepartment(temp_);
                cout << "Updated Lecturer E-Mail:" << endl;
                cin >> temp_;
                lecturers[updated].setEmail(temp_);
                cout << "Updated Lecturer Phone Number:" << endl;
                cin >> temp_;
                lecturers[updated].setPhone(temp_);
                cout << "Updated Lecturer title:" << endl;
                cin >> temp_;
                lecturers[updated].setChair(temp_);
            }
            else
            {
                cout << "Error." << endl;
            }
        }
        else if (menuLoop == 3)
        {
            cout << "1 - Add Appointment" << endl;
            cout << "2 - List Appointments" << endl;
            cout << "3 - Remove Appointment" << endl;
            cout << "4 - Update Appointment" << endl;
            cin >> menu;

            if (menu == 1)
            {
                string temp_;
                Appointment newA;
                cout << "Student No:" << endl;
                cin >> temp_;
                newA.S.setNumber(temp_);
                cout << "Lecturer No:" << endl;
                cin >> temp_;
                newA.L.setNumber(temp_);
                cout << "Date:" << endl;
                cin >> temp_;
                newA.setDate(temp_);
                cout << "Start Time:" << endl;
                cin >> temp_;
                newA.setStart(temp_);
                cout << "End Time:" << endl;
                cin >> temp_;
                newA.setEnd(temp_);

                appointments[appointmentCount] = newA;
                appointmentCount++;
                count[2]++;
            }
            else if (menu == 2)
            {
                for (i = 0; i < appointmentCount; i++)
                {
                    appointments[i].display();
                }
            }
            else if (menu == 3)
            {
                // appointment deletion is chosen
                string temp_, temp_2;
                int deleted;
                cout << "Enter the Student No to remove:" << endl;
                cin >> temp_;
                cout << "Enter the Lecturer No to remove:" << endl;
                cin >> temp_2;
                i = 0;
                while (i < appointmentCount)
                {
                    if (appointments[i].S.getNumber() == temp_ && appointments[i].L.getNumber() == temp_2)
                        deleted = i;
                    i++;
                }
                for (i = deleted; i < appointmentCount; i++)
                {
                    appointments[i] = appointments[i + 1];
                }
            }
            else if (menu == 4)
            {
                // appointment update is chosen
                string temp_, temp_2;
                int updated;
                cout << "Enter the Student No to update:" << endl;
                cin >> temp_;
                cout << "Enter the Lecturer No to update:" << endl;
                cin >> temp_2;
                i = 0;
                while (i < appointmentCount)
                {
                    if (appointments[i].S.getNumber() == temp_ && appointments[i].L.getNumber() == temp_2)
                        updated = i;
                    i++;
                }
                cout << "Updated Appointment Date:" << endl;
                cin >> temp_;
                appointments[updated].setDate(temp_);
                cout << "Updated Starting Hour:" << endl;
                cin >> temp_;
                appointments[updated].setStart(temp_);
                cout << "Updated Ending Hour:" << endl;
                cin >> temp_;
                appointments[updated].setEnd(temp_);
            }
            else
            {
                cout << "Error." << endl;
            }
        }
        else if (menuLoop == 4)
        {
            cout << "1 - Student List" << endl;
            cout << "2 - Lecturer List" << endl;
            cout << "3 - Appointment List" << endl;
            cin >> menu;

            if (menu == 1)
            {
                for (i = 0; i < studentCount; i++)
                {
                    students[i].display();
                }
            }
            else if (menu == 2)
            {
                for (i = 0; i < lecturerCount; i++)
                {
                    lecturers[i].display();
                }
            }
            else if (menu == 3)
            {
                for (i = 0; i < appointmentCount; i++)
                {
                    appointments[i].display();
                }
            }
        }
        else if (menuLoop == 5)
        {
            // Save data to the database before exiting
            saveStudentsToDB(students, studentCount);
            saveLecturersToDB(lecturers, lecturerCount);
            saveAppointmentsToDB(appointments, appointmentCount);

            cout << "Data saved to resource file. Exiting..." << endl;
        }
    }
    return 0;
}

