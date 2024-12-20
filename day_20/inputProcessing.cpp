#include "InputProcessing.hpp"

using namespace std;

pair<int64_t, int64_t> countStars(const vector<string> &text) {
    pair<int64_t, int64_t> stars = make_pair(0,0);

    Map myMap(text);

    stars = myMap.countShortcuts({2, 20}, 100);

    return stars;
}