#include "guard.hpp"

using namespace std;

Guard::Guard() :
    count(1),
    position(make_pair(0, 0)),
    visited({}),
    direction(make_pair(-1, 0)),
    initPos(make_pair(0, 0)),
    state(OK) 
{
}

Guard::Guard(int i, int j) :
    count(1),
    position(make_pair(i, j)),
    visited({{{i, j}, {-1, 0}}}),
    direction(make_pair(-1, 0)),
    initPos(make_pair(i, j)),
    state(OK) 
{
}

void Guard::move(const unordered_set<pair<int,int>> &map, unsigned int width, unsigned int height) {
    int i = position.first + direction.first;
    int j = position.second + direction.second;

    while (!map.contains(make_pair(i,j))) {
        if (i < 0 || i > height - 1 || j < 0 || j > width - 1) {
            state = OUT_OF_BOUNDS;
            return;
        }

        position = make_pair(i, j);
        PositionDirection posDir = {{i,j}, direction};
        if (!hasVisited(i,j)) {
            count++;
            visited.insert(posDir);
        } else if (visited.contains(posDir)){
            // cout << posDir.position.first << " ; " << posDir.position.second << " was already visited with direction " << posDir.direction.first << " ; " << posDir.direction.second << endl;
            state = IN_CYCLE;
        }
        
        i += direction.first;
        j += direction.second;
    }

    direction = make_pair(direction.second, -direction.first);
}

void Guard::resetPos() {
    position = initPos;
    direction = make_pair(-1, 0);
    visited = {};
    state = OK;
    count = 0;
}

bool Guard::hasVisited(int i, int j) {
    for (pair<int, int> dir : initializer_list<pair<int, int>>{{1,0}, {-1,0}, {0,1}, {0,-1}}) {
        PositionDirection key = {{i,j}, dir};
        if (visited.contains(key)) {
            return true;
        } 
    }
    return false;
}

void Guard::logPos() {
    cout << "Guard at " << position.first << " ; " << position.second << endl; 
}

void Guard::logCount() {
    cout << "Count " << count << endl; 
}

void Guard::logVisited() {
    for (auto el : visited) {
        cout << el.position.first << " ; " << el.position.second  << " (" << el.direction.first << " ; " << el.direction.second << ")";
    }
    cout << endl;
}

void Guard::writeResult(string fileName, const unordered_set<pair<int,int>> &map, unsigned int height, unsigned int width) {
    ofstream myfile;
    myfile.open (fileName);
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            if (hasVisited(i,j)) myfile << "X";
            else if (map.contains(make_pair(i,j))) myfile << "#";
            else myfile << ".";
        }
        myfile << "\n"; 
    }
    myfile.close();
    cout << "file written" << endl;
}

const pair<int, int> Guard::getPos() {
    return position;
}

int Guard::getCount() {
    return count;
}

unordered_set<PositionDirection, PositionDirectionHash> Guard::getVisited() const {
    return visited;
}