#include "WideMap.hpp"
#include <queue>
#include <stack>
#include <set>

WideMap::WideMap(const Map &baseMap) {
    height = baseMap.height;
    width = 2 * baseMap.width;

    robot = baseMap.robot;
    robot.pos = {baseMap.robot.pos.real(), baseMap.robot.pos.imag() * 2}; 

    for (const auto &[key, val] : baseMap.obstacles) {
        complex<int> pos = posFromKey(key);
        char baseToken = baseMap.getElement(pos);

        complex<int> widePos = pos + complex<int>(0, pos.imag());

        if (baseToken == '#') {
            obstacles[keyFromPos(widePos)] = '#';
            obstacles[keyFromPos(widePos + complex<int>(0,1))] = '#';
        } else if (baseToken == 'O') {
            obstacles[keyFromPos(widePos)] = '[';
            obstacles[keyFromPos(widePos + complex<int>(0,1))] = ']';
        }
    }
}

void WideMap::moveRobot() {
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
    stack<complex<int>> boxesToMove;
    queue<complex<int>> cellsToCheck({robot.pos});
    set<string> visitedCells;

    bool wallEncountered = false;

    while (!cellsToCheck.empty()) {
        complex<int> cellPos = cellsToCheck.front();
        visitedCells.insert(keyFromPos(cellPos));
        cellsToCheck.pop();
        
        char token = getElement(cellPos + robot.dir);
        if (token == '[') {
            if (!visitedCells.contains(keyFromPos(cellPos + robot.dir))) {
                cellsToCheck.push(cellPos + robot.dir);
                boxesToMove.push(cellPos + robot.dir);
            }
            if (!visitedCells.contains(keyFromPos((cellPos + complex<int>(0, 1)) + robot.dir))) {
                cellsToCheck.push((cellPos + complex<int>(0, 1)) + robot.dir);
            }
        } else if (token == ']') {
            if (!visitedCells.contains(keyFromPos(cellPos + robot.dir))) {
                cellsToCheck.push(cellPos + robot.dir);
            }
            if (!visitedCells.contains(keyFromPos((cellPos - complex<int>(0, 1)) + robot.dir))) {
                cellsToCheck.push((cellPos - complex<int>(0, 1)) + robot.dir);
                boxesToMove.push((cellPos - complex<int>(0, 1)) + robot.dir);
            }
        } else if (token == '#') {
            wallEncountered = true;
        }
    }

    // At this point, we have a stack of boxes that are grouped.
    // We need to empty the stack, moving each box once towards the robot's direction
    if (wallEncountered) return;

    while (!boxesToMove.empty()) {
        complex<int> boxPos = boxesToMove.top();
        boxesToMove.pop();

        obstacles.erase(keyFromPos(boxPos));
        obstacles.erase(keyFromPos(boxPos + complex<int>(0, 1)));

        obstacles[keyFromPos(boxPos + robot.dir)] = '[';
        obstacles[keyFromPos(boxPos + complex<int>(0, 1) + robot.dir)] = ']';

    }

    // Move robot
    robot.pos = robot.pos + robot.dir;
}