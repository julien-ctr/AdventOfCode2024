#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

// Function declarations
void loadData(const vector<string> &text, vector<vector<int>> &locks, vector<vector<int>> &keys);
bool keyFitsLock(const vector<int> &key, const vector<int> &lock);
pair<int64_t, string> countStars(const vector<string> &text);
