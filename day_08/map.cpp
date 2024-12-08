#include "map.hpp"

using namespace std;

string getStringPos(int i, int j) {
    return to_string(i) + "-" + to_string(j);
}

Map::Map() :
    m({}),
    frequencies({}),
    antinodes({}),
    width(0),
    height(0){
}

Map::Map(const std::vector<std::string> &text) : m({}), frequencies({}), antinodes({}){
    int i = 0, j = 0;
    for (const string &line : text) {
        for (char c : line) {
            if (c != '.') {
                m[c].push_back(make_pair(i,j));

                if (find(frequencies.begin(), frequencies.end(), c) == frequencies.end()) {
                    frequencies.push_back(c);
                }
            }
            j++;
        }
        i++;
        j = 0;
    }

    width = text[0].size();
    height = text.size();
}

bool Map::isInBounds(int i, int j) {
    return (i >= 0 && j >= 0 && i < height && j < width);
}

void Map::generateAntinodes(){
    for (const char freq : frequencies) {
        for (unsigned int i = 0; i < m[freq].size(); ++i) {
            for (unsigned int j = i + 1; j < m[freq].size(); ++j) {
                int dy = m[freq][i].first - m[freq][j].first;
                int dx = m[freq][i].second - m[freq][j].second;

                // cout << "Attempting to put antinode at y = " << m[freq][i].first + dy << ", x = " << m[freq][i].second + dx << endl;
                if (isInBounds(m[freq][i].first + dy, m[freq][i].second + dx)) {
                    antinodes.insert(getStringPos(m[freq][i].first + dy, m[freq][i].second + dx));
                }

                // cout << "Attempting to put antinode at y = " << m[freq][j].first - dy << ", x = " << m[freq][j].second - dx << endl;
                if (isInBounds(m[freq][j].first - dy, m[freq][j].second - dx)) {
                    antinodes.insert(getStringPos(m[freq][j].first - dy, m[freq][j].second - dx));
                }
            }
        }
    }
}

void Map::generateNewAntinodes(){
    for (const char freq : frequencies) {
        for (unsigned int i = 0; i < m[freq].size(); ++i) {
            for (unsigned int j = i + 1; j < m[freq].size(); ++j) {
                pair<int, int> posi = m[freq][i];
                pair<int, int> posj = m[freq][j];

                int dy = posi.first - posj.first;
                int dx = posi.second - posj.second;

                unsigned int k = 0;
                while (isInBounds(posi.first + k * dy, posi.second + k * dx)) {
                    //cout << "Antinode (" << freq << ") put at y = " << m[freq][i].first + dy << ", x = " << m[freq][i].second + dx << endl;
                    antinodes.insert(getStringPos(posi.first + k * dy, posi.second + k * dx));
                    k++;
                }

                k = 0;
                while (isInBounds(posj.first - k * dy, posj.second - k * dx)) {
                    //cout << "Antinode (" << freq << ") put at y = " << m[freq][j].first - dy << ", x = " << m[freq][j].second - dx << endl;
                    antinodes.insert(getStringPos(posj.first - k * dy, posj.second - k * dx));
                    k++;
                }
            }
        }
    }
}

unsigned int Map::getAntinodesCount() {
    return antinodes.size();
};

void Map::writeResult(std::string filename) {
    ofstream myfile;
    myfile.open (filename);

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            bool found = false;
            for (auto freq : frequencies) {
                pair<int, int> target = make_pair(i,j);
                if (find(m[freq].begin(), m[freq].end(), target) != m[freq].end()) {
                    myfile << freq;
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (antinodes.contains(getStringPos(i,j))) {
                    myfile << "#";
                } else {
                    myfile << ".";
                }
            }

        }
        myfile << "\n";
    }

    myfile.close();
    cout << "file written" << endl;
};

void Map::log() {
    for (const auto &[key,val] : m) {
        cout << key << " : ";
        for (const auto &el : val) {
            cout << el.first << "-" << el.second << " ";
        }
        cout << endl;
    }

    cout << "Frequencies : ";
    for (const char c : frequencies) {
        cout << c << " ";
    }
    cout << endl;
}