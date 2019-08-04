#include "FileManager.h"
#include "Frontend.h"
#include "OptionManager.h"
#include "Transformation.h"

void initialize() { FileManager::Initialize(); }

std::string getTargetDir(std::string &Target) {
  std::string Cwd = OptionManager::WorkingDirVec.str();
  std::string Diff = Target.substr(Cwd.size(), Target.size());
  std::string TargetDir = OptionManager::OutputDir + "/preprocess/" + Diff;
  return TargetDir;
}

int main(int argc, char *argv[]) {
  OptionManager::handleOptions(argc, argv);
  initialize();
  for (auto &Entry : OptionManager::CompilationDB) {
    std::string Directory = Entry["directory"];
    std::string InputFile = Entry["file"];
    std::string TargetDir = getTargetDir(Directory);
    llvm::sys::fs::create_directories(TargetDir);
    llvm::sys::fs::set_current_path(Directory);

    std::vector<std::string> StrArgs;
    for (auto &A : Entry["arguments"]) {
      StrArgs.push_back(A);
    }
    std::vector<const char *> Args;
    for (auto &S : StrArgs) {
      if (S == "-g")
        continue;
      if (S == "-c")
        continue;
      std::string Ext = ".c";
      if (S.size() > 2 && std::equal(Ext.rbegin(), Ext.rend(), S.rbegin()))
        continue;
      llvm::errs() << S << "\n";
      Args.push_back(S.c_str());
    }
    Transformation *TR = new Transformation();
    Frontend::Parse(Args, InputFile, TR);
    break;
  }
  return 0;
}
