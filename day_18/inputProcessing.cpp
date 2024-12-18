#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, Map &myMap) {
    int i = 0;
    for (const string &line : text) {
        stringstream sstream(line);
        int x, y;
        char comma;
        sstream >> x >> comma >> y;

        myMap.map[y * myMap.width + x] = ++i;
    }
}

pair<int64_t, string> countStars(const vector<string> &text) {
    pair<uint64_t, string> stars = make_pair(0,"");

    Map myMap(71, 71);

    loadData(text, myMap);

    stars.first = myMap.findBestPath(1024);
    stars.second = text[myMap.findFirstCut() - 1];

    return stars;
}