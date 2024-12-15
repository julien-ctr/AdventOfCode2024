#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, Map &myMap) {
    ParsingState state = PARSING_MAP;

    int row = 0, col = 0;
    for (const string &line : text) {
        if (line.empty()) {
            state = PARSING_MOVES;
            myMap.height = row;
            ++row;
            continue;
        }

        for (const char c : line) {
            string key = keyFromPos({row, col});

            switch (state) {
                case PARSING_MAP :
                    if (c == '#' || c == 'O') { // If obstacle
                        myMap.obstacles[key] = c;
                    } else if (c == '@') { // If robot
                        myMap.robot = Robot({row, col}, {0, 0});
                    }
                    break;
                case PARSING_MOVES:
                    myMap.robot.movesList.push_back(c);
                    break;
                default:
                    break;
            }
            ++col;
        }
        ++row;
        if (myMap.width == 0) myMap.width = col;
        col = 0;
    }

   
}

pair<uint64_t, uint64_t> countStars(const vector<string> &text) {
    pair<uint64_t, uint64_t> stars = make_pair(0,0);

    Map myMap;

    loadData(text, myMap);
    WideMap myWideMap(myMap);
    
    myMap.processAllMoves();
    // myMap.log();
    myWideMap.processAllMoves();
    // myWideMap.log();

    stars.first = myMap.computeScore();
    stars.second = myWideMap.computeScore();

    return stars;
}