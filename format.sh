#!/bin/bash
cd "$(dirname "$0")"
clang-format -i --style=file src/*.cpp
clang-format -i --style=file runtime/*.c