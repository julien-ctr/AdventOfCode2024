#include "InputProcessing.hpp"

using namespace std;

void parseData(const vector<string> &text, vector<vector<int>> &map) {
    unsigned int row = 0;
    for (const string &line : text) {
        map.push_back({});
        for (const char c : line) {
            map[row].push_back(c - '0');
        }
        ++row;
    }
}

void logMap(const vector<vector<int>> &map) {
    cout << "Size of the map : " << map.size() << " * " << map[0].size() << endl;
    for (vector<int> line : map) {
        for (unsigned int n : line) {
            cout << n << " ";
        }
        cout << endl;
    }
}

string keyFromPos(unsigned int row, unsigned int col) {
    return to_string(row) + '_' + to_string(col);
}

uint64_t trailheadScoreHelper(const vector<vector<int>> &map, unsigned int row, unsigned int col,
                                unsigned int currentVal, unsigned int goal, unordered_set<string> &visitedEnds) {
    if (col < 0 || row < 0 || col >= map[0].size() || row >= map.size()) { // Check if out of bounds
        return 0;
    }

    if (currentVal != map[row][col]) {
        return 0;
    }

    if (currentVal == goal) {
        visitedEnds.insert(keyFromPos(row,col));
        return 1;
    }

    return  trailheadScoreHelper(map, row + 1, col, currentVal+1, goal, visitedEnds) +
            trailheadScoreHelper(map, row - 1, col, currentVal+1, goal, visitedEnds) +
            trailheadScoreHelper(map, row, col + 1, currentVal+1, goal, visitedEnds) +
            trailheadScoreHelper(map, row, col - 1, currentVal+1, goal, visitedEnds);
}

pair<uint64_t, uint64_t> trailheadScore(const vector<vector<int>> &map, unsigned int row, unsigned int col) {
    unordered_set<string> visitedEnds;
    return make_pair(visitedEnds.size(), trailheadScoreHelper(map, row, col, 0, 9, visitedEnds));
}

pair<uint64_t, uint64_t> countStars(const vector<string> &text) {
    pair<uint64_t, uint64_t> stars = make_pair(0,0);

    vector<vector<int>> map;
    parseData(text, map);

    for (unsigned int row = 0 ; row < map.size(); ++row) {
        for (unsigned int col = 0; col < map[0].size(); ++col) {
            if (map[row][col] == 0) {
                pair<uint64_t, uint64_t> result = trailheadScore(map, row, col);
                stars.first += result.first;
                stars.second += result.second;
            }
        }    
    }

    return stars;
}