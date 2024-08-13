#include "config/ManageGlobals.hpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdlib>

// Definitions for parseArguments, readConfig, and applyConfig
void ConfigManager::parseArgumentsAndSetGlobals(int argc, char *argv[])
{
  bool logging_enabled = false;
  std::string env_path = "resources/config.env";
  std::string db_path = "resources/appointments.db";
  std::string log_path = "resources/log.txt";
  std::string log_to = "";
  if (argc == 1)
    readEnvAndSetGlobals(env_path);

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg == "-env" && i + 1 < argc)
    {
      env_path = argv[++i];
      readEnvAndSetGlobals(env_path);
    }
    else if (arg == "-log" && i + 1 < argc)
    {
      logging_enabled = (argv[++i] == "true" ? true : false);
    }
    else if (arg == "-db" && i + 1 < argc)
    {
      db_path = argv[++i];
    }
    else if (arg == "-lp" && i + 1 < argc)
    {
      log_path = argv[++i];
    }
    else if (arg == "-lt" && i + 1 < argc)
    {
      log_to = argv[++i];
    }
  }
  // accepts args -env resources/config.env -db resources/appointments.db -log true -lp log.txt -lt CONSONL_FILE
}

void ConfigManager::readEnvAndSetGlobals(const std::string &filepath)
{
  std::map<std::string, std::string> _env;

  std::ifstream file(filepath);

  if (!file.is_open())
  {
    std::cerr << "Could not open the .env file: " << filepath << std::endl;
  }

  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    std::string key, value;

    if (std::getline(iss, key, '=') && std::getline(iss, value))
    {
      _env[key] = value;
    }
  }

  logging_enabled = (_env.at("logging_enabled") == "true" ? true : false);
  db_path = _env.at("db_path");
  log_path = _env.at("log_path");
  log_to = _env.at("log_to");

  file.close();
}
