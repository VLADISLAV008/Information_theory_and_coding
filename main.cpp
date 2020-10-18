#include "Huffman_coding/Archiver.h"
#include "LZW/Archiver_LZW.h"

using namespace std;

void huffman_test(bool code, int divider, string file_path) {
    auto archiver = Archiver(divider);

    if (code) {
        archiver.code(file_path);
    } else {
        archiver.decode(file_path);
    }
}

void lzw_test(bool code, int dict_capacity, string file_path) {
    auto archiver = Archiver_LZW();

    if (code) {
        archiver.code(file_path, dict_capacity);
    } else {
        archiver.decode(file_path, dict_capacity);
    }
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string mode(argv[1]);
    bool code = mode == "-c";
    int divider = atoi(argv[2]);
    string file_path(argv[3]);

    lzw_test(code, divider, file_path);
    return 0;
}
