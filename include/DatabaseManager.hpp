#ifndef DATABASE_MANAGER_HPP
#define DATABASE_MANAGER_HPP

#include <iostream>
#include <string>
#include <sqlite3.h>
#include <memory>
#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class DatabaseManager
{
public:
  DatabaseManager(const std::string &dbPath);
  ~DatabaseManager();

  // void executeSQL(const std::string &sql);
  std::vector<std::map<std::string, std::string>> executeQuery(const std::string &query);

  bool executeSQL(const std::string &sql);
  bool executeSQLWithCallback(const std::string &sql, int (*callback)(void *, int, char **, char **), void *data);
  sqlite3_stmt *prepareStatement(const std::string &sql);
  std::string dbErrorMsg() const;

private:
  sqlite3 *db;
  std::string databasePath;
  std::shared_ptr<spdlog::logger> logger;
};

#endif // DATABASE_MANAGER_HPP
