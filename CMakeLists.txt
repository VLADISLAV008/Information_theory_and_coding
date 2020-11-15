cmake_minimum_required(VERSION 3.16)
project(Information_theory_and_coding)

set(CMAKE_CXX_STANDARD 17)

add_executable(Information_theory_and_coding "main.cpp" "Huffman_coding/Archiver.cpp" "Huffman_coding/Archiver.h" LZW/Archiver_LZW.cpp LZW/Archiver_LZW.h Hamming_encoding/HammingEncoding.cpp Hamming_encoding/HammingEncoding.h Cyclic_redundancy_check/CRC.cpp Cyclic_redundancy_check/CRC.h Cyclic_redundancy_check/BinaryPolynomial.h)