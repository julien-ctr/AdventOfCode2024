#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <limits>

using namespace std;

// Function declarations
vector<vector<int>> processInput(vector<string> &fileContent);
bool isSafe(const vector<int> &level);
bool isAlmostSafe(const vector<int> &level);
unsigned int countValid1(vector<vector<int>> &levels);
unsigned int countValid2(vector<vector<int>> &levels);