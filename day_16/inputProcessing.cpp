#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, Map &myMap) {
    int line_num = -1;
    for (const string &line : text) {
        myMap.maze.push_back({});
        ++line_num;
        for (const char c : line) {
            myMap.maze[line_num].push_back(c);

            if (c == 'S') myMap.start = {line_num, myMap.maze[line_num].size()-1};
            if (c == 'E') myMap.end = {line_num, myMap.maze[line_num].size()-1};

        }
    }

   myMap.height = myMap.maze.size();
   myMap.width = myMap.maze[0].size();
}

pair<uint64_t, uint64_t> countStars(const vector<string> &text) {
    pair<uint64_t, uint64_t> stars = make_pair(0,0);

    Map myMap;

    loadData(text, myMap);

    stars = myMap.solveMaze();

    // myMap.log();
    return stars;
}