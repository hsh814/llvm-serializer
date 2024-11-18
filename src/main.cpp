#include "llvm/BinaryFormat/Magic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Object/Archive.h"
#include "llvm/Object/Error.h"
#include "llvm/Object/ObjectFile.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include <iostream>
#include <map>
#include <memory>
#include <vector>

using namespace llvm;

std::unique_ptr<llvm::Module> parseIRFile(const std::string fileName,
                                          llvm::LLVMContext &context) {
  llvm::SMDiagnostic err;
  std::unique_ptr<llvm::Module> module =
      llvm::parseIRFile(fileName, err, context);
  if (!module) {
    err.print(fileName.c_str(), errs());
    return nullptr;
  }
  return module;
}

void printArgTypeInfo(std::unique_ptr<llvm::Module> &module,
                      std::string targetFunctionName) {
  llvm::Function *targetFunction = module->getFunction(targetFunctionName);
  if (!targetFunction) {
    errs() << "Function not found: " << targetFunctionName << "\n";
    return;
  }
  for (auto &arg : targetFunction->args()) {
    std::string argName = arg.getName().str();
    llvm::Type *argType = arg.getType();
    std::string argTypeName;
    llvm::raw_string_ostream rso(argTypeName);
    argType->print(rso);
    rso.str();
    errs() << "Argument name: " << argName << ", type: " << argTypeName << "\n";
    if (argType->isPointerTy()) {
      // Save data if not null
    } else {
      // Save data
    }
  }
}

int main(int argc, char **argv, char **envp) {
  if (argc < 3) {
    errs() << "Usage: " << argv[0] << " <IR file> <Target function>\n";
    return 1;
  }
  llvm::LLVMContext context;
  std::unique_ptr<llvm::Module> module = parseIRFile(argv[1], context);
  if (module) {
    printArgTypeInfo(module, argv[2]);
  } else {
    errs() << "Failed to parse IR file\n";
    return 1;
  }
  return 0;
}