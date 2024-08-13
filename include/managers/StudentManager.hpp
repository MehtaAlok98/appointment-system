#ifndef STUDENT_MANAGER_HPP
#define STUDENT_MANAGER_HPP

#include <vector>
#include <iostream>
#include <sqlite3.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "DatabaseManager.hpp"
#include "core/Student.hpp"

class StudentManager
{
public:
  StudentManager(DatabaseManager &dbMgr);

  void loadStudents();
  void saveStudent(const Student &student);
  void updateStudent(const Student &student);
  void deleteStudent(const std::string &studentNumber);
  void handleStudentMenu();

private:
  DatabaseManager &dbManager;
  std::shared_ptr<spdlog::logger> logger;
};

#endif // STUDENT_MANAGER_HPP
