#pragma once
#include <cstdint>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

struct Map {
    unsigned int height, width;
    vector<vector<char>> maze;
    pair<int, int> start;
    pair<int, int> end;
    unordered_set<string> tiles;

    Map() : height(0), width(0), maze({}), start({}), end({}), tiles({}) {};

    pair<int64_t, int> solveMaze();

    void log();

    virtual ~Map() = default;
};

struct Path {
    pair<int, int> currentPos;
    pair<int, int> direction;
    int64_t score;

    Path(pair<int, int> startPos) : currentPos(startPos), score(0), direction({0,1}) {};
};

struct ComparePaths {
    bool operator()(const Path &a, const Path &b) {
        return a.score > b.score;
    }
};

string keyFromPos(pair<int, int> pos);
pair<int, int> posFromKey(string key);
pair<int, int> operator+(const pair<int, int>& x, const pair<int, int>& y);
pair<int, int> operator-(const pair<int, int>& x, const pair<int, int>& y);