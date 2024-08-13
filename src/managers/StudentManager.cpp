#include "managers/StudentManager.hpp"

StudentManager::StudentManager(DatabaseManager &dbMgr) : dbManager(dbMgr)
{
  auto existingLogger = spdlog::get("StudentManager");
  if (!existingLogger)
  {

    logger = spdlog::stdout_color_mt("StudentManager");
    spdlog::set_level(spdlog::level::info);
  }
  else
  {
    logger = existingLogger;
  }

  //create student table if not exists
  std::string setupSQL = "CREATE TABLE IF NOT EXISTS LECTURER (ID TEXT PRIMARY KEY, NAME TEXT, SURNAME TEXT, DEPARTMENT TEXT, EMAIL TEXT, PHONE TEXT, CHAIR TEXT);";
  sqlite3_stmt *stmt = dbManager.prepareStatement(setupSQL);
  if (sqlite3_step(stmt) != SQLITE_DONE)
  {
    logger->error("Failed to create LECTURER table: {}", dbManager.dbErrorMsg());
  }
  sqlite3_finalize(stmt);

  // check if there is any table in the database or not
  std::string checkTablesSQL = "SELECT name FROM sqlite_master WHERE type='table';";
  sqlite3_stmt *stmt1 = dbManager.prepareStatement(checkTablesSQL);
  while (sqlite3_step(stmt1) == SQLITE_ROW)
  {
    std::cout << "Table exists: " << reinterpret_cast<const char *>(sqlite3_column_text(stmt1, 0)) << std::endl;
  }
  sqlite3_finalize(stmt1);
}

void StudentManager::loadStudents()
{
  std::string selectSQL = "SELECT ID, NAME, SURNAME, DEPARTMENT, EMAIL, PHONE, YEAR FROM STUDENT";
  sqlite3_stmt *stmt = dbManager.prepareStatement(selectSQL);

  if (!stmt)
    return;

  while (sqlite3_step(stmt) == SQLITE_ROW)
  {
    std::cout << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)) << " - ";
    std::cout << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)) << " - ";
    std::cout << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)) << " - ";
    std::cout << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)) << " - ";
    std::cout << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)) << " - ";
    std::cout << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5)) << " - ";
    std::cout << reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6)) << std::endl;
  }

  sqlite3_finalize(stmt);
  logger->info("Displayed all students from the database");
}

void StudentManager::saveStudent(const Student &student)
{
  std::string insertSQL = "INSERT OR REPLACE INTO STUDENT (ID, NAME, SURNAME, DEPARTMENT, EMAIL, PHONE, YEAR) VALUES (?, ?, ?, ?, ?, ?, ?);";
  sqlite3_stmt *stmt = dbManager.prepareStatement(insertSQL);

  if (!stmt)
    return;

  sqlite3_bind_text(stmt, 1, student.getNumber().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, student.getName().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, student.getSurname().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, student.getDepartment().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, student.getEmail().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 6, student.getPhone().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 7, student.getYear().c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE)
  {
    logger->error("Could not insert student: {}", dbManager.dbErrorMsg());
  }

  sqlite3_finalize(stmt);
  logger->info("Saved student {} to the database", student.getNumber());
}

void StudentManager::updateStudent(const Student &student)
{
  saveStudent(student);
  logger->info("Updated student {} in the database", student.getNumber());
}

void StudentManager::deleteStudent(const std::string &studentNumber)
{
  std::string deleteSQL = "DELETE FROM STUDENT WHERE ID = ?";
  sqlite3_stmt *stmt = dbManager.prepareStatement(deleteSQL);

  if (!stmt)
    return;

  sqlite3_bind_text(stmt, 1, studentNumber.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE)
  {
    logger->error("Could not delete student: {}", dbManager.dbErrorMsg());
  }

  sqlite3_finalize(stmt);
  logger->info("Deleted student {} from the database", studentNumber);
}

void StudentManager::handleStudentMenu()
{
  int menu;
  std::cout << "1 - Add student\n";
  std::cout << "2 - List students\n";
  std::cout << "3 - Remove student\n";
  std::cout << "4 - Update student\n";
  std::cout << "Enter your choice: ";
  std::cin >> menu;

  std::string temp_;
  Student student;
  switch (menu)
  {
  case 1:
    std::cout << "Student No: ";
    std::cin >> temp_;
    student.setNumber(temp_);
    std::cout << "Student Name: ";
    std::cin >> temp_;
    student.setName(temp_);
    std::cout << "Student Surname: ";
    std::cin >> temp_;
    student.setSurname(temp_);
    std::cout << "Student Department: ";
    std::cin >> temp_;
    student.setDepartment(temp_);
    std::cout << "Student Email: ";
    std::cin >> temp_;
    student.setEmail(temp_);
    std::cout << "Student Phone: ";
    std::cin >> temp_;
    student.setPhone(temp_);
    std::cout << "Student Year: ";
    std::cin >> temp_;
    student.setYear(temp_);
    saveStudent(student);
    break;
  case 2:
    loadStudents();
    break;
  case 3:
    std::cout << "Enter the student No to remove: ";
    std::cin >> temp_;
    deleteStudent(temp_);
    break;
  case 4:
    std::cout << "Enter the student No to update: ";
    std::cin >> temp_;
    student.setNumber(temp_);
    std::cout << "Updated student Name: ";
    std::cin >> temp_;
    student.setName(temp_);
    std::cout << "Updated student Surname: ";
    std::cin >> temp_;
    student.setSurname(temp_);
    std::cout << "Updated student Department: ";
    std::cin >> temp_;
    student.setDepartment(temp_);
    std::cout << "Updated student Email: ";
    std::cin >> temp_;
    student.setEmail(temp_);
    std::cout << "Updated student Phone: ";
    std::cin >> temp_;
    student.setPhone(temp_);
    std::cout << "Updated student Year: ";
    std::cin >> temp_;
    student.setYear(temp_);
    updateStudent(student);
    break;
  default:
    std::cout << "Invalid choice.\n";
  }
}
