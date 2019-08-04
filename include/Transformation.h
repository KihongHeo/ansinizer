#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Expr.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Rewrite/Core/Rewriter.h"

class TransformationVisitor;

class Transformation : public clang::ASTConsumer {
  friend class TransformationVisitor;

public:
  Transformation() : Visitor(NULL) {}
  ~Transformation() { delete Visitor; }

protected:
  virtual void Initialize(clang::ASTContext &Ctx) override;
  virtual bool HandleTopLevelDecl(clang::DeclGroupRef D) override;
  virtual void HandleTranslationUnit(clang::ASTContext &Ctx) override;

  //  std::vector<clang::Stmt *> getAllChildren(clang::Stmt *S);
  /*
    void removeSourceText(const clang::SourceLocation &B,
                          const clang::SourceLocation &E);
  */
  clang::ASTContext *Context;
  clang::Rewriter TheRewriter;
  TransformationVisitor *Visitor;
};

class TransformationVisitor
    : public clang::RecursiveASTVisitor<TransformationVisitor> {
public:
  TransformationVisitor(Transformation *R) : Consumer(R) {}

  bool VisitFunctionDecl(clang::FunctionDecl *FD);

private:
  Transformation *Consumer;
};

#endif // TRANSFORMATION_H
