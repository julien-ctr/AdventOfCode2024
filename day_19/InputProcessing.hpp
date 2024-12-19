#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include "Onsen.hpp"

using namespace std;

// Function declarations
void loadData(const vector<string> &text, Onsen &myOnsen);
pair<int64_t, int64_t> countStars(const vector<string> &text);