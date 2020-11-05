#include "HammingEncoding.h"

string HammingEncoding::encode(const string &bin_string) {
    int number_check_bits = (int) ceil(log2(bin_string.size() + log2(bin_string.size() + 1) + 1));

    string encode_bits("00");
    long long pow2 = 4;
    for (char c : bin_string) {
        if (encode_bits.size() == pow2 - 1) {
            encode_bits.push_back('0');
            pow2 *= 2;
        }
        encode_bits.push_back(c);
    }

    vector<string> bin_strings =
            get_binary_number_representation(bin_string.size() + number_check_bits + 1);

    pow2 = 1;
    for (int i = 0; i < number_check_bits; i++) {
        unsigned int check_bit = 0;
        for (int j = 0; j < encode_bits.size(); j++) {
            check_bit ^= (unsigned int) (encode_bits[j] - '0') * (bin_strings[j + 1][i] - '0');
        }
        encode_bits[pow2 - 1] = check_bit + '0';
        pow2 *= 2;
    }

    return encode_bits;
}

pair<string, string> HammingEncoding::decode(const string &bin_string) {
    vector<string> bin_strings =
            get_binary_number_representation(bin_string.size() + 1);

    int number_check_bits = (int) ceil(log2(bin_string.size() + 1));
    string check_bits;
    for (int i = 0; i < number_check_bits; i++) {
        unsigned int check_bit = 0;
        for (int j = 0; j < bin_string.size(); j++) {
            check_bit ^= (unsigned int) (bin_string[j] - '0') * (bin_strings[j + 1][i] - '0');
        }
        check_bits.push_back(check_bit + '0');
    }
    reverse(check_bits.begin(), check_bits.end());

    int index = stoi(check_bits, nullptr, 2);
    string info_message, corrected_message = bin_string;
    if (index == 0) {
        info_message = "No errors were found in the message.";
    } else {
        info_message = "An error was detected in the message on the index = " + to_string(index) + ".";
        if (corrected_message[index - 1] == '0') corrected_message[index - 1] = '1';
        else corrected_message[index - 1] = '0';
    }

    string decode_message;
    long long pow2 = 2;
    for (int i = 1; i < corrected_message.size(); i++) {
        if (i != pow2 - 1) {
            decode_message.push_back(corrected_message[i]);
        } else {
            pow2 *= 2;
        }
    }

    return make_pair(decode_message, info_message);
}

vector<string> HammingEncoding::get_binary_number_representation(int max_number) {
    vector<string> bin_strings(max_number);
    for (int i = 0; i < bin_strings.size(); i++) {
        string bin = bitset<64>(i).to_string();
        reverse(bin.begin(), bin.end());
        bin_strings[i] = bin;
    }
    return bin_strings;
}
