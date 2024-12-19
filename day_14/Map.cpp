#include "Map.hpp"

string keyFromPos(complex<int64_t> pos) {
    return to_string(pos.real()) + "_" + to_string(pos.imag());
}

complex<int64_t> posFromKey(string key) {
    std::stringstream sstream(key);
    int realPart, imagPart;
    char delimiter;

    // Extract real and imaginary parts separated by '_'
    sstream >> realPart >> delimiter >> imagPart;

    // Return the complex number
    return complex<int64_t>(realPart, imagPart);
}


void Map::moveRobots(int64_t factor) {
    for (Robot &r : robots) {
        int64_t newpx, newpy;
        newpx = (r.pos.real() + r.vel.real() * factor) % width;
        newpx = newpx < 0 ? newpx + width : newpx; 
        newpy = (r.pos.imag() + r.vel.imag() * factor) % height;
        newpy = newpy < 0 ? newpy + height : newpy; 

        --robotsPerCell[keyFromPos(r.pos)];
        if (robotsPerCell[keyFromPos(r.pos)] == 0) robotsPerCell.erase(keyFromPos(r.pos));
        r.pos = {newpx, newpy};
        ++robotsPerCell[keyFromPos(r.pos)];
    }
}


int64_t Map::countRobots() {
    int64_t midWidth = width / 2;
    int64_t midHeight = height / 2;
    uint64_t firstQuad = 0, secondQuad = 0, thirdQuad = 0, fourthQuad = 0;

    uint64_t c = 0;

    for (const Robot &r : robots) {

        if (r.pos.real() < midWidth && r.pos.imag() < midHeight) ++firstQuad;
        else if (r.pos.real() > midWidth && r.pos.imag() < midHeight) ++secondQuad;
        else if (r.pos.real() < midWidth && r.pos.imag() > midHeight) ++thirdQuad;
        else if (r.pos.real() > midWidth && r.pos.imag() > midHeight) ++fourthQuad;

        ++c;
    }

    return firstQuad * secondQuad * thirdQuad * fourthQuad;
}

void Map::log(string filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return; // Exit with an error code
    }

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            string cellKey = to_string(x) + "_" + to_string(y);
            unsigned int count = robotsPerCell.count(cellKey) ? robotsPerCell[cellKey] : 0;
            outFile  << (count > 0 ? to_string(count) : ".") << " ";
        }
        outFile  << endl; // New line after each row
    }

    outFile.close();
};

double Map::highestRobotDensity(unsigned int windowWidth, unsigned int windowHeight) {
    double maxDensity = -1;

    if (windowWidth > width || windowHeight > height) {
        cout << "Window size exceeds map dimensions!" << endl;
        return -1;
    }

    for (unsigned int y = 0; y <= height - windowHeight; ++y) {
        for (unsigned int x = 0; x <= width - windowWidth; ++x) {
            unsigned int robotCount = 0;
            for (const Robot &r : robots) {
                int rx = r.pos.real();
                int ry = r.pos.imag();

                if (rx >= x && rx < x + windowWidth && ry >= y && ry < y + windowHeight) {
                    ++robotCount;
                }
            }

            double density = static_cast<double>(robotCount) / (windowWidth * windowHeight);
            if (density > maxDensity) {
                maxDensity = density;
            }
            // cout << "Window at (" << x << "," << y << ") -> Density: " << density << endl;
        }
    }
    return maxDensity;
};

uint64_t Map::findLargestGroup(unsigned int threshold) {
    /*
    Performs a BFS to find all the contiguous groups of robots and get their size.
    Returns the highest size found.
    */

    vector<vector<bool>> visited(height, vector<bool>(width, false));
    const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}};
    uint64_t maxSize = 0;
   
    for (const auto &[key, val] : robotsPerCell) {
        complex<int64_t> pos = posFromKey(key);
        uint64_t col = pos.real();
        uint64_t row = pos.imag();

        if (visited[row][col]) continue;

        visited[row][col] = true;

        queue<pair<int, int>> q;
        q.push({row, col});
        uint64_t currentSize = 1;

        while (!q.empty()) {
            auto [currentRow, currentCol] = q.front();
            q.pop();

            for (const auto &direction : directions) {
                unsigned int newRow = currentRow + direction.second;
                unsigned int newCol = currentCol + direction.first;

                if (newRow < 0 || newRow >= height || newCol < 0 || newCol >= width) {
                    continue;
                } else if (!visited[newRow][newCol] && robotsPerCell.contains(keyFromPos({newRow, newCol}))) {
                    ++currentSize;
                    visited[newRow][newCol] = true;
                    q.push({newRow, newCol});
                }
            }
        }
        if (currentSize > maxSize) {
            maxSize = currentSize;
        }
        if (maxSize >= threshold) {
            return maxSize;
        }
    }

    return maxSize;
}

double Map::varX() {
    const unsigned int size = robots.size();

    vector<double> x_values(robots.size());
    transform(robots.begin(), robots.end(), x_values.begin(),
              [](const Robot& robot) { return robot.pos.real(); });
    const double mean = accumulate(x_values.begin(), x_values.end(), 0.0) / size;
    


    auto varianceFunc = [&mean, &size](double accumulator, const double &val) {
        return accumulator + ((val - mean)*(val - mean) / (size - 1));
    };

    return accumulate(x_values.begin(), x_values.end(), 0.0, varianceFunc);
} 

double Map::varY() {
    const unsigned int size = robots.size();

    vector<double> y_values(robots.size());
    transform(robots.begin(), robots.end(), y_values.begin(),
              [](const Robot& robot) { return robot.pos.imag(); });
    const double mean = accumulate(y_values.begin(), y_values.end(), 0.0) / size;
    


    auto varianceFunc = [&mean, &size](double accumulator, const double &val) {
        return accumulator + ((val - mean)*(val - mean) / (size - 1));
    };

    return accumulate(y_values.begin(), y_values.end(), 0.0, varianceFunc);
}

pair<int, int> Map::getMinVariance(int k) {
    pair<int, int> result(0,0);

    double minVarX = -1;
    double minVarY = -1;
    for (unsigned int n = 1; n <= k; ++n) {
        moveRobots(1);
        double vx = varX();
        double vy = varY();

        if (vx < minVarX || minVarX == -1) {
            // cout << "New X Variance minimum found at move n = " << n << " : " << vx << endl;
            // log("minX.txt"); 
            minVarX = vx;
            result.first = n;
        }

        if (vy < minVarY || minVarY == -1) {
            // cout << "New Y Variance minimum found at move n = " << n << " : " << vy << endl;
            // log("minY.txt"); 
            minVarY = vy;
            result.second = n;
        }
    }
    
    moveRobots(-k);

    return result;
}

uint64_t Map::findTree() {
    unsigned int maxDimension = width > height ? width : height;
    pair<int, int> optimalPositions = getMinVariance(maxDimension);
    int optimalX = optimalPositions.first;
    int optimalY = optimalPositions.second;

    for (unsigned int t = 0; t < height * width; ++t) {
        if (t % height == optimalY && t % width == optimalX) return t;
    }

    return -1;
}