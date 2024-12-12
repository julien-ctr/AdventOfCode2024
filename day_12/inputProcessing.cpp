#include "InputProcessing.hpp"

using namespace std;

/*
To get the number of edges :
    Count the angles:
        outer angle if two close neighbours are not from the region (N&E / N&W / S&E / S&W)
        inner angle if two close neighbours are from the region but the one closing the square isn't.

        e.g. : 
        .....
        .XX..
        .X...
        .....

        X at (1,1) is an outer angle because N & W are not from the region. 
        It is also an inner angle, because S & E are from the region, but (2,2) isn't.
*/

unsigned int countInnerAngles(const vector<string>& map, Region& region, pair<unsigned int, unsigned int> pos) {
    unsigned int count = 0;
    unsigned int row = pos.first, col = pos.second;

    bool leftEdge = col == 0;
    bool rightEdge = col == map[0].size() - 1;
    bool topEdge = row == 0;
    bool botEdge = row == map.size() - 1;

    bool topIsSameRegion = topEdge ? false : region.visited.contains(make_pair(row-1, col));
    bool botIsSameRegion = botEdge ? false : region.visited.contains(make_pair(row+1, col));
    bool leftIsSameRegion = leftEdge ? false : region.visited.contains(make_pair(row, col-1));
    bool rightIsSameRegion = rightEdge ? false : region.visited.contains(make_pair(row, col+1));

    // N+W 
    if ((!topEdge && !leftEdge) // If not on the top nor left border
        && (leftIsSameRegion && topIsSameRegion && !region.visited.contains(make_pair(row-1, col-1)))) {
            ++count;
    }

    // S+W 
    if ((!botEdge && !leftEdge) // If not on the bot nor left border
        && (leftIsSameRegion && botIsSameRegion && !region.visited.contains(make_pair(row+1, col-1)))) {
        ++count;
    }

    // S+E
    if ((!botEdge && !rightEdge) // If not on the bot nor right border
        && (rightIsSameRegion && botIsSameRegion && !region.visited.contains(make_pair(row+1, col+1)))) {
        ++count;
    }

    // N+E 
    if ((!topEdge && !rightEdge) // If not on the top nor right border
        && (rightIsSameRegion && topIsSameRegion && !region.visited.contains(make_pair(row-1, col+1)))) {
        ++count;
    }


    return count;
}

unsigned int countOuterAngles(const vector<string>& map, Region& region, pair<unsigned int, unsigned int> pos) {
    unsigned int count = 0;
    unsigned int row = pos.first, col = pos.second;

    bool leftEdge = col == 0;
    bool rightEdge = col == map[0].size() - 1;
    bool topEdge = row == 0;
    bool botEdge = row == map.size() - 1;


    bool topIsSameRegion = topEdge ? false : region.visited.contains(make_pair(row-1, col));
    bool botIsSameRegion = botEdge ? false : region.visited.contains(make_pair(row+1, col));
    bool leftIsSameRegion = leftEdge ? false : region.visited.contains(make_pair(row, col-1));
    bool rightIsSameRegion = rightEdge ? false : region.visited.contains(make_pair(row, col+1));

    // N+W 
    if (!leftIsSameRegion && !topIsSameRegion) {
        ++count;
    }

    // S+W 
    if (!leftIsSameRegion && !botIsSameRegion) {
        ++count;
    }

    // S+E
    if (!rightIsSameRegion && !botIsSameRegion) {
        ++count;
    }

    // N+E 
    if (!rightIsSameRegion && !topIsSameRegion) {
        ++count;
    }

    return count;
}

void calculateRegions(const vector<string>& map, unordered_map<char, vector<Region>>& regions) {
    unsigned int width = map[0].size();
    unsigned int height = map.size();
    vector<vector<bool>> visited(height, vector<bool>(width, false));

    const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (unsigned int row = 0; row < height; ++row) {
        for (unsigned int col = 0; col < width; ++col) {
            if (visited[row][col]) continue;

            char key = map[row][col];
            visited[row][col] = true;

            Region region = {0, 0};
            queue<pair<int, int>> q;
            q.push({row, col});

            while (!q.empty()) {
                auto [currentRow, currentCol] = q.front();
                q.pop();
                region.area++;
                region.visited.insert(make_pair(currentRow, currentCol));

                for (const auto &direction : directions) {
                    unsigned int newRow = currentRow + direction.first;
                    unsigned int newCol = currentCol + direction.second;

                    if (newRow < 0 || newRow >= height || newCol < 0 || newCol >= width) {
                        region.perimeter++;
                    } else if (map[newRow][newCol] != key) {
                        region.perimeter++;
                    } else if (!visited[newRow][newCol]) {
                        visited[newRow][newCol] = true;
                        q.push({newRow, newCol});
                    }
                }
            }
            regions[key].push_back(region);
        }
    }

    // Count the edges 
    for (auto &[key, val] : regions) {
        for (Region &region : val) {
            for (const auto &[row, col] : region.visited) {
                region.innerAngles += countInnerAngles(map, region, make_pair(row, col));
                region.outerAngles += countOuterAngles(map, region, make_pair(row, col));
            }

            region.edges = region.innerAngles + region.outerAngles;
        }
    }
}


pair<uint64_t, uint64_t> countStars(const vector<string> &text) {
    pair<uint64_t, uint64_t> stars = make_pair(0,0);

    unordered_map<char, vector<Region>> regions;

    calculateRegions(text, regions);

    for (const auto &[key, val] : regions) {
        for (Region region : val) {
            stars.first += region.area * region.perimeter;
            stars.second += region.area * region.edges;
        }
    }

    return stars;
}