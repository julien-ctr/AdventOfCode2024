#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <functional>

using namespace std;

struct ArrayHash {
    size_t operator()(const std::array<std::string, 3>& arr) const {
        size_t combinedHash = 0;
        std::hash<std::string> stringHasher;

        for (const auto& str : arr) {
            combinedHash ^= stringHasher(str) + 0x9e3779b9 + (combinedHash << 6) + (combinedHash >> 2);
        }

        return combinedHash;
    }
};


// Function declarations
bool startsWithT(const string &str);
bool isConnectedToAll(const unordered_map<string,vector<string>> &neighbors, const vector<string> &group, const string &computer);
vector<string> findMaxExtend(const unordered_map<string,vector<string>> &neighbors, vector<string> &group);
pair<int64_t, string> countStars(const vector<string> &text);
