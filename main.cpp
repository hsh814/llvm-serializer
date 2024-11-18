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

std::unique_ptr<llvm::Module> parseIRFile(const std::string &fileName) {
  llvm::LLVMContext context;
  llvm::SMDiagnostic err;
  std::unique_ptr<llvm::Module> module = parseIRFile(fileName, err, context);
  if (!module) {
    err.print(fileName.c_str(), errs());
    return nullptr;
  }
  return module;
}

void printModuleInfo(std::unique_ptr<llvm::Module> &module,
                     std::string &targetFunctionName) {
  llvm::Function *targetFunction = module->getFunction(targetFunctionName);
  if (!targetFunction) {
    errs() << "Function not found: " << targetFunctionName << "\n";
    return;
  }
}

int main(int argc, char **argv, char **envp) {
  if (argc < 2) {
    errs() << "Usage: " << argv[0] << " <IR file>\n";
    return 1;
  }
  std::unique_ptr<llvm::Module> module = parseIRFile(argv[1]);
  if (module) {
    module->print(outs(), nullptr);
  } else {
    errs() << "Failed to parse IR file\n";
    return 1;
  }

  // for (const auto &pair : result) {
  //   std::cout << "Argument index: " << pair.first << ", Pointer fields: ";
  // }
  return 0;
}