#include "managers/AppointmentManager.hpp"
#include <iostream>

AppointmentManager::AppointmentManager(DatabaseManager &dbMgr) : dbManager(dbMgr)
{
  auto existingLogger = spdlog::get("AppointmentManager");
  if (!existingLogger)
  {

    logger = spdlog::stdout_color_mt("AppointmentManager");
    spdlog::set_level(spdlog::level::info);
  }
  else
  {
    logger = existingLogger;
  }
}

void AppointmentManager::loadAppointments(std::vector<Appointment> &appointments)
{
  std::string selectSQL = "SELECT STUDENT_ID, LECTURER_ID, DATE, START_TIME, END_TIME FROM APPOINTMENT";
  sqlite3_stmt *stmt = dbManager.prepareStatement(selectSQL);

  if (!stmt)
    return;

  while (sqlite3_step(stmt) == SQLITE_ROW)
  {
    Appointment appointment;
    appointment.S.setNumber(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
    appointment.L.setNumber(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    appointment.setDate(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
    appointment.setStart(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
    appointment.setEnd(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)));
    appointments.push_back(appointment);
  }

  sqlite3_finalize(stmt);
  logger->info("Loaded all appointments from the database");
}

void AppointmentManager::saveAppointment(const Appointment &appointment)
{
  std::string insertSQL = "INSERT OR REPLACE INTO APPOINTMENT (STUDENT_ID, LECTURER_ID, DATE, START_TIME, END_TIME) VALUES (?, ?, ?, ?, ?);";
  sqlite3_stmt *stmt = dbManager.prepareStatement(insertSQL);

  if (!stmt)
    return;

  sqlite3_bind_text(stmt, 1, appointment.S.getNumber().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, appointment.L.getNumber().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, appointment.getDate().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, appointment.getStart().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, appointment.getEnd().c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE)
  {
    logger->error("Could not insert appointment: {}", dbManager.dbErrorMsg());
  }

  sqlite3_finalize(stmt);
  logger->info("Saved appointment for student {} with lecturer {} to the database", appointment.S.getNumber(), appointment.L.getNumber());
}

void AppointmentManager::updateAppointment(const Appointment &appointment)
{
  saveAppointment(appointment);
  logger->info("Updated appointment for student {} with lecturer {} in the database", appointment.S.getNumber(), appointment.L.getNumber());
}

void AppointmentManager::deleteAppointment(const std::string &studentNumber, const std::string &lecturerNumber)
{
  std::string deleteSQL = "DELETE FROM APPOINTMENT WHERE STUDENT_ID = ? AND LECTURER_ID = ?";

  sqlite3_stmt *stmt = dbManager.prepareStatement(deleteSQL);

  if (!stmt)
    return;

  sqlite3_bind_text(stmt, 1, studentNumber.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, lecturerNumber.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE)
  {
    logger->error("Could not delete appointment: {}", dbManager.dbErrorMsg());
  }

  sqlite3_finalize(stmt);
  logger->info("Deleted appointment for student {} with lecturer {} from the database", studentNumber, lecturerNumber);
}

void AppointmentManager::handleAppointmentMenu()
{
  int menu;
  std::cout << "1 - Add Appointment\n";
  std::cout << "2 - List Appointments\n";
  std::cout << "3 - Remove Appointment\n";
  std::cout << "4 - Update Appointment\n";
  std::cout << "Enter your choice: ";
  std::cin >> menu;

  std::string temp_, temp_2; // student and lecturer
  Appointment appointment;
  switch (menu)
  {
  case 1:
    std::cout << "Student No: ";
    std::cin >> temp_;
    appointment.S.setNumber(temp_);
    std::cout << "Lecturer No: ";
    std::cin >> temp_;
    appointment.L.setNumber(temp_);
    std::cout << "Date: ";
    std::cin >> temp_;
    appointment.setDate(temp_);
    std::cout << "Start Time: ";
    std::cin >> temp_;
    appointment.setStart(temp_);
    std::cout << "End Time: ";
    std::cin >> temp_;
    appointment.setEnd(temp_);
    saveAppointment(appointment);
    break;
  case 2:
  {
    std::vector<Appointment> appointments;
    loadAppointments(appointments);
    for (const auto &app : appointments)
    {
      std::cout << app.S.getNumber() << " - ";
      std::cout << app.L.getNumber() << " - ";
      std::cout << app.getDate() << " - ";
      std::cout << app.getStart() << " - ";
      std::cout << app.getEnd() << std::endl;
    }
  }
  break;
  case 3:
    std::cout << "Enter the Student No to remove: ";
    std::cin >> temp_;
    std::cout << "Enter the Lecturer No to remove: ";
    std::cin >> temp_2;
    deleteAppointment(temp_, temp_2);
    break;
  case 4:
    std::cout << "Enter the Student No to update: ";
    std::cin >> temp_;
    appointment.S.setNumber(temp_);
    std::cout << "Enter the Lecturer No to update: ";
    std::cin >> temp_;
    appointment.L.setNumber(temp_);
    std::cout << "Updated Appointment Date: ";
    std::cin >> temp_;
    appointment.setDate(temp_);
    std::cout << "Updated Starting Hour: ";
    std::cin >> temp_;
    appointment.setStart(temp_);
    std::cout << "Updated Ending Hour: ";
    std::cin >> temp_;
    appointment.setEnd(temp_);
    updateAppointment(appointment);
    break;
  default:
    std::cout << "Invalid choice.\n";
  }
}
