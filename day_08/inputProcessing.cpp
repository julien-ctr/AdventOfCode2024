#include "InputProcessing.hpp"

using namespace std;

pair<int64_t, int64_t> countStars(const vector<string> &text) {
    pair<int64_t, int64_t> stars = make_pair(0,0);

    Map map(text);
    map.generateAntinodes();
    stars.first = map.getAntinodesCount();

    map.generateNewAntinodes();
    stars.second = map.getAntinodesCount();

    //map.writeResult();

    return stars;
}