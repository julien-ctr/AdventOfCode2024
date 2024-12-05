#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <regex>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Function declarations
void loadData(const vector<string> &text, unordered_map<int, vector<int>> &map, vector<vector<int>> &v);
bool isValidUpdate(unordered_map<int, vector<int>> &rules, const vector<int> &update);
void sortUpdate(unordered_map<int, vector<int>> &rules, vector<int> &update);
pair<int, int> countStars(unordered_map<int, vector<int>> &rules, const vector<vector<int>> &update);