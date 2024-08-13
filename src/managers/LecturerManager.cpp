#include "managers/LecturerManager.hpp"

LecturerManager::LecturerManager(DatabaseManager &dbMgr) : dbManager(dbMgr)
{
  auto existingLogger = spdlog::get("LecturerManager");
  if (!existingLogger)
  {

    logger = spdlog::stdout_color_mt("LecturerManager");
    spdlog::set_level(spdlog::level::info);
  }
  else
  {
    logger = existingLogger;
  }

  // create lecturer table if not exists
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

void LecturerManager::loadLecturers()
{
  std::string selectSQL = "SELECT ID, NAME, SURNAME, DEPARTMENT, EMAIL, PHONE, CHAIR FROM LECTURER";
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
  logger->info("Displayed all lecturers from the database");
}

void LecturerManager::saveLecturer(const Lecturer &lecturer)
{
  std::string insertSQL = "INSERT OR REPLACE INTO LECTURER (ID, NAME, SURNAME, DEPARTMENT, EMAIL, PHONE, CHAIR) VALUES (?, ?, ?, ?, ?, ?, ?);";
  sqlite3_stmt *stmt = dbManager.prepareStatement(insertSQL);

  if (!stmt)
    return;

  sqlite3_bind_text(stmt, 1, lecturer.getNumber().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, lecturer.getName().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, lecturer.getSurname().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 4, lecturer.getDepartment().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 5, lecturer.getEmail().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 6, lecturer.getPhone().c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 7, lecturer.getChair().c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE)
  {
    logger->error("Could not insert lecturer: {}", dbManager.dbErrorMsg());
  }

  sqlite3_finalize(stmt);
  logger->info("Saved lecturer {} to the database", lecturer.getNumber());
}

void LecturerManager::updateLecturer(const Lecturer &lecturer)
{
  saveLecturer(lecturer);
  logger->info("Updated lecturer {} in the database", lecturer.getNumber());
}

void LecturerManager::deleteLecturer(const std::string &lecturerNumber)
{
  std::string deleteSQL = "DELETE FROM LECTURER WHERE ID = ?";
  sqlite3_stmt *stmt = dbManager.prepareStatement(deleteSQL);

  if (!stmt)
    return;

  sqlite3_bind_text(stmt, 1, lecturerNumber.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE)
  {
    logger->error("Could not delete lecturer: {}", dbManager.dbErrorMsg());
  }

  sqlite3_finalize(stmt);
  logger->info("Deleted lecturer {} from the database", lecturerNumber);
}

void LecturerManager::handleLecturerMenu()
{
  int menu;
  std::cout << "1 - Add Lecturer\n";
  std::cout << "2 - List Lecturers\n";
  std::cout << "3 - Remove Lecturer\n";
  std::cout << "4 - Update Lecturer\n";
  std::cout << "Enter your choice: ";
  std::cin >> menu;

  std::string temp_;
  Lecturer lecturer;
  switch (menu)
  {
  case 1:
    std::cout << "Lecturer No: ";
    std::cin >> temp_;
    lecturer.setNumber(temp_);
    std::cout << "Lecturer Name: ";
    std::cin >> temp_;
    lecturer.setName(temp_);
    std::cout << "Lecturer Surname: ";
    std::cin >> temp_;
    lecturer.setSurname(temp_);
    std::cout << "Lecturer Department: ";
    std::cin >> temp_;
    lecturer.setDepartment(temp_);
    std::cout << "Lecturer Email: ";
    std::cin >> temp_;
    lecturer.setEmail(temp_);
    std::cout << "Lecturer Phone: ";
    std::cin >> temp_;
    lecturer.setPhone(temp_);
    std::cout << "Lecturer Chair: ";
    std::cin >> temp_;
    lecturer.setChair(temp_);
    saveLecturer(lecturer);
    break;
  case 2:
    loadLecturers();
    break;
  case 3:
    std::cout << "Enter the Lecturer No to remove: ";
    std::cin >> temp_;
    deleteLecturer(temp_);
    break;
  case 4:
    std::cout << "Enter the Lecturer No to update: ";
    std::cin >> temp_;
    lecturer.setNumber(temp_);
    std::cout << "Updated lecturer Name: ";
    std::cin >> temp_;
    lecturer.setName(temp_);
    std::cout << "Updated lecturer Surname: ";
    std::cin >> temp_;
    lecturer.setSurname(temp_);
    std::cout << "Updated lecturer Department: ";
    std::cin >> temp_;
    lecturer.setDepartment(temp_);
    std::cout << "Updated lecturer Email: ";
    std::cin >> temp_;
    lecturer.setEmail(temp_);
    std::cout << "Updated lecturer Phone: ";
    std::cin >> temp_;
    lecturer.setPhone(temp_);
    std::cout << "Updated lecturer Chair: ";
    std::cin >> temp_;
    lecturer.setChair(temp_);
    updateLecturer(lecturer);
    break;
  default:
    std::cout << "Invalid choice.\n";
  }
}
