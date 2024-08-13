#ifndef LECTURER_MANAGER_HPP
#define LECTURER_MANAGER_HPP

#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "core/Lecturer.hpp"
#include "DatabaseManager.hpp"

class LecturerManager
{
public:
  LecturerManager(DatabaseManager &dbMgr);

  void loadLecturers();
  void saveLecturer(const Lecturer &lecturer);
  void updateLecturer(const Lecturer &lecturer);
  void deleteLecturer(const std::string &lecturerNumber);
  void handleLecturerMenu();

private:
  DatabaseManager &dbManager;
  std::shared_ptr<spdlog::logger> logger;
};

#endif // LECTURER_MANAGER_HPP
