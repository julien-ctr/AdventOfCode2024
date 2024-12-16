#include "Map.hpp"

string keyFromPos(pair<int, int> pos) {
    return to_string(pos.first) + "_" + to_string(pos.second);
}

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

pair<int64_t, int> Map::solveMaze() {
    priority_queue<Path, vector<Path>, ComparePaths> paths;
    paths.push(Path(start)); 

    vector<Path> finalPaths;

    uint64_t minScore = INT64_MAX;
    unordered_map<string, unordered_map<int, uint64_t>> minDistances;

    const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    while (!paths.empty()) {
        Path currentPath = paths.top();
        paths.pop();

        for (int i = 0; i < directions.size(); ++i) {
            const auto &dir = directions[i];
            pair<int, int> newPos = currentPath.currentPos + dir;

            // Check if the new position is valid
            if (maze[newPos.first][newPos.second] != '#') {
                uint64_t newScore = currentPath.score + 1;
                if (currentPath.direction != dir) {
                    newScore += 1000;
                }

                if (minDistances[keyFromPos(newPos)].count(i) == 0 || 
                    newScore <= minDistances[keyFromPos(newPos)][i]) {
                    minDistances[keyFromPos(newPos)][i] = newScore;

                    Path newPath = currentPath;
                    newPath.currentPos = newPos;
                    newPath.direction = dir;
                    newPath.score = newScore;

                    if (newPos == end) {
                        finalPaths.push_back(newPath);
                        if (newScore < minScore) minScore = newScore;
                    } else if (newScore < minScore) {
                        paths.push(newPath);
                    }
                }
            }
        }
    }

    unordered_set<string> allFinalTiles;
    queue<tuple<string, int, int>> cells; // (posKey, direction, currentScore)

    for (const auto &[direction, score] : minDistances[keyFromPos(end)]) {
        if (score == minScore) {
            cells.push({keyFromPos(end), direction, minScore});
        }
    }
    while (!cells.empty()) {
        const auto &[pos, dir, currentScore] = cells.front();
        cells.pop();
        allFinalTiles.insert(pos);

        pair<int, int> currentPos = posFromKey(pos);
        pair<int, int> prevPos = currentPos - directions[dir];

        for (const auto &[prevDir, prevScore] : minDistances[keyFromPos(prevPos)]) {
            if (prevScore == (currentScore - (prevDir == dir ? 1 : 1001))) {
                cells.push({keyFromPos(prevPos), prevDir, prevScore});
            } else if (prevPos == start) {
                cells.push({keyFromPos(prevPos), prevDir, 0});
            }
        }
    }

    tiles = allFinalTiles;

    return {minScore, allFinalTiles.size()};
}


void Map::log() {
    cout << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (tiles.contains(keyFromPos({i,j}))) {
                cout << "O";
            } else {
                cout << (maze[i][j] != '.' ? maze[i][j] : ' ');
            }
        }
        cout << endl;
    }
}