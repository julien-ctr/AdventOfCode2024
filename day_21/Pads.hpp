#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <iostream>

using namespace std;

pair<int, int> operator+(const pair<int, int>& x, const pair<int, int>& y);
pair<int, int> operator-(const pair<int, int>& x, const pair<int, int>& y);

pair<int, int> posFromKey(string key);

vector<pair<char,char>> getTransitions(const string &s);

struct Pad {
    vector<vector<char>> pad;
    unordered_map<char, pair<int, int>> positions;

    Pad(const vector<vector<char>>& inputPad) {
        pad = inputPad;
        for (int i = 0; i < pad.size(); ++i) {
            for (int j = 0; j < pad[i].size(); ++j) {
                positions[pad[i][j]] = {i, j};
            }
        }
    }

    virtual string getSequence(const char from, const char to) = 0;
};

struct NumPad : public Pad {
    NumPad() : Pad({{'7', '8', '9'},
                    {'4', '5', '6'},
                    {'1', '2', '3'},
                    {'X', '0', 'A'}}) {}

    string getSequence(const char from, const char to) override;
};

struct DirPad : public Pad {
    DirPad() : Pad({{' ', '^', 'A'},
                    {'<', 'v', '>'}}) {}

    string getSequence(const char from, const char to) override;
};


struct Password {
    string code;

    int getNumericPart() const {return stoi(code.substr(1,4));};

    Password(string c) : code("A" + c) {};
};

int64_t typePassword(const Password &p, int dirRobots);