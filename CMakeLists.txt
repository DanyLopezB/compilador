cmake_minimum_required(VERSION 3.8)
project(compilador)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp lexico.h lexico.cpp sintactico.cpp sintactico.h codigo.cpp codigo.h archivoFuente.txt salida.txt)
add_executable(compilador ${SOURCE_FILES})