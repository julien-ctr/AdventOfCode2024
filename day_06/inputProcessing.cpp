#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, unordered_set<pair<int, int>> &map, Guard &guard) {
    int i = 0, j = 0;

    for (const string &line : text) {
        for (char c : line) {
            if (c == '#') {
                map.insert({i,j});
            } else if (c == '^') {
                guard = Guard(i,j);
            }
            j++;
        }
        i++;
        j=0;
    }
}

pair<int, int> countStars(const vector<string> &text) {
    pair<int, int> stars = make_pair(0,0);

    // Part 1
    unordered_set<pair<int, int>> map;
    Guard guard;
    loadData(text, map, guard);
    unsigned int width = text[0].size();
    unsigned int height = text.size();

    pair<int, int> pos = guard.getPos();

    while  (guard.state != Guard::State::OUT_OF_BOUNDS) {
        guard.move(map, width, height);
    }

    stars.first = guard.getCount();

    // Part 2 
    for (auto posDir : guard.getVisited()) {
        guard.resetPos();

        // Copy map but add an obstacle
        unordered_set<pair<int, int>> newMap = map;
        newMap.insert(make_pair(posDir.position.first, posDir.position.second));

        // cout << "ADDED OBSTACLE AT " << posDir.position.first << " ; " <<  posDir.position.second << endl;

        while  (guard.state != Guard::State::OUT_OF_BOUNDS && guard.state != Guard::State::IN_CYCLE) {
            guard.move(newMap, width, height);
        }
        
        if (guard.state == Guard::State::IN_CYCLE) stars.second++;
    }

    return stars;
}