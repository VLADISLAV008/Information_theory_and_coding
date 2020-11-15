#include "CRC.h"

string CRC::encode(const string &bin_string) {
    vector<int> coef;
    for (char c: bin_string) {
        coef.push_back(c - '0');
    }
    BinaryPolynomial message(coef);

    string crc = (message % *this->polynomial).to_string();
    string zeros = string(polynomial->get_size() - crc.size() - 1, '0');

    return bin_string + zeros + crc;
}

pair<string, string> CRC::decode(const string &bin_string) {
    string decode_message(bin_string.begin(), bin_string.end() - polynomial->get_size() + 1);
    string decode_crc(bin_string.end() - polynomial->get_size() + 1, bin_string.end());
    string crc = (BinaryPolynomial(decode_message) % *this->polynomial).to_string();
    string zeros = string(polynomial->get_size() - crc.size() - 1, '0');

    string info_message;
    if (zeros + crc == decode_crc) {
        info_message = "No errors were found in the message. The CRC code = " + zeros + crc + ".";
    } else {
        info_message = "An error was detected in the message. The CRC code = " + zeros + crc + ".";
        decode_message = "";
    }

    return make_pair(decode_message, info_message);
}

CRC::CRC() {
    vector<int> coef = {1, 0, 1, 0, 0, 1};
    this->polynomial = new BinaryPolynomial(coef);
}

CRC::~CRC() {
    delete polynomial;
}
