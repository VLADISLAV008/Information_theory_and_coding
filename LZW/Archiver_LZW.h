#pragma once

#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <bitset>

using namespace std;

class Archiver_LZW {
private:
    char separate_symbol = 0;

    string read_from_file(const string &file);

    string generate_file_name(const string &file);

    void write_to_file(const string &file, const string &text);

    unordered_map<string, long long> get_init_dict(const string &text);

    string code_message(const string &text, unordered_map<string, long long> &dict, int dict_capacity);

    string code_indexes(const vector<long long> &indexes, int dict_capacity);

    vector<int> convert_bits_to_indexes(const string &bits, int dict_capacity);

public :
    bool code(const string &file, int dict_capacity);

    void decode(const string &file, int dict_capacity);
};
