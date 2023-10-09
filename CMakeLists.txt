cmake_minimum_required(VERSION 3.26)
project(compilerPrj)

set(CMAKE_CXX_STANDARD 17)

add_executable(compilerPrj sources/main.cpp
        sources/LexicalAnalyzer.cpp
        headers/LexicalAnalyzer.h
        sources/SyntaxAnalyzer.cpp
        headers/SyntaxAnalyzer.h
        sources/Node.cpp
        headers/Node.h
        sources/SemanticAnalyzer.cpp
        headers/SemanticAnalyzer.h)
