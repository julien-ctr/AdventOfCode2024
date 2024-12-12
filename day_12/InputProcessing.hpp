#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Region {
    uint64_t perimeter;
    uint64_t area;
    uint64_t edges;
    set<pair<int, int>> visited;

    bool operator==(const Region& other) const {
        return perimeter == other.perimeter && area == other.area;
    };

    Region(uint64_t p, uint64_t a) : perimeter(p), area(a), visited({}), edges(0) {};
};

// Function declarations
pair<uint64_t, uint64_t> countStars(const vector<string> &text);