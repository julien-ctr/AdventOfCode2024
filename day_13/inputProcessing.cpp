#include "InputProcessing.hpp"

using namespace std;

void parseLine(const string &line, int64_t &x, int64_t &y) {
    size_t colonPos = line.find(":");
    if (colonPos == string::npos) return;

    string data = line.substr(colonPos + 1);
    stringstream ss(data);
    string temp;

    char token;
    while (ss >> temp) {
        token = temp[0];
        if (temp.find('+') != string::npos || temp.find('=') != string::npos) {
            temp.erase(0, temp.find_first_of("+=") + 1);
            int value;
            stringstream num_ss(temp);
            num_ss >> value;
            if (token == 'X') {
                x = value;
            } else if (token == 'Y') {
                y = value;
            }
        }
    }
}

void loadData(const vector<string> &text, vector<Equation> &equations) {
    Equation eq;
    unsigned int lineCount = 0;

    for (const string &line : text) {
        if (line.empty()) {
            equations.push_back(eq); // Push the completed equation
            eq = Equation(); // Reset for the next equation
            lineCount = 0; // Reset line count for the next equation
            continue;
        }

        if (lineCount == 0) {
            parseLine(line, eq.x1, eq.y1);
        } else if (lineCount == 1) {
            parseLine(line, eq.x2, eq.y2);
        } else if (lineCount == 2) {
            parseLine(line, eq.xf, eq.yf);
        }

        ++lineCount;
    }

    if (lineCount > 0) {
        equations.push_back(eq); // Push the last equation if not already added
    }
}


void scaleEquations(vector<Equation> &equations, const int64_t factor) {
    for (Equation &eq : equations) {
        eq.scale(factor);
    }
}

pair<uint64_t, uint64_t> countStars(const vector<string> &text) {
    pair<uint64_t, uint64_t> stars = make_pair(0,0);

    vector<Equation> equations;
    loadData(text, equations);

    for (const Equation &eq : equations) {
        pair<int64_t, int64_t> res = eq.solve();
        if (res.first != -1) stars.first += 3 * res.first + res.second;
    }

    scaleEquations(equations, 10000000000000);

    for (const Equation &eq : equations) {
        pair<int64_t, int64_t> res = eq.solve();
        if (res.first != -1) stars.second += 3 * res.first + res.second;
    }

    return stars;
}