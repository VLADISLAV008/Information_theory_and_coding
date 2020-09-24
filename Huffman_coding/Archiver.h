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

struct Node {
    string str;
    long long frequency;
    Node *left;
    Node *right;
};

class Archiver {
private:
    int divider;
    char separate_symbol = 0;
    char end_of_tree_symbol = 3;

    string read_from_file(const string &file);

    void write_to_file(const string &file, const string &text);

    unordered_map<string, long long> get_frequencies_of_occurrence(const string &text) const;

    Node *build_tree(unordered_map<string, long long> &frequencies);

    Node *build_tree(vector<string> &nodes);

    string tree_to_str(const string &file, Node *tree);

    void get_encodings(Node *node, const string &code, unordered_map<string, string> &encodings);

    string code_message(const string &text, unordered_map<string, string> &encodings);

public :
    explicit Archiver(int divider);

    void setDivider(int divider);

    void code(const string &file);

    void decode(const string &file);
};
