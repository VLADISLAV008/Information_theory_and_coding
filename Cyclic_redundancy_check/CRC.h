#pragma once

#include "BinaryPolynomial.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

class CRC {
private:
    BinaryPolynomial *polynomial;
public :
    CRC();

    string encode(const string &bin_string);

    pair<string, string> decode(const string &bin_string);

    virtual ~CRC();
};
