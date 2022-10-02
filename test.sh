#!/bin/zsh

set -e

CXX=${CXX:-$(which c++)}
REFLEX=${REFLEX:-$(which reflex)}
BISON=${BISON:-$(which bison)}

LDFLAGS='-lreflex -L/opt/homebrew/Cellar/re-flex/3.2.11/lib'
CXXFLAGS='-std=c++14 -I./src -I./build -I/opt/homebrew/Cellar/re-flex/3.2.11/include'

set -x

$REFLEX -o ./build/scanner.cpp --header-file=./build/scanner.hpp ./src/scanner.lxx
$BISON --debug -o ./build/parser.cpp -d ./src/parser.yxx
$CXX -c -g ./src/main.cpp -o ./build/main.o `echo $CXXFLAGS`
$CXX -c -g ./build/scanner.cpp -o ./build/scanner.o `echo $CXXFLAGS`
$CXX -c -g ./build/parser.cpp -o ./build/parser.o `echo $CXXFLAGS`
$CXX -c -g ./src/report.cpp -o ./build/report.o `echo $CXXFLAGS`
$CXX -c -g ./src/ast.cpp -o ./build/ast.o `echo $CXXFLAGS`
$CXX    -g ./build/main.o ./build/scanner.o ./build/parser.o ./build/report.o ./build/ast.o -o ./build/testlang `echo $LDFLAGS`
./build/testlang ./src/test.tl
