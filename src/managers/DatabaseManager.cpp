#include "DatabaseManager.hpp"

DatabaseManager::DatabaseManager(const std::string &dbPath) : databasePath(dbPath)
{
  int rc = sqlite3_open(databasePath.c_str(), &db);
  auto existingLogger = spdlog::get("DatabaseManager");
  if (!existingLogger)
  {

    logger = spdlog::stdout_color_mt("DatabaseManager");
    spdlog::set_level(spdlog::level::info);
  }
  else
  {
    logger = existingLogger;
  }

  if (rc)
  {
    logger->error("Can't open database: {}", sqlite3_errmsg(db));
    db = nullptr;
  }
  else
  {
    logger->info("Opened database successfully: {}", databasePath);
  }
}

DatabaseManager::~DatabaseManager()
{
  if (db)
  {
    sqlite3_close(db);
    logger->info("Database closed: {}", databasePath);
  }
}

bool DatabaseManager::executeSQL(const std::string &sql)
{
  char *errMsg = 0;
  int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

  if (rc != SQLITE_OK)
  {
    logger->error("SQL error: {}", errMsg);
    sqlite3_free(errMsg);
    return false;
  }

  logger->info("SQL executed successfully: {}", sql);
  return true;
}

std::vector<std::map<std::string, std::string>> DatabaseManager::executeQuery(const std::string &query)
{
  std::vector<std::map<std::string, std::string>> results;
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
  {
    std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    return results;
  }

  int colCount = sqlite3_column_count(stmt);
  while (sqlite3_step(stmt) == SQLITE_ROW)
  {
    std::map<std::string, std::string> row;
    for (int i = 0; i < colCount; ++i)
    {
      const char *colName = sqlite3_column_name(stmt, i);
      const char *colValue = reinterpret_cast<const char *>(sqlite3_column_text(stmt, i));
      row[colName] = colValue ? colValue : "";
    }
    results.push_back(row);
  }

  sqlite3_finalize(stmt);
  return results;
}

bool DatabaseManager::executeSQLWithCallback(const std::string &sql, int (*callback)(void *, int, char **, char **), void *data)
{
  char *errMsg = 0;
  int rc = sqlite3_exec(db, sql.c_str(), callback, data, &errMsg);

  if (rc != SQLITE_OK)
  {
    logger->error("SQL error: {}", errMsg);
    sqlite3_free(errMsg);
    return false;
  }

  logger->info("SQL executed with callback successfully: {}", sql);
  return true;
}

sqlite3_stmt *DatabaseManager::prepareStatement(const std::string &sql)
{
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  if (rc != SQLITE_OK)
  {
    logger->error("Failed to prepare statement: {}", sqlite3_errmsg(db));
    return nullptr;
  }

  return stmt;
}

std::string DatabaseManager::dbErrorMsg() const
{
  return sqlite3_errmsg(this->db);
}
