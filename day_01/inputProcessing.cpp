#include "InputProcessing.hpp"

using namespace std;

pair<vector<int>, vector<int>> processInput(vector<string> &fileContent) {
    string pattern = R"(\b(\d+)\b\s+\b(\d+)\b)";
    regex regex(pattern);
    pair<vector<int>, vector<int>> result;

    for (string line : fileContent) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            smatch match = *it;
            result.first.push_back(stoi(match[1].str()));
            result.second.push_back(stoi(match[2].str()));
        }
    }

    return result;
}

void sortPairs(pair<vector<int>, vector<int>> &pairs) {
    sort(pairs.first.begin(), pairs.first.end());
    sort(pairs.second.begin(), pairs.second.end());
}

int sumDistances(pair<vector<int>, vector<int>> &pairs) {
    unsigned int sum = 0;
    
    for (unsigned int i = 0; i < pairs.first.size(); i++) {
        sum += abs(pairs.first[i] - pairs.second[i]);
    }

    return sum;
}

int similarityScore(pair<vector<int>, vector<int>> &pairs) {
    unsigned int score = 0;
    unordered_map<int, int> counts;

    // Count all occurences of numbers on the right column
    for (int x : pairs.second) {
        if (counts.find(x) != counts.end()) {
            counts[x]++;
        } else {
            counts[x] = 1;
        }
    }

    for (unsigned int i = 0; i < pairs.first.size(); i++) {
        int leftElement = pairs.first[i];
        score += leftElement * counts[leftElement];
    }

    return score;
}