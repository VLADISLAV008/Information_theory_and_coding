cmake_minimum_required(VERSION 3.16)
project(Information_theory_and_coding)

set(CMAKE_CXX_STANDARD 17)

add_executable(Information_theory_and_coding "main.cpp" "Huffman_coding/Archiver.cpp" "Huffman_coding/Archiver.h" LZW/Archiver_LZW.cpp LZW/Archiver_LZW.h)