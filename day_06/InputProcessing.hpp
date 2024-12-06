#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include "guard.hpp"
#include "common.hpp"

using namespace std;

// Function declarations
void loadData(const vector<string> &text, unordered_set<pair<int, int>> &map, unordered_map<int, vector<int>> &obstacleXMap, unordered_map<int, vector<int>> &obstacleYMap, Guard &guard);
void sortObstacleMaps(unordered_map<int, vector<int>>& obstacleXMap, unordered_map<int, vector<int>>& obstacleYMap);
pair<int, int> countStars(const vector<string> &text);