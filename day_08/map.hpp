#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

class Map {
    private:
        std::unordered_map<char, std::vector<std::pair<int, int>>> m;
        std::vector<char> frequencies;
        std::unordered_set<std::string> antinodes;
        unsigned int height, width;

    public:
        Map();
        Map(const std::vector<std::string> &text);

        bool isInBounds(int i, int j);
        void generateAntinodes();
        void generateNewAntinodes();

        unsigned int getAntinodesCount();
        void writeResult(std::string filename = "result.txt");
        void log();
};

std::string getStringPos(int i, int j);