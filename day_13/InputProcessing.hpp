#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Equation {
    int64_t x1, x2, xf, y1, y2, yf;

    Equation(){};
};

// Function declarations
pair<uint64_t, uint64_t> countStars(const vector<string> &text);