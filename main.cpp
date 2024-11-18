#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/BinaryFormat/Magic.h"
#include "llvm/Object/Archive.h"
#include "llvm/Object/Error.h"
#include "llvm/Object/ObjectFile.h"

#include <iostream>
#include <map>
#include <vector>

using namespace llvm;

std::unique_ptr<llvm::Module> parseIRFile(const std::string &fileName) {
  llvm::LLVMContext context;
  llvm::SMDiagnostic err;
  std::unique_ptr<llvm::Module> module = parseIRFile(fileName, err, context);
  // ErrorOr<std::unique_ptr<MemoryBuffer>> bufferErr =
  //     MemoryBuffer::getFileOrSTDIN(fileName);
  // std::error_code ec = bufferErr.getError();
  // if (ec) {
  //   errs() << "Error: " << ec.message() << "\n";
  //   return nullptr;
  // }
  // MemoryBufferRef Buffer = bufferErr.get()->getMemBufferRef();
  // file_magic magic = identify_magic(Buffer.getBuffer());
  // LLVMContext context;
  // if (magic == file_magic::bitcode) {
  //   SMDiagnostic Err;
  //   std::unique_ptr<llvm::Module> module(parseIR(Buffer, Err, context));
  //   if (!module) {
  //     errs() << "Error: " << Err.getMessage().str() << "\n";
  //     return nullptr;
  //   }
  //   // Do something with the module
  //   return module;
  // }
  // if (magic == file_magic::archive) {
  //   Expected<std::unique_ptr<object::Binary>> archOwner =
  //       object::createBinary(Buffer, &context);
  //   if (!archOwner)
  //     ec = errorToErrorCode(archOwner.takeError());
  //   llvm::object::Binary *arch = archOwner.get().get();
  //   if (ec) {
  //     errs() << "Error: " << ec.message() << "\n";
  //     return nullptr;
  //   }
  //   if (auto archive = dyn_cast<object::Archive>(arch)) {
  //     // Load all bitcode files into memory
  //     auto Err = Error::success();
  //     for (object::Archive::child_iterator AI = archive->child_begin(Err),
  //                                          AE = archive->child_end();
  //          AI != AE; ++AI) {

  //       StringRef memberName;
  //       std::error_code ec;
  //       ErrorOr<object::Archive::Child> childOrErr = *AI;
  //       ec = childOrErr.getError();
  //       if (ec) {
  //         errs() << "Error: " << ec.message() << "\n";
  //         return nullptr;
  //       }
  //       auto memberNameErr = childOrErr->getName();
  //       ec = memberNameErr ? std::error_code()
  //                          : errorToErrorCode(memberNameErr.takeError());
  //       if (!ec) {
  //         memberName = memberNameErr.get();
  //         outs() << "Archive member: " << memberName << "\n";
  //       } else {
  //         errs() << "Archive member does not have a name!\n";
  //         return nullptr;
  //       }

  //       Expected<std::unique_ptr<llvm::object::Binary>> child =
  //           childOrErr->getAsBinary();
  //       if (!child)
  //         ec = errorToErrorCode(child.takeError());
  //       if (ec) {
  //         // If we can't open as a binary object file its hopefully a bitcode
  //         // file
  //         auto buff = childOrErr->getMemoryBufferRef();
  //         ec = buff ? std::error_code() : errorToErrorCode(buff.takeError());
  //         if (ec) {
  //           errs() << "Failed to get MemoryBuffer: " << ec.message() << "\n";
  //           return nullptr;
  //         }

  //         if (buff) {
  //           SMDiagnostic Err;
  //           std::unique_ptr<llvm::Module> module =
  //               parseIR(buff.get(), Err, context);
  //           return module;
  //         } else {
  //           errs() << "Buffer was NULL!\n";
  //           return nullptr;
  //         }

  //       } else if (child.get()->isObject()) {
  //         errs() << "Object file " << child.get()->getFileName().str() <<
  //                    " in archive is not supported\n";
  //         return nullptr;
  //       } else {
  //         errs() << "Loading archive child with error " << ec.message() << "\n";
  //         return nullptr;
  //       }
  //     }
  //     if (Err) {
  //       errs() << "Cannot iterate over archive\n";
  //       return nullptr;
  //     }
  //   }

  //   return nullptr;
  // }
}

int main(int argc, char **argv, char **envp) {
  std::unique_ptr<llvm::Module> module = parseIRFile(argv[1]);

  // for (const auto &pair : result) {
  //   std::cout << "Argument index: " << pair.first << ", Pointer fields: ";
  // }
  return 0;
}