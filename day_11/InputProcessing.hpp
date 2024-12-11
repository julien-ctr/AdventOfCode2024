#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <cmath>

using namespace std;

// Function declarations
void parseData(const vector<string> &text, unordered_map<uint64_t, uint64_t> &stoneList);
unsigned int numDigits(uint64_t x);
pair<uint64_t, uint64_t> cut(uint64_t x, unsigned int pos);
pair<uint64_t, uint64_t> cutHalf(uint64_t x);
void iter(unordered_map<uint64_t, uint64_t> &stoneList, unordered_map<uint64_t, vector<uint64_t>> &memory);
pair<uint64_t, uint64_t> countStars(const vector<string> &text);