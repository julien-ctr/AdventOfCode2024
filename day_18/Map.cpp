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

int64_t Map::findBestPath(int k) {
    priority_queue<Path, vector<Path>, Heuristic> paths(Heuristic(start, end));
    paths.push(Path(start)); 

    unordered_map<string, uint64_t> minDistances;
    minDistances[keyFromPos(start)] = 0;

    const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    while (!paths.empty()) {
        Path currentPath = paths.top();
        paths.pop();

        if (currentPath.currentPos == end) return currentPath.score;

        for (int i = 0; i < directions.size(); ++i) {
            const auto &dir = directions[i];
            pair<int, int> newPos = currentPath.currentPos + dir;

            int token = at(newPos.first, newPos.second);
            if (token == 0 || token > k) {
                uint64_t newScore = currentPath.score + 1;
                string newKey = keyFromPos(newPos);

                if (!minDistances.contains(newKey) ||
                    newScore < minDistances[newKey]) {
                    minDistances[newKey] = newScore;

                    Path newPath = currentPath;
                    newPath.currentPos = newPos;
                    newPath.score = newScore;
                    paths.push(newPath);
                }
            }
        }
    }

    return -1;
}

int64_t Map::findFirstCut() {
    int max = *max_element(map.begin(), map.end()); // final number of obstacles
    int k = max / 2;
    int delta = k / 2;
    int score = findBestPath(k);
    while (delta > 0) {
        if (score > 0) {
            k += delta;
        } else {
            k -= delta;
        }
        delta /= 2;
        score = findBestPath(k);
    }

    return (score == -1 ? k : k + 1); // If the number of obstacles was even, you might need to do a final check
}


void Map::log(int k) {
    cout << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int token = (*this).at(j, i);
            if (token > 0 && token <= k) {
                cout << "#";
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }
}