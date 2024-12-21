#include "Map.hpp"

pair<int, int> posFromKey(string key) {
    stringstream sstream(key);
    int first, second;
    char delimiter;

    sstream >> first >> delimiter >> second;

    return make_pair(first, second);
}

pair<int, int> operator+(const pair<int, int>& x, const pair<int, int>& y) {
    return make_pair(x.first + y.first, x.second + y.second);
}

pair<int, int> operator-(const pair<int, int>& x, const pair<int, int>& y) {
    return make_pair(x.first - y.first, x.second - y.second);
}

void Map::init(const vector<string> &text) {
    height = text.size();
    width = text[0].size();
    isWall = vector<bool>(height*width);

    int y = 0;
    for (const string &line : text) {
        int x = 0;
        for (const char c : line) {
            isWall[y * width + x] = c == '#';
            if (c == 'S') {start = {x,y};};
            if (c == 'E') {end = {x,y};};
            ++x;
        }
        ++y;       
    }
}

void Map::labelPath() {
    queue<Path> paths;
    paths.push(Path(start)); 

    unordered_set<pair<int, int>, pairHash> visited;
    visited.reserve(path.size());

    const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    while (!paths.empty()) {
        Path currentPath = paths.front();
        paths.pop();

        visited.insert(currentPath.currentPos);
        path.push_back(currentPath.currentPos);
        labels[currentPath.currentPos] = currentPath.score;

        if (currentPath.currentPos == end) return;

        for (const auto &dir : directions) {
            pair<int, int> newPos = currentPath.currentPos + dir;

            if (!isWall[newPos.second * width + newPos.first] && !visited.contains(newPos)) {
                Path newPath = currentPath;
                newPath.currentPos = newPos;
                newPath.score = currentPath.score + 1;
                paths.push(newPath);
            }
        }
    }
}

