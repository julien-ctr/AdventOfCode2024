#pragma once
#include <cstdint>
#include <cmath>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <queue>
#include <chrono>

using namespace std;

pair<int, int> operator+(const pair<int, int>& x, const pair<int, int>& y);
pair<int, int> operator-(const pair<int, int>& x, const pair<int, int>& y);

struct pairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

struct Map {
    unsigned int height, width;
    pair<int, int> start;
    pair<int, int> end;
    unordered_map<pair<int, int>, int, pairHash> labels;
    vector<bool> isWall;
    vector<pair<int,int>> path;

    struct Path {
        pair<int, int> currentPos;
        int64_t score;

        Path(pair<int, int> startPos) : currentPos(startPos), score(0) {};
    };

    Map(const vector<string> &text) {
        init(text);
        labelPath();
    };

    void init(const vector<string> &text);

    void labelPath();

    pair<int64_t, int64_t> countShortcuts(pair<int64_t, int64_t> allowedCheat, int64_t k);

    void log();
};

pair<int, int> posFromKey(string key);