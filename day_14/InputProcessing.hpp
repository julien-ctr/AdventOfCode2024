#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include "Map.hpp"

using namespace std;

// Function declarations
void loadData(const vector<string> &text, Map &myMap);
pair<uint64_t, uint64_t> countStars(const vector<string> &text);