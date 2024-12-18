#include "InputProcessing.hpp"
#include "Map.hpp"

using namespace std;

void loadData(const vector<string> &text, Map &myMap) {
    for (const string &line : text) {
        complex<int64_t> pos, vel;

        stringstream sstream(line);
        char unused;
        int64_t px, py, vx, vy;

        sstream >> unused >> unused >> px >> unused >> py;
        sstream >> unused >> unused >> vx >> unused >> vy;

        pos = {px, py};
        vel = {vx, vy};

        myMap.robots.emplace_back(Robot(pos,vel));
        myMap.robotsPerCell[keyFromPos(pos)] += 1;
    }
}

pair<uint64_t, uint64_t> countStars(const vector<string> &text) {
    pair<uint64_t, uint64_t> stars = make_pair(0,0);

    Map myMap(101, 103);

    loadData(text, myMap);

    myMap.moveRobots(100);
    stars.first = myMap.countRobots();
    myMap.moveRobots(-100); // Go back to initial position

    uint64_t secCount = 0;

    /*---------------------------------------------------------------------------------------*/
    /* BELOW : First solution, using a sliding window to check the highest density in a map */
    // bool found = false;
    // double d = 0;
    // while (!found) {
    //     ++secCount;
    //     myMap.moveRobots(1);
    //     d = myMap.highestRobotDensity(5,5);

    //     if (d > 0.80) {
    //         myMap.log("result.txt");
    //         found = true;

            /* Below : interactive version to make sure that the result is a tree */
            // char answer;
            // cout << "Check result.txt. Is it a tree ? [y/n] ";
            // cin >> answer;
            // cout << "You entered: " << answer << endl;
            // if (answer == 'y') {
            //     found = true;
            // }
    //     }
    // }
    /*---------------------------------------------------------------------------------------*/
    
    /*---------------------------------------------------------------------------------------*/
    /* BELOW : Second solution, finding a row of at least N robots and hope that it is the tree */
    // unsigned int estimatedTreeSize = 8;
    // while (myMap.findLargestGroup(estimatedTreeSize) < estimatedTreeSize) {
    //     myMap.moveRobots(1);
    //     ++secCount;
    // }

    // stars.second = secCount;
    /*---------------------------------------------------------------------------------------*/

    stars.second = myMap.findTree();

    return stars;
}