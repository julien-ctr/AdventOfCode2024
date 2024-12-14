#pragma once
#include <complex>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>

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

    uint64_t findLargestGroup(const Map &myMap);
};

string keyFromPos(complex<int64_t> pos);