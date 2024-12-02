#include "InputProcessing.hpp"

using namespace std;

pair<vector<int>, vector<int>> processInput(vector<string> &fileContent) {
    pair<vector<int>, vector<int>> result;
    for (string line : fileContent) {
        istringstream iss(line);
        vector<int> v;

        int num;

        iss >> num;
        v.push_back(num);
        result.first.push_back(num);

        iss >> num;
        v.push_back(num);
        result.second.push_back(num);
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