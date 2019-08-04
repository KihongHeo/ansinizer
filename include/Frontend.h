#ifndef FRONTEND_H
#define FRONTEND_H

#include "clang/Parse/ParseAST.h"

#include <string>

class Frontend {
public:
  static bool Parse(std::vector<const char *> &Args,
                    const std::string &InputFile, clang::ASTConsumer *C);
};

#endif // FRONTEND_H
