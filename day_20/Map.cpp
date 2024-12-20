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
            if (!isWall[y * width + x]) path.push_back({x,y});
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
    */

    int64_t countFirst = 0;
    int64_t countSecond = 0;

    for (unsigned int i = 0; i < path.size(); ++i) {
        pair<int, int> pos = path[i];
        for (unsigned int j = i + 1; j < path.size(); ++j) {
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