#pragma once
#include <utility>

namespace std {
template <> struct hash<std::pair<int, int>> {
    inline size_t operator()(const std::pair<int, int> &v) const {
        std::hash<int> int_hasher;
        return int_hasher(v.first) ^ int_hasher(v.second);
    }
};
}

using namespace std;

struct PositionDirection {
    pair<int, int> position;
    pair<int, int> direction;

    bool operator==(const PositionDirection& other) const {
        return position == other.position && direction == other.direction;
    }
};

struct PositionDirectionHash {
    size_t operator()(const PositionDirection& pd) const {
        auto hash1 = hash<int>{}(pd.position.first) ^ (hash<int>{}(pd.position.second) << 1);
        auto hash2 = hash<int>{}(pd.direction.first) ^ (hash<int>{}(pd.direction.second) << 1);
        return hash1 ^ (hash2 << 1);
    }
};