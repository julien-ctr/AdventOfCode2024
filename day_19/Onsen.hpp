#pragma once
#include <cstdint>
#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

struct Onsen {
    unordered_set<string> available;
    vector<string> toMake;
    unsigned int maxSize;

    Onsen() : maxSize(0), available({}), toMake({}) {};

    int64_t canBeMadeCount(const string &result, unordered_map<string, int64_t> &cache);

    pair<int64_t, int64_t> countPossible();
};