#include "Huffman_coding/Archiver.h"
#include "LZW/Archiver_LZW.h"
#include "Hamming_encoding/HammingEncoding.h"
#include "Cyclic_redundancy_check/CRC.h"

using namespace std;

void huffman_test(char *argv[]) {
    string mode(argv[1]);
    bool code = mode == "-c";
    int divider = atoi(argv[2]);
    string file_path(argv[3]);

    auto archiver = Archiver(divider);
    if (code) {
        archiver.code(file_path);
    } else {
        archiver.decode(file_path);
    }
}

void lzw_test(char *argv[]) {
    string mode(argv[1]);
    bool code = mode == "-c";
    int dict_capacity = atoi(argv[2]);
    string file_path(argv[3]);

    auto archiver = Archiver_LZW();
    if (code) {
        archiver.code(file_path, dict_capacity);
    } else {
        archiver.decode(file_path, dict_capacity);
    }
}

void hamming_encoding_test(char *argv[]) {
    string mode(argv[1]);
    bool code = mode == "-c";
    string bits(argv[2]);

    auto encoding = HammingEncoding();
    if (code) {
        string encoding_bits = encoding.encode(bits);
        cout << encoding_bits;
    } else {
        pair<string, string> result = encoding.decode(bits);
        cout << result.second << " " << result.first;
    }
}

void crc_test(char *argv[]) {
    string mode(argv[1]);
    bool code = mode == "-c";
    string bits(argv[2]);

    auto encoding = CRC();
    if (code) {
        string encoding_bits = encoding.encode(bits);
        cout << encoding_bits;
    } else {
        pair<string, string> result = encoding.decode(bits);
        cout << result.second << " " << result.first;
    }
}

int main(int argc, char *argv[]) {
    //lzw_test(argv);
    //huffman_test(argv);
    //hamming_encoding_test(argv);
    crc_test(argv);
    return 0;
}
