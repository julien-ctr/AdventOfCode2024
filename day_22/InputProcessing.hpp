#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

using namespace std;

struct TupleHash {
    template <typename... T>
    size_t operator()(const tuple<T...>& t) const {
        return hash_tuple(t, std::index_sequence_for<T...>{});
    }

private:
    template <typename Tuple, size_t... I>
    size_t hash_tuple(const Tuple& t, std::index_sequence<I...>) const {
        return (... ^ (hash<typename tuple_element<I, Tuple>::type>{}(get<I>(t)) << (I * 5)));
    }
};


// Function declarations
void getNext(int64_t &x);
pair<int64_t, int64_t> countStars(const vector<string> &text);
