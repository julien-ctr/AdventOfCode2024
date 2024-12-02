#include "InputProcessing.hpp"

using namespace std;

vector<vector<int>> processInput(vector<string> &fileContent) {
    vector<vector<int>> result;
    for (const string &line : fileContent) {
        istringstream iss(line);
        vector<int> v;
        int num;
        while (iss >> num) {
            v.push_back(num);
        }
        result.push_back(v);
    }
    return result;
}

vector<vector<int>> calculateDiffs(vector<vector<int>> &values) {
    vector<vector<int>> diffs;
    diffs.reserve(values.size());

    for (const vector<int> &v : values) {
        vector<int> diff(v.size());
        std::adjacent_difference(v.begin(), v.end(), diff.begin());
        diffs.push_back(vector<int>(diff.begin() + 1, diff.end()));
    }

    return diffs;
}

bool isSafe(const vector<int> &level) {
    vector<int> diff(level.size());
    std::adjacent_difference(level.begin(), level.end(), diff.begin());

    vector<int>::const_iterator minimum = min_element(diff.begin()+1, diff.end());
    vector<int>::const_iterator maximum = max_element(diff.begin()+1, diff.end());
    return ((*maximum) * (*minimum) > 0 && (*maximum) <= 3 && (*minimum) >= -3);
}

bool isAlmostSafe(const vector<int> &level) {
    for (unsigned int i = 0; i < level.size(); i++) {
        vector<int> newLevel = level;
        newLevel.erase(newLevel.begin() + i);
        
        if (isSafe(newLevel)) {
            return true;
        }
    }
    return false;
}

unsigned int countValid1(vector<vector<int>> &levels) {
    unsigned int score = 0;
    for (const vector<int> &line : levels) {
        if (isSafe(line)){
            score++;
        }
    }
    return score;
}

unsigned int countValid2(vector<vector<int>> &levels) {
    unsigned int score = 0;
    unsigned int i = 0;
    for (const vector<int> &line : levels) {
        if (isSafe(line) || isAlmostSafe(line)) {
            score++;
        }
        i++;
    }
    return score;
}