#include "InputProcessing.hpp"

using namespace std;

void parseData(const vector<string> &text, unordered_map<uint64_t, uint64_t> &stoneList) {
    istringstream iss(text[0]);
    uint64_t num;

    while (iss >> num) {
        stoneList[num]++;
    }
}

unsigned int numDigits(uint64_t x) {
    return log10(x) + 1;
}

pair<uint64_t, uint64_t> cut(uint64_t x, unsigned int pos) {
    // Cuts x in two numbers after digit pos
    uint64_t power = pow(10, numDigits(x) - pos);

    return make_pair(x / power, x % power);
}

pair<uint64_t, uint64_t> cutHalf(uint64_t x) {
    return cut(x, numDigits(x)/2);
}

void iter(unordered_map<uint64_t, uint64_t> &stoneList, unordered_map<uint64_t, vector<uint64_t>> &memory) {
    unordered_set<uint64_t> toCheck;
    vector<pair<uint64_t, uint64_t>> toAdd;

    for (const auto &[key, val] : stoneList) {
        toCheck.insert(key);
    }

    for (const auto &key : toCheck) {
        uint64_t amount = stoneList[key];

        if (memory.contains(key)) {
            stoneList[key] -= amount;
            for (uint64_t stone : memory[key]) {
                toAdd.push_back(make_pair(stone, amount));
            }
            continue;
        }

        if (key == 0) {
            stoneList[key] -= amount;
            toAdd.push_back(make_pair(1, amount));
            memory[key] = {1};
        }

        else if (numDigits(key) % 2 == 0) {
            pair<uint64_t, uint64_t> splittedNumber = cutHalf(key);
            stoneList[key] -= amount;
            toAdd.push_back(make_pair(splittedNumber.first, amount));
            toAdd.push_back(make_pair(splittedNumber.second, amount));
            memory[key].push_back(splittedNumber.first);
            memory[key].push_back(splittedNumber.second);

        }

        else {
            stoneList[key] -= amount;
            toAdd.push_back(make_pair(key * 2024, amount));
            memory[key].push_back(key * 2024);
        }

        if (stoneList[key] == 0) {
            stoneList.erase(key);
        }
    } 

    for (const auto pair : toAdd) {
        stoneList[pair.first] += pair.second;
    }
}

pair<uint64_t, uint64_t> countStars(const vector<string> &text) {
    pair<uint64_t, uint64_t> stars = make_pair(0,0);

    unordered_map<uint64_t, uint64_t> stoneList;

    parseData(text, stoneList);

    unordered_map<uint64_t, vector<uint64_t>> memory;

    for (unsigned int k = 0; k < 25; ++k) {
        iter(stoneList, memory);
    }

    for (const auto &[key, value] : stoneList) {
        stars.first += value;
    }

    for (unsigned int k = 0; k < 50; ++k) {
        iter(stoneList, memory);
    }

    for (const auto &[key, value] : stoneList) {
        stars.second += value;
    }

    return stars;
}