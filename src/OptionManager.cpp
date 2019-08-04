#include "OptionManager.h"

#include "llvm/Support/raw_ostream.h"

#include <fstream>

llvm::SmallString<128> OptionManager::WorkingDirVec;
std::string OptionManager::InputFile = "";
std::string OptionManager::OutputDir = "sparrow-out";
nlohmann::json OptionManager::CompilationDB = nullptr;

void OptionManager::handleOptions(int argc, char *argv[]) {
  if (argc < 2) {
    llvm::errs() << "Invalid Arguments\n";
    exit(1);
  }

  llvm::SmallString<128> OutputDirVec(OutputDir);
  llvm::sys::fs::make_absolute(OutputDirVec);
  OutputDir = OutputDirVec.str();

  llvm::sys::fs::current_path(WorkingDirVec);

  std::ifstream IF(argv[1]);
  IF >> CompilationDB;
}
