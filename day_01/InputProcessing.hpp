#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<pair<int, int>> processInput(vector<string> &fileContent) {
    string pattern = R"(\b(\d+)\b\s+\b(\d+)\b)";
    regex regex(pattern);
    vector<pair<int, int>> result;

    for (string line : fileContent) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            smatch match = *it;
            pair<int, int> numbers = make_pair(stoi(match[1].str()), (stoi(match[2].str())));
            result.push_back(numbers);
        }
    }

    return result;
}

void sortPairs(vector<pair<int, int>> &pairs) {
    vector<int> firstList;
    vector<int> secondList;

    for (auto p : pairs) {
        firstList.push_back(p.first);
        secondList.push_back(p.second);
    }

    sort(firstList.begin(), firstList.end());
    sort(secondList.begin(), secondList.end());

    for (unsigned int i = 0; i < firstList.size(); i++) {
        pairs[i] = make_pair(firstList[i], secondList[i]);
    }
}

int sumDistances(vector<pair<int, int>> &pairs) {
    unsigned int sum = 0;
    
    for (auto p : pairs) {
        sum += abs(p.first - p.second);
    }

    return sum;
}

int similarityScore(vector<pair<int, int>> &pairs) {
    unsigned int score = 0;
    unordered_map<int, int> counts;

    // Count all occurences of numbers on the right column
    for (unsigned int i = 0; i < pairs.size(); i++) {
        int rightElement = pairs[i].second;
        if (counts.find(rightElement) != counts.end()) {
            counts[rightElement]++;
        } else {
            counts[rightElement] = 1;
        }
    }

    for (unsigned int i = 0; i < pairs.size(); i++) {
        int leftElement = pairs[i].first;
        score += leftElement * counts[leftElement];
    }

    return score;
}