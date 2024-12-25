#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, vector<vector<int>> &locks, vector<vector<int>> &keys) {
    unsigned int lockNum = 0;
    unsigned int keyNum = 0;

    for (unsigned int lineNum = 0; lineNum < text.size(); lineNum += 8) {
        bool isLock = text[lineNum][0] == '#';
        if (isLock)  {
            locks.emplace_back(vector<int>(5,0));
        }
        else {
            keys.emplace_back(vector<int>(5,0));
        }

        for (unsigned int delta = 1; delta < 6; ++delta) {
            for (unsigned int col = 0; col < 5; ++col) {
                if (isLock) {
                    locks[lockNum][col] += text[lineNum + delta][col] == '#' ? 1 : 0;
                } else {
                    keys[keyNum][col] += text[lineNum + delta][col] == '#' ? 1 : 0;
                }
            }
        }

        if (isLock) {
            ++lockNum;
        }
        else {
            ++keyNum;
        }
    }
}

bool keyFitsLock(const vector<int> &key, const vector<int> &lock) {
    for (unsigned int i = 0; i < 5; ++i) {
        if (key[i] + lock[i] > 5) return false;
    }
    return true;
}

pair<int64_t, string> countStars(const vector<string> &text) {
    pair<int64_t, string> stars = make_pair(0,"");

    vector<vector<int>> locks;
    vector<vector<int>> keys;

    loadData(text, locks, keys);

    int64_t count = 0;
    for (const auto key : keys) {
        count += count_if(locks.begin(), locks.end(), 
                          [&key](const auto &lock) { return keyFitsLock(key, lock); });
    }
    stars.first = count;
    return stars;
}