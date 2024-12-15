#include "Map.hpp"

string keyFromPos(complex<int> pos) {
    return to_string(pos.real()) + "_" + to_string(pos.imag());
}

complex<int> posFromKey(string key) {
    std::stringstream sstream(key);
    int realPart, imagPart;
    char delimiter;

    sstream >> realPart >> delimiter >> imagPart;

    return complex<int>(realPart, imagPart);
}

char Map::getElement(complex<int> pos) const {
    string key = keyFromPos(pos);
    return (obstacles.contains(key) ? obstacles.at(key) : (robot.pos == pos ? '@' : '.'));
};

bool Map::isFreeCell(complex<int> pos) const {
    return getElement(pos) == '.';
};

void Map::moveRobot() {
    switch (robot.movesList[robot.moveIdx++]) {
        case '^':
            robot.dir = {-1, 0};
            break;
        case '>':
            robot.dir = {0, 1};
            break;
        case 'v':
            robot.dir = {1, 0};
            break;
        case '<':
            robot.dir = {0, -1};
            break;
        default:
            break;
    }

    // Cast a ray towards the direction until reaching a wall (#) and count how many boxes were encountered
    complex<int> k = 1;
    unsigned int boxesCount = 0;
    vector<complex<int>> boxes;
    while (getElement(robot.pos + k * robot.dir) != '#' && getElement(robot.pos + k * robot.dir) != '.') {
        if (getElement(robot.pos + k * robot.dir) == 'O') {
            boxesCount++;
            boxes.push_back(robot.pos + k * robot.dir);
        }
        k = k + 1;
    }

    if (getElement(robot.pos + k * robot.dir) == '#') k = k - 1;

    // Move encountered boxes 
    complex<int> n = 1;
    for (auto it = boxes.rbegin(); it != boxes.rend(); ++it) {
        const complex<int> &boxPos = *it;
        obstacles.erase(keyFromPos(boxPos));
        obstacles[keyFromPos(robot.pos + (k - n + 1) * robot.dir)] = 'O';
        n = n + 1;
    }

    // Move robot
    robot.pos = robot.pos + (k - complex<int>(boxesCount)) * robot.dir;
};

void Map::processAllMoves() {
    while (robot.moveIdx < robot.movesList.size()) {
        moveRobot();
    }
};

int64_t Map::computeScore() {
    int64_t score = 0;
    for (const auto &[key, val] : obstacles) {
        if (val == 'O' || val == '[') {
            complex<int> pos = posFromKey(key);
            score += 100*pos.real() + pos.imag();
        }
    }
    return score;
};

void Map::log() {
    cout << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << getElement({i,j});
        }
        cout << endl;
    }
}