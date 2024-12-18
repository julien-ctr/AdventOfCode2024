#pragma once
#include <complex>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

struct Robot {
    complex<int64_t> pos, vel;

    Robot(complex<int64_t> p, complex<int64_t> v) : pos(p), vel(v) {};
};

struct Map {
    unsigned int height, width;
    vector<Robot> robots;
    unordered_map<string, unsigned int> robotsPerCell;

    Map(unsigned int w, unsigned int h) : height(h), width(w), robots({}), robotsPerCell({}) {};

    void moveRobots(int64_t factor);

    int64_t countRobots();

    void log(string filename);

    double highestRobotDensity(unsigned int windowWidth, unsigned int windowHeight);

    double varX();
    double varY();

    uint64_t findLargestGroup(unsigned int threshold);

    uint64_t findTree();

    pair<int, int> getMinVariance(int k);
};

string keyFromPos(complex<int64_t> pos);