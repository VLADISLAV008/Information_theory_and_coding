#include "Archiver_LZW.h"

string Archiver_LZW::read_from_file(const string &file) {
    ifstream infile(file, ios::binary);

    string text;
    stringstream ss;
    ss << infile.rdbuf();
    text = ss.str();

    infile.close();
    return text;
}

bool Archiver_LZW::code(const string &file, int dict_capacity) {
    string text = read_from_file(file);
    unordered_map<string, long long> dict = get_init_dict(text);

    if (dict.size() > pow(2, dict_capacity)) {
        return false;
    }
    string code = code_message(text, dict, dict_capacity);
    string code_file = generate_file_name(file);

    write_to_file(code_file, code);

    return true;
}

unordered_map<string, long long> Archiver_LZW::get_init_dict(const string &text) {
    unordered_map<string, long long> dict;
    for (char i : text) {
        string c(1, i);
        if (dict.find(c) == dict.end()) {
            dict[c] = dict.size();
        }
    }
    return dict;
}

string Archiver_LZW::code_message(const string &text, unordered_map<string, long long> &dict, int dict_capacity) {
    long long dict_max_size = pow(2, dict_capacity);

    string code(dict.size(), ' ');
    for (auto &it : dict) {
        code[it.second] = it.first[0];
    }
    code.push_back(separate_symbol);

    string buf = "";
    vector<long long> indexes;
    for (char i : text) {
        buf.push_back(i);
        if (dict.find(buf) == dict.end()) {
            if (dict.size() < dict_max_size) {
                dict[buf] = dict.size();
            }

            buf.erase(buf.size() - 1);
            indexes.push_back(dict[buf]);

            buf = "";
            buf.push_back(i);
        }
    }
    indexes.push_back(dict[buf]);

    string indexes_code = code_indexes(indexes, dict_capacity);
    code.append(indexes_code);
    return code;
}

string Archiver_LZW::code_indexes(const vector<long long int> &indexes, int dict_capacity) {
    string code;
    string buf;
    for (long long index : indexes) {
        for (int j = 1 << (dict_capacity - 1); j > 0; j = j / 2) {
            (index & j) ? buf.append("1") : buf.append("0");
            if (buf.size() == 8) {
                char c = (char) stoi(buf, nullptr, 2);
                code.push_back(c);
                buf = "";
            }
        }
    }
    buf.push_back(separate_symbol);
    code = buf + code;
    return code;
}

string Archiver_LZW::generate_file_name(const string &file) {
    string code_file;
    for (int i = 0; i < file.length() - 4; i++) {
        code_file.push_back(file[i]);
    }
    code_file.append(".zipped");

    return code_file;
}

void Archiver_LZW::write_to_file(const string &file, const string &text) {
    ofstream outfile(file, ios::binary);
    outfile << text;
    outfile.close();
}

void Archiver_LZW::decode(const string &file, int dict_capacity) {
    string content = read_from_file(file);

    unordered_map<int, string> dict;
    int index = 0;
    while (content[index] != separate_symbol) {
        string s(1, content[index]);
        dict[index] = s;
        index++;
    }
    index++;

    string end_code_message;
    while (content[index] != separate_symbol) {
        end_code_message.push_back(content[index]);
        index++;
    }
    index++;

    string buf;
    for (int i = index; i < content.length(); i++) {
        buf += bitset<8>(content[i]).to_string();
    }
    buf.append(end_code_message);

    string message;
    vector<int> indexes = convert_bits_to_indexes(buf, dict_capacity);
    string prev;
    for (int i = 0; i < indexes.size(); i++) {
        string cur = dict[indexes[i]];
        if (cur.empty()) {
            cur = prev + prev[0];
            dict[indexes[i]] = cur;
        } else {
            if (i != 0) {
                dict[dict.size()] = prev + cur[0];
            }
            prev = cur;
        }

        message.append(cur);
        prev = cur;
    }

    string decode_file;
    for (int i = 0; i < file.length() - 7; i++) {
        decode_file.push_back(file[i]);
    }
    decode_file.append(".unzipped");

    write_to_file(decode_file, message);
}

vector<int> Archiver_LZW::convert_bits_to_indexes(const string &bits, int dict_capacity) {
    vector<int> indexes;
    for (int i = 0; i < bits.size(); i += dict_capacity) {
        string buf;
        for (int j = i; j < i + dict_capacity; j++) {
            buf.push_back(bits[j]);
        }
        int index = stoi(buf, nullptr, 2);
        indexes.push_back(index);
    }
    return indexes;
}
