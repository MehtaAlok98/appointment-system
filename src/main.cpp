// main.cpp
#include <iostream>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "config/Globals.hpp"
#include "config/ManageGlobals.hpp"
#include "DatabaseManager.hpp"
#include "managers/StudentManager.hpp"
#include "managers/LecturerManager.hpp"
#include "managers/AppointmentManager.hpp"

int main(int argc, char *argv[])
{
  spdlog::info("Application started");

  ConfigManager::parseArgumentsAndSetGlobals(argc, argv);

  DatabaseManager dbManager(db_path);

  StudentManager studentManager(dbManager);
  LecturerManager lecturerManager(dbManager);
  AppointmentManager appointmentManager(dbManager);

  std::vector<Student> students;
  std::vector<Lecturer> lecturers;
  std::vector<Appointment> appointments;

  studentManager.loadStudents();
  lecturerManager.loadLecturers();
  appointmentManager.loadAppointments(appointments);

  int menuLoop = 0;
  while (menuLoop != 5)
  {
    std::cout << "\nStudent - Lecturer Appointment System\n\n";
    std::cout << "Menu:\n1 - Student Menu\n2 - Lecturer Menu\n3 - Appointment Menu\n4 - Get Final Lists\n5 - Save and Exit\nEnter your choice: ";
    std::cin >> menuLoop;

    switch (menuLoop)
    {
    case 1:
      studentManager.handleStudentMenu();
      break;
    case 2:
      lecturerManager.handleLecturerMenu();
      break;
    case 3:
      appointmentManager.handleAppointmentMenu();
      break;
    case 4:
      std::cout << "1 - Student List\n2 - Lecturer List\n3 - Appointment List\n";
      int choice;
      std::cin >> choice;
      switch (choice)
      {
      case 1:
        for (const auto &student : students)
          student.display();
        break;
      case 2:
        for (const auto &lecturer : lecturers)
          lecturer.display();
        break;
      case 3:
        for (const auto &appointment : appointments)
          appointment.display();
        break;
      default:
        std::cout << "Invalid choice.\n";
      }
      break;
    case 5:
      // Save data to the database before exiting
      for (const auto &student : students)
      {
        studentManager.saveStudent(student);
      }
      for (const auto &lecturer : lecturers)
      {
        lecturerManager.saveLecturer(lecturer);
      }
      for (const auto &appointment : appointments)
      {
        appointmentManager.saveAppointment(appointment);
      }
      std::cout << "Data saved to resource file. Exiting...\n";
      break;
    default:
      std::cout << "Invalid choice. Please try again.\n";
    }
  }
  spdlog::info("Application finished");
  return 0;
}
