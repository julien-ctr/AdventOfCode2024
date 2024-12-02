#include "InputProcessing.hpp"

using namespace std;

vector<vector<int>> processInput(vector<string> &fileContent) {
    string pattern = R"(\b(\d+)\b)";
    regex regex(pattern);
    vector<vector<int>> result;

    for (string line : fileContent) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto end = std::sregex_iterator();

        vector<int> v;
        for (auto it = begin; it != end; ++it) {
            smatch match = *it;
            v.push_back(stoi(match.str()));
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

bool isSafe(const vector<int> &diff) {
    vector<int>::const_iterator minimum = min_element(diff.begin(), diff.end());
    vector<int>::const_iterator maximum = max_element(diff.begin(), diff.end());
    return ((*maximum) * (*minimum) > 0 && (*maximum) <= 3 && (*minimum) >= -3);
}

bool isAlmostSafe(const vector<int> &level, const vector<int> &diff) {
    for (unsigned int i = 0; i < level.size(); i++) {
        vector<int> newLevel = level;
        newLevel.erase(newLevel.begin() + i);

        vector<int> tempDiff(newLevel.size());
        adjacent_difference(newLevel.begin(), newLevel.end(), tempDiff.begin());
        vector<int> newDiff(vector<int>(tempDiff.begin() + 1, tempDiff.end()));
        
        if (isSafe(newDiff)) {
            return true;
        }
    }
    return false;
}

unsigned int countValid1(vector<vector<int>> &diffs) {
    unsigned int score = 0;
    for (const vector<int> &line : diffs) {
        if (isSafe(line)){
            score++;
        }
    }
    return score;
}

unsigned int countValid2(vector<vector<int>> &levels, vector<vector<int>> &diffs) {
    unsigned int score = 0;
    unsigned int i = 0;
    for (const vector<int> &line : diffs) {
        if (isSafe(line) || isAlmostSafe(levels[i], line)) {
            score++;
        }
        i++;
    }
    return score;
}