#include "InputProcessing.hpp"

using namespace std;

void getNext(int64_t &x) {
    int64_t r = x * 64; // Multiply
    x ^= r; // Mix
    x = x % 16777216; // Prune

    r = x / 32;
    x ^= r;
    x = x % 16777216;

    r = x * 2048;
    x ^= r;
    x = x % 16777216;
}

pair<int64_t, int64_t> countStars(const vector<string> &text) {
    pair<int64_t, int64_t> stars = make_pair(0,0);
    unordered_map<tuple<int64_t, int64_t, int64_t, int64_t>, int64_t, TupleHash> sequencesValues;

    const int64_t ITERATIONS = 2000;

    int i = 0;
    for (const string &line : text) {
        int64_t num = stoi(line);
        unordered_set<tuple<int64_t, int64_t, int64_t, int64_t>, TupleHash> tested;
        vector<int64_t> lastDiffs(4, 0);
        int64_t oldPrice = num % 10;

        for (int j = 0; j < ITERATIONS; ++j) {  
            getNext(num);

            int64_t price = num % 10;
 
            lastDiffs[0] = lastDiffs[1];
            lastDiffs[1] = lastDiffs[2];
            lastDiffs[2] = lastDiffs[3];
            lastDiffs[3] = price - oldPrice;

            oldPrice = price;
            
            if (j >= 3) {
                tuple<int64_t, int64_t, int64_t, int64_t> seqKey(lastDiffs[0], lastDiffs[1], lastDiffs[2], lastDiffs[3]);

                if (tested.find(seqKey) == tested.end()) {
                    sequencesValues[seqKey] += price;
                    tested.insert(seqKey);
                }
            }
        }
        stars.first += num;
        ++i;
    }

    int64_t maxBananas = 0;
    for (auto &[key, value] : sequencesValues) {
        if (value > maxBananas) maxBananas = value;
    }
    stars.second = maxBananas;

    return stars;
}