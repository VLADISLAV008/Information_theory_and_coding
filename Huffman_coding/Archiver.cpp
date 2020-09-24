#include "Archiver.h"
#include <utility>


Archiver::Archiver(int divider) : divider(divider) {}

void Archiver::setDivider(int divider) {
    this->divider = divider;
}

void Archiver::code(const string &file) {
    string text = read_from_file(file);

    unordered_map<string, long long> frequencies =
            get_frequencies_of_occurrence(text);
    Node *root = build_tree(frequencies);

    unordered_map<string, string> encodings;
    get_encodings(root, "", encodings);

    string code_file;
    for (int i = 0; i < file.length() - 4; i++) {
        code_file.push_back(file[i]);
    }
    code_file.append(".zipped");

    string tree = tree_to_str(code_file, root);
    string code = code_message(text, encodings);
    write_to_file(code_file, tree + code);
}

void Archiver::decode(const string &file) {
    string content = read_from_file(file);

    vector<string> nodes;
    string node;
    int index = 0;
    while (content[index] != end_of_tree_symbol) {
        if (content[index] == separate_symbol) {
            nodes.push_back(node);
            node = "";
        } else {
            node.push_back(content[index]);
        }
        index++;
    }
    index += 2;

    string end_code_message;
    while (content[index] != '$') {
        end_code_message.push_back(content[index]);
        index++;
    }
    index++;

    string code_message;
    for (int i = index; i < content.length(); i++) {
        code_message.push_back(content[i]);
    }

    Node *root = build_tree(nodes);

    string message, buf;
    Node *cur = root;
    for (char c : code_message) {
        buf = bitset<8>(c).to_string();

        for (int i = 0; i < buf.length(); ++i) {
            if (buf[i] == '0') {
                cur = cur->left;
            } else {
                cur = cur->right;
            }
            if (cur->left == nullptr) {
                message.append(cur->str);
                cur = root;
            }
        }
    }

    for (int i = 0; i < end_code_message.length(); ++i) {
        if (end_code_message[i] == '0') {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
        if (cur->left == nullptr) {
            message.append(cur->str);
            cur = root;
        }
    }

    string decode_file;
    for (int i = 0; i < file.length() - 7; i++) {
        decode_file.push_back(file[i]);
    }
    decode_file.append(".unzipped");
    write_to_file(decode_file, message);
}

string Archiver::read_from_file(const string &file) {
    ifstream infile(file, ios::binary);

    string text;
    stringstream ss;
    ss << infile.rdbuf();
    text = ss.str();

    infile.close();
    return text;
}

void Archiver::write_to_file(const string &file, const string &text) {
    ofstream outfile(file, ios::binary);
    outfile << text;
    outfile.close();
}

unordered_map<string, long long> Archiver::get_frequencies_of_occurrence(const string &text) const {
    unordered_map<string, long long> frequencies;

    string buf;
    for (char i : text) {
        buf.push_back(i);
        if (buf.length() == this->divider) {
            if (frequencies.count(buf)) {
                frequencies[buf]++;
            } else {
                frequencies[buf] = 1;
            }
            buf = "";
        }
    }
    if (buf.length() > 0) {
        if (frequencies.count(buf)) {
            frequencies[buf]++;
        } else {
            frequencies[buf] = 1;
        }
    }

    return frequencies;
}

Node *Archiver::build_tree(unordered_map<string, long long> &frequencies) {
    auto cmp = [](Node *left, Node *right) { return left->frequency > right->frequency; };
    priority_queue<Node *, vector<Node *>, decltype(cmp)> nodes(cmp);

    for (const auto &n : frequencies) {
        Node *node = new Node{n.first, n.second, nullptr, nullptr};
        nodes.push(node);
    }

    while (nodes.size() > 1) {
        Node *node1 = nodes.top();
        nodes.pop();

        Node *node2 = nodes.top();
        nodes.pop();

        Node *node = new Node{node1->str + node2->str, node1->frequency + node2->frequency, node1, node2};
        nodes.push(node);
    }

    return nodes.top();
}

Node *Archiver::build_tree(vector<string> &nodes) {
    Node *root = new Node();

    queue<Node *> q;
    q.push(root);
    for (string str: nodes) {
        Node *node = q.front();
        q.pop();

        node->str = str;
        if (str == "") {
            node->left = new Node();
            node->right = new Node();
            q.push(node->left);
            q.push(node->right);
        }
    }

    return root;
}

string Archiver::tree_to_str(const string &file, Node *tree) {
    string result;
    queue<Node *> queue;
    queue.push(tree);

    while (!queue.empty()) {
        Node *cur = queue.front();
        queue.pop();

        if (cur->left != nullptr) {
            queue.push(cur->left);
            queue.push(cur->right);

            result.push_back(separate_symbol);
        } else {
            result.append(cur->str + separate_symbol);
        }
    }

    result.push_back(end_of_tree_symbol);
    result.push_back('\n');
    return result;
}

void Archiver::get_encodings(Node *node, const string &code, unordered_map<string, string> &encodings) {
    if (node->left == nullptr) {
        encodings[node->str] = code;
        return;
    }

    get_encodings(node->left, code + "0", encodings);
    get_encodings(node->right, code + "1", encodings);
}

string Archiver::code_message(const string &text, unordered_map<string, string> &encodings) {
    string code, buf, buf_code;
    for (char i : text) {
        buf.push_back(i);
        if (buf.length() == this->divider) {
            for (char j : encodings[buf]) {
                buf_code.push_back(j);
                if (buf_code.size() == 8) {
                    char c = (char) stoi(buf_code, nullptr, 2);
                    code.push_back(c);
                    buf_code = "";
                }
            }
            buf = "";
        }
    }
    if (!buf.empty()) {
        for (char j : encodings[buf]) {
            buf_code.push_back(j);
            if (buf_code.size() == 8) {
                char c = (char) stoi(buf_code, nullptr, 2);
                code.push_back(c);
                buf_code = "";
            }
        }
    }

    return buf_code + '$' + code;
}


