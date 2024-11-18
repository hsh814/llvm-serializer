cmake_minimum_required(VERSION 3.25)

project(llvm-serializer)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})

# Check if using Clang or GCC
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # Enable AddressSanitizer for both compile and link stages
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

add_executable(llvm-serializer main.cpp)
target_link_libraries(llvm-serializer
  LLVMSupport
  LLVMIRReader
  LLVMAsmParser
  LLVMBitReader
  LLVMObject
)

