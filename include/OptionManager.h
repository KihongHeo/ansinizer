#ifndef OPTION_MANAGER_H
#define OPTION_MANAGER_H

#include "llvm/Support/FileSystem.h"

#include <nlohmann/json.hpp>
#include <string>

class OptionManager {
public:
  static llvm::SmallString<128> WorkingDirVec;
  static std::string InputFile;
  static std::string OutputDir;
  static nlohmann::json CompilationDB;
  static void handleOptions(int argc, char *argv[]);
};

#endif // OPTION_MANAGER_H
