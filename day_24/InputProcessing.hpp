#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <cstdint>
#include <functional>

using namespace std;

enum ParsingState {
    VALUES,
    GATES
};

// Function declarations
void loadData(const vector<string> &text, unordered_map<string,int> &values, unordered_map<string, vector<string>> &gates);
void solve(unordered_map<string,int> &values, const unordered_map<string, vector<string>> &gates, const string &toSolve, int depth = 0);
vector<string> fixErrors(unordered_map<string,int> &values, unordered_map<string, vector<string>> &gates);
pair<int64_t, string> countStars(const vector<string> &text);
