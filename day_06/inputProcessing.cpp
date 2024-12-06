#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, unordered_set<pair<int, int>> &map, 
            unordered_map<int, vector<int>> &obstacleXMap, unordered_map<int, vector<int>> &obstacleYMap, Guard &guard) {
    int i = 0, j = 0;

    for (const string &line : text) {
        for (char c : line) {
            if (c == '#') {
                map.insert({i,j});
                obstacleXMap[i].push_back(j);
                obstacleYMap[j].push_back(i);
            } else if (c == '^') {
                guard = Guard(i,j);
            }
            j++;
        }
        i++;
        j=0;
    }
}

void sortObstacleMaps(unordered_map<int, vector<int>>& obstacleXMap, unordered_map<int, vector<int>>& obstacleYMap) {
    for (auto& pair : obstacleXMap) {
        std::sort(pair.second.begin(), pair.second.end());
    }

    for (auto& pair : obstacleYMap) {
        std::sort(pair.second.begin(), pair.second.end());
    }
}

pair<int, int> countStars(const vector<string> &text) {
    pair<int, int> stars = make_pair(0,0);

    // Part 1
    unordered_set<pair<int, int>> map;
    unordered_map<int, vector<int>> obstacleXMap; // Maps y -> sorted vector of x positions
    unordered_map<int, vector<int>> obstacleYMap; // Maps x -> sorted vector of y positions

    sortObstacleMaps(obstacleXMap, obstacleYMap);

    Guard guard;
    loadData(text, map, obstacleXMap, obstacleYMap, guard);

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

        obstacleXMap[posDir.position.first].push_back(posDir.position.second);
        obstacleYMap[posDir.position.second].push_back(posDir.position.first);

        sortObstacleMaps(obstacleXMap, obstacleYMap);

        // cout << endl << "ADDED OBSTACLE AT " << posDir.position.first << " ; " <<  posDir.position.second << endl;

        while  (guard.state != Guard::State::OUT_OF_BOUNDS && guard.state != Guard::State::IN_CYCLE) {
            guard.moveOptimized(obstacleXMap, obstacleYMap, width, height);
        }
        
        if (guard.state == Guard::State::IN_CYCLE) {
            stars.second++;
            // cout << posDir.position.first << " ; " << posDir.position.second << " WAS VALID POSITION." << endl;
        }

        obstacleXMap[posDir.position.first].erase(find(obstacleXMap[posDir.position.first].begin(), 
                                                       obstacleXMap[posDir.position.first].end(),
                                                       posDir.position.second));
        obstacleYMap[posDir.position.second].erase(find(obstacleYMap[posDir.position.second].begin(), 
                                                        obstacleYMap[posDir.position.second].end(),
                                                        posDir.position.first));;
    }

    return stars;
}