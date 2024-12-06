#pragma once
#include <utility>
#include <iostream>
#include <unordered_set>
#include <fstream>
#include "common.hpp"

using namespace std;

class Guard {
    private:
        pair<int, int> position;
        pair<int, int> initPos;
        pair<int, int> direction;
        unsigned int count;
        unordered_set<PositionDirection, PositionDirectionHash> visited;

    public:
        enum State {
            OK,
            OUT_OF_BOUNDS,
            IN_CYCLE,
        } state;

        Guard(); // Default
        Guard(int i, int j); // Constructor
        void move(const unordered_set<pair<int,int>> &map, unsigned int width, unsigned int height);
        void resetPos();
        bool hasVisited(int i, int j);

        void logPos();
        void logCount();
        void logVisited();
        void writeResult(string fileName, const unordered_set<pair<int,int>> &map, unsigned int height, unsigned int width);

        const pair<int, int> getPos();
        int getCount();
        unordered_set<PositionDirection, PositionDirectionHash> getVisited() const;
};