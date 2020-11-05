#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <bitset>

using namespace std;

class HammingEncoding {
private:
    static vector<string> get_binary_number_representation(int max_number);
public :
    string encode(const string &bin_string);

    pair<string,string> decode(const string &bin_string);
};