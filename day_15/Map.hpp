#pragma once
#include <complex>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

struct Robot {
    complex<int> pos, dir;
    vector<char> movesList;
    unsigned int moveIdx;

    Robot(complex<int> p, complex<int> v) : pos(p), dir(v), movesList({}), moveIdx(0) {};
};

struct Map {
    unsigned int height, width;
    Robot robot;
    unordered_map<string, char> obstacles;

    Map() : height(0), width(0), robot({0,0}), obstacles({}) {};

    virtual void moveRobot();

    void processAllMoves();

    char getElement(complex<int> pos) const;

    bool isFreeCell(complex<int> pos) const;

    int64_t computeScore();

    void log();

    virtual ~Map() = default;
};

string keyFromPos(complex<int> pos);
complex<int> posFromKey(string key);