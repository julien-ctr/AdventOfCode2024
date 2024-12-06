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

void Guard::moveOptimized(unordered_map<int, vector<int>> &Xmap, unordered_map<int, vector<int>> &Ymap, unsigned int width, unsigned int height, bool log) {
    int i = position.first;
    int j = position.second;

    int obstacle = -1;
    if (log) {
        cout << "Position : " << position.first << " ; " << position.second << endl;
        cout << "Direction : " << direction.first << " ; " << direction.second << endl;
    }

    if (direction.second == 0) { // Vertical
        auto it = std::lower_bound(Ymap[j].begin(), Ymap[j].end(), i);

        if (log) {
            cout << "Ymap " << j << " : ";
            for (auto  val : Ymap[j]) {
                cout << val << " ";
            }
            cout << endl;
        }

        if (it != Ymap[j].begin() && direction.first == -1) { // Up
            --it;
            obstacle = *it;
            position.first = obstacle + 1;
        } else if (it != Ymap[j].end() && direction.first == 1) { // Down
            obstacle = *it;
            position.first = obstacle - 1;
        }
    } else { // Horizontal
        auto it = std::lower_bound(Xmap[i].begin(), Xmap[i].end(), j);

        if (log) {
            cout << "Xmap " << i << " : ";
            for (auto  val : Xmap[i]) {
                cout << val << " ";
            }
            cout << endl;
        }

        if (it != Xmap[i].begin() && direction.second == -1) { // Left
            --it;
            obstacle = *it;
            position.second = obstacle + 1;
        } else if (it != Xmap[i].end() && direction.second == 1) { // Right
            obstacle = *it;
            position.second = obstacle - 1;
        }
    }
    
    if (obstacle > -1 && obstacle < width && obstacle < height) { // If obstacle found
        if (log) cout << "OBSTACLE FOUND" << endl;
        PositionDirection posDir = {position, direction};
        if (!visited.contains(posDir)) {
            visited.insert(posDir);
        } else {
            if (log) cout << "LOOP DETECTED" << endl;
            state = IN_CYCLE;
        }
    } else {
        if (log) cout << "NOW OUT OF BOUNDS" << endl;
        state = OUT_OF_BOUNDS;
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