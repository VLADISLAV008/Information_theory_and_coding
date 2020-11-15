#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

class BinaryPolynomial {
private:
    vector<int> coef;

public :
    explicit BinaryPolynomial(vector<int> coef) {
        this->coef = move(coef);
    }

    explicit BinaryPolynomial(const string& coef) {
        for (char c: coef) {
            this->coef.push_back(c - '0');
        }
    }

    BinaryPolynomial operator-(BinaryPolynomial const &obj) const {
        vector<int> res;

        if (this->coef.size() > obj.coef.size()) {
            res = this->coef;
            for (int i = 0; i < obj.coef.size(); i++) {
                res[i] = res[i] ^ obj.coef[i];
            }
        } else {
            res = obj.coef;
            for (int i = 0; i < this->coef.size(); i++) {
                res[i] = res[i] ^ this->coef[i];
            }
        }

        while (res.size() > 1 && res[res.size() - 1] == 0) {
            res.erase(--res.end());
        }

        return BinaryPolynomial(res);
    }

    BinaryPolynomial shift(unsigned int pow) const {
        vector<int> res;
        for (int i = 0; i < pow; i++) {
            res.push_back(0);
        }
        res.insert(res.end(), this->coef.begin(), this->coef.end());
        return BinaryPolynomial(res);
    }

    BinaryPolynomial operator%(BinaryPolynomial const &obj) const {
        BinaryPolynomial this_copy(this->coef);
        while (this_copy.coef.size() >= obj.coef.size()) {
            unsigned int pow = this_copy.coef.size() - obj.coef.size();
            this_copy = this_copy - obj.shift(pow);
        }
        return BinaryPolynomial(this_copy);
    }

    int get_size() {
        return this->coef.size();
    }

    string to_string() const {
        string res;
        for (float i : this->coef) {
            res.push_back(i + '0');
        }
        return res;
    }
};


