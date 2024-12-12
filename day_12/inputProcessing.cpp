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

void countEdges(const vector<string>& map, Region& region) {
    unsigned int count = 0;

    for (const auto &[row, col] : region.visited) {
        bool topIsSameRegion = region.visited.contains(make_pair(row-1, col));
        bool botIsSameRegion = region.visited.contains(make_pair(row+1, col));
        bool leftIsSameRegion = region.visited.contains(make_pair(row, col-1));
        bool rightIsSameRegion = region.visited.contains(make_pair(row, col+1));

        // Inner angles
        if ((!leftIsSameRegion && !topIsSameRegion)  || // NW
            (!leftIsSameRegion && !botIsSameRegion)  || // SW
            (!rightIsSameRegion && !botIsSameRegion) || // SE
            (!rightIsSameRegion && !topIsSameRegion)) { // NE
            ++count;
        }

        // Outer angles
        if ((leftIsSameRegion && topIsSameRegion && !region.visited.contains(make_pair(row-1, col-1)))  || //NW
            (leftIsSameRegion && botIsSameRegion && !region.visited.contains(make_pair(row+1, col-1)))  || //SW
            (rightIsSameRegion && botIsSameRegion && !region.visited.contains(make_pair(row+1, col+1))) || //SE
            (rightIsSameRegion && topIsSameRegion && !region.visited.contains(make_pair(row-1, col+1)))) { //NE
            ++count;
        }
    }
    region.edges = count;
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

    for (auto &[key, val] : regions) {
        for (Region &region : val) {
            countEdges(map, region);
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