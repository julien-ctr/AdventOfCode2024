#include "Onsen.hpp"

int64_t Onsen::canBeMadeCount(const string &result, unordered_map<string, int64_t> &cache) {
    if (cache.contains(result)) {
        return cache[result];
    }

    int64_t count = 0;

    if (available.contains(result)) {
        ++count;
    }

    unsigned int iter = maxSize < result.size() ? maxSize : result.size();
    for (unsigned int i = 1; i <= iter; ++i) {
        if (available.contains(result.substr(0, i))) { // Only split if left is valid
            count += canBeMadeCount(result.substr(i), cache);
        }
    }

    cache[result] = count;
    return count;
}

pair<int64_t, int64_t> Onsen::countPossible() {
    unordered_map<string, int64_t> cacheCount;
    pair<int64_t, int64_t> count = {0, 0};

    for (const string &towel : toMake) {
        int64_t amount = canBeMadeCount(towel, cacheCount);
        count.first += (amount > 0 ? 1 : 0);
        count.second += canBeMadeCount(towel, cacheCount);
    }

    return count;
}