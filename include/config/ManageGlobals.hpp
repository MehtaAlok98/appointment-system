#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <string>
#include <map>
#include "Globals.hpp"

class ConfigManager
{
private:
  static void readEnvAndSetGlobals(const std::string &filepath);

public:
  static void parseArgumentsAndSetGlobals(int argc, char *argv[]);
};

#endif // CONFIG_MANAGER_HPP
