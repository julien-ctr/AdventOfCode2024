#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <algorithm>
#include <cstdint>

using namespace std;

struct Equation {
    int64_t x1, x2, xf, y1, y2, yf;

    Equation(){};

    void scale(const int64_t factor) {
        xf += factor;
        yf += factor;
    }

    pair<int64_t, int64_t> solve() const {
        // Returns {-1, -1} if no solution is found.

        int64_t a = (yf * x2 - y2 * xf) / (y1 * x2 - x1 * y2);
        int64_t b = (xf - a * x1) / x2;

        bool isValidSolution = a*x1 + b*x2 == xf && a*y1 + b*y2 == yf && a >= 0 && b >= 0;

        return (isValidSolution ? make_pair(a,b) : make_pair((int64_t) -1, (int64_t) -1));
    }
};

// Function declarations
void parseLine(const string &line, int64_t &x, int64_t &y);
void loadData(const vector<string> &text, vector<Equation> &equations);
void scaleEquations(vector<Equation> &equations, const int64_t factor);
pair<uint64_t, uint64_t> countStars(const vector<string> &text);