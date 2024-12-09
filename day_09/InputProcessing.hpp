#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

using namespace std;


// Function declarations
void parseData(const vector<string> &text, vector<int> &memory);
pair<uint64_t, uint64_t> countStars(const vector<string> &text);