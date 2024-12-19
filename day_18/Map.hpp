#pragma once
#include <cstdint>
#include <cmath>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Map {
    unsigned int height, width;
    pair<int, int> start;
    pair<int, int> end;
    vector<int> map;

    struct Path {
        pair<int, int> currentPos;
        int64_t score;

        Path(pair<int, int> startPos) : currentPos(startPos), score(0) {};
    };

    struct Heuristic {
        const pair<int, int> &start;
        const pair<int, int> &end;

        Heuristic(const pair<int, int> &startRef, const pair<int, int> &endRef) : start(startRef), end(endRef) {};

        bool operator()(const Path &a, const Path &b) {
            int h1 = a.score + abs(a.currentPos.first - end.first) + abs(a.currentPos.second - end.second);
            int h2 = b.score + abs(b.currentPos.first - end.first) + abs(b.currentPos.second - end.second);
            return h1 > h2;
        }
    };

    Map(int h, int w) : height(h), width(w), map(h * w, 0), start({0,0}), end({width-1, height-1}) {};

    int at(int x, int y) {
        if (x < 0 || y < 0 || x >= width || y >= height) {
            return -1;
        }
        return map[y * width + x];
    }

    int64_t findBestPath(int k);

    int64_t findFirstCut();

    void log(int k);

    virtual ~Map() = default;
};

string keyFromPos(pair<int, int> pos);
pair<int, int> posFromKey(string key);
pair<int, int> operator+(const pair<int, int>& x, const pair<int, int>& y);
pair<int, int> operator-(const pair<int, int>& x, const pair<int, int>& y);