// Helper function to compute the Manhattan distance
int manhattanDistance(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

pair<int64_t, int64_t> Map::countShortcuts(const pair<int64_t, int64_t> allowedCheats, const int64_t k) {
    /*
    I can't find a way to optimize this problem further.
    Parallelization would obviously make it faster, but that's not really an algorithmic optimization.
    I tried using a BFS starting from each point of the initial path, but is only happened to be at best 
    a little slower than the version I currently have.
    Currently, for n being the number of tiles in the initial path, this method runs n(n+1)/2 iterations of the inner for loop,
    each having :
        An access to path[j] in O(1)
        Comparisons in O(1)
        Sums and differences in O(1)
    Therefore, the total time complexity is O(n^2).

    To optimize further, another algorithm should be implemented.
    Idea : for each node of the path, look in the diamond shape of radius 20 surrounding it. Each time you move forward
    in the initial path, the diamond gets shifted by 1 (see below).
    */

    int64_t countFirst = 0;
    int64_t countSecond = 0;

    for (unsigned int i = 0; i < path.size(); ++i) {
        pair<int, int> pos = path[i];
        for (unsigned int j = i + k + 2; j < path.size(); ++j) {
            pair<int, int> pos2 = path[j];

            // Early exit if one dimension is already over the authorized cheat
            if (abs(pos2.first - pos.first) > allowedCheats.second || abs(pos2.second - pos.second) > allowedCheats.second) continue;


            int manhattanDistance = abs(pos2.first - pos.first) + abs(pos2.second - pos.second);

            if (manhattanDistance > allowedCheats.second) continue;

            int64_t gain = abs(labels[pos2] - labels[pos]) - manhattanDistance;
            if (gain >= k) {
                if (manhattanDistance <= allowedCheats.first) {
                    ++countFirst;
                }
                ++countSecond; 
            }   
        }
    }

    return {countFirst, countSecond};
}

bool Map::isValidPosition(const pair<int, int> &pos) {
    return pos.first >= 0 && pos.second >= 0 && pos.first < width && pos.second < height && !isWall[pos.second * width + pos.first];
}

/* BELOW : Attempt with the diamond shifting method */
// pair<int64_t, int64_t> Map::countShortcuts(const pair<int64_t, int64_t> allowedCheats, const int64_t k) {
//     int64_t countFirst = 0;
//     int64_t countSecond = 0;
//     unordered_set<pair<int, int>, pairHash> foundNeighbors;  // To store previously processed neighbors

//     // Step 1: Calculate the diamond around the start position
//     pair<int, int> pos = path[0];
        
//     for (int dy = -allowedCheats.second; dy <= allowedCheats.second; ++dy) {
//         for (int dx = -(allowedCheats.second - abs(dy)); dx <= (allowedCheats.second - abs(dy)); ++dx) {
//             pair<int, int> neighbor = pos + make_pair(dx, dy);

//             // Check bounds and walls
//             if (!isValidPosition(neighbor)) continue;
//             // Add to the set of found neighbors
//             foundNeighbors.insert(neighbor);

//             int manhattanDist = abs(dx) + abs(dy);
//             int64_t gain = abs(labels[neighbor] - labels[pos]) - manhattanDist;
            
//             // Check the gain and count
//             if (gain >= k) {
//                 if (manhattanDist <= allowedCheats.first) {
//                     ++countFirst;
//                 }
//                 ++countSecond;
//             }
//         }
//     }

//     // Step 2 : Iterate over the rest of the path to calculate shortcuts
//     for (int64_t i = 1; i < path.size(); ++i) {
//         pair<int, int> oldPos = path[i-1];
//         pair<int, int> pos = path[i];
//         pair<int, int> shift = pos - oldPos;
        

//         // Step 2.a : Remove neighbors that have become not valid
//         for (auto it = foundNeighbors.begin(); it != foundNeighbors.end(); ) {
//             if (manhattanDistance(pos, *it) > allowedCheats.second) {
//                 it = foundNeighbors.erase(it); // erase returns the next valid iterator
//             } else {
//                 ++it;
//             }
//         }

//         // Step 2.b : Add new possible neighbours
//         if (shift.first > 0) { // Shift right
//             pair<int, int> baseNode = pos + make_pair(allowedCheats.second, 0);
//             if (isValidPosition(baseNode)) {
//                 foundNeighbors.insert(baseNode);
//             }

//             for (unsigned int s = 1; s <= allowedCheats.second; ++s) {
//                 pair<int, int> otherNode1 = baseNode - make_pair(s, -s);
//                 pair<int, int> otherNode2 = baseNode - make_pair(s, s);
//                 if (isValidPosition(otherNode1)) {
//                     foundNeighbors.insert(otherNode1);
//                 }
//                 if (isValidPosition(otherNode2)) {
//                     foundNeighbors.insert(otherNode2);
//                 }

//             }
//         } else if (shift.first < 0) { // Shift left
//             pair<int, int> baseNode = pos - make_pair(allowedCheats.second, 0);
//             if (isValidPosition(baseNode)) {
//                 foundNeighbors.insert(baseNode);
//             }

//             for (unsigned int s = 1; s <= allowedCheats.second; ++s) {
//                 pair<int, int> otherNode1 = baseNode + make_pair(s, -s);
//                 pair<int, int> otherNode2 = baseNode + make_pair(s, s);
//                 if (isValidPosition(otherNode1)) {
//                     foundNeighbors.insert(otherNode1);
//                 }
//                 if (isValidPosition(otherNode2)) {
//                     foundNeighbors.insert(otherNode2);
//                 }

//             }
//         } else if (shift.second > 0) { // Shift down
//             pair<int, int> baseNode = pos + make_pair(0, allowedCheats.second);
//             if (isValidPosition(baseNode)) {
//                 foundNeighbors.insert(baseNode);
//             }

//             for (unsigned int s = 1; s <= allowedCheats.second; ++s) {
//                 pair<int, int> otherNode1 = baseNode - make_pair(-s, s);
//                 pair<int, int> otherNode2 = baseNode - make_pair(s, s);
//                 if (isValidPosition(otherNode1)) {
//                     foundNeighbors.insert(otherNode1);
//                 }
//                 if (isValidPosition(otherNode2)) {
//                     foundNeighbors.insert(otherNode2);
//                 }

//             }
//         } else if (shift.second < 0) { // Shift up
//             pair<int, int> baseNode = pos - make_pair(0, allowedCheats.second);
//             if (isValidPosition(baseNode)) {
//                 foundNeighbors.insert(baseNode);
//             }

//             for (unsigned int s = 1; s <= allowedCheats.second; ++s) {
//                 pair<int, int> otherNode1 = baseNode + make_pair(-s, s);
//                 pair<int, int> otherNode2 = baseNode + make_pair(s, s);
//                 if (isValidPosition(otherNode1)) {
//                     foundNeighbors.insert(otherNode1);
//                 }
//                 if (isValidPosition(otherNode2)) {
//                     foundNeighbors.insert(otherNode2);
//                 }

//             }
//         }

//         // Step 2.c : Process all neighbours
//         for (const pair<int,int> &oldNeighbor : foundNeighbors) {
//             int64_t oldi = labels[oldNeighbor];
//             if (abs(oldi - i) < k + 2) continue;
//             int manhattanDist = manhattanDistance(pos, oldNeighbor);
//             int64_t gain = abs(oldi - i) - manhattanDist;
//             if (gain >= k) {
//                 if (manhattanDist <= allowedCheats.first) {
//                     ++countFirst;
//                 }
//                 ++countSecond;
//             }
//         }
//     }
//     return {countFirst/2, countSecond/2};
// }


void Map::log() {
    cout << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            char token = (isWall[i * width + j] ? '#' : '.');
            cout << token;
        }
        cout << endl;
    }
}