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
void parseData(const std::vector<std::string> &text, std::vector<std::vector<int>> &map);

void logMap(const std::vector<std::vector<int>> &map);

std::string keyFromPos(unsigned int row, unsigned int col);

uint64_t trailheadScoreHelper(const std::vector<std::vector<int>> &map, unsigned int row, unsigned int col,
                              unsigned int currentVal, unsigned int goal, std::unordered_set<std::string> &visitedEnds);

std::pair<uint64_t, uint64_t> trailheadScore(const std::vector<std::vector<int>> &map, unsigned int row, unsigned int col);

std::pair<uint64_t, uint64_t> countStars(const std::vector<std::string> &text);