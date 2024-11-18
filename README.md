# llvm-serializer
Parse LLVM IR and generate serialization code.

## Build
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j 4
```

## Usage
```bash
./build/llvm-serializer test.ll target_function
```

## Contribution
Before commit, run `./format.sh`.