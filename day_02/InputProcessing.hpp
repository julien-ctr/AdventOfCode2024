#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <limits>

using namespace std;

// Function declarations
vector<vector<int>> processInput(vector<string> &fileContent);
vector<vector<int>> calculateDiffs(vector<vector<int>> &values);
bool isSafe(const vector<int> &diff);
bool isAlmostSafe(const vector<int> &level, const vector<int> &diff);
unsigned int countValid1(vector<vector<int>> &diffs);
unsigned int countValid2(vector<vector<int>> &levels, vector<vector<int>> &diffs);