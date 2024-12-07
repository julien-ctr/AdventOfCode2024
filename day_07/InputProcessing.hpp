#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include "equation.hpp"

using namespace std;


// Function declarations
void loadData(const vector<string> &text, vector<Equation> &eqList);
pair<int64_t, int64_t> countStars(const vector<string> &text);