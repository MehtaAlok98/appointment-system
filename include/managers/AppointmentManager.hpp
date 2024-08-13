#ifndef APPOINTMENTMANAGER_HPP
#define APPOINTMENTMANAGER_HPP

#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "core/Appointment.hpp"
#include "DatabaseManager.hpp"
#include "core/Student.hpp"
#include "core/Lecturer.hpp"

class AppointmentManager
{
public:
  AppointmentManager(DatabaseManager &dbMgr);

  void loadAppointments(std::vector<Appointment> &appointments);
  void saveAppointment(const Appointment &appointment);
  void updateAppointment(const Appointment &appointment);
  void deleteAppointment(const std::string &studentNumber, const std::string &lecturerNumber);
  void handleAppointmentMenu();

private:
  DatabaseManager &dbManager;
  std::shared_ptr<spdlog::logger> logger;
};

#endif // APPOINTMENTMANAGER_HPP
