cmake_minimum_required(VERSION 3.26)
project(compilerPrj)

set(CMAKE_CXX_STANDARD 17)

add_executable(compilerPrj main.cpp
        sources/LexicalAnalyzer.cpp
        headers/LexicalAnalyzer.h
        SyntaxAnalyzer.cpp
        SyntaxAnalyzer.h
        Node.cpp
        Node.h)
