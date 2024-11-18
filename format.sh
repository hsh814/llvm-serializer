#!/bin/bash
cd "$(dirname "$0")"
clang-format -i --style=file main.cpp