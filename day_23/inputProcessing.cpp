#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, unordered_map<string,vector<string>> &neighbors) {
    for (const string &line : text) {
        string a = line.substr(0,2);
        string b = line.substr(3);

        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
}

bool startsWithT(const string &str) {
    return !str.empty() && str[0] == 't';
}

bool isConnectedToAll(const unordered_map<string,vector<string>> &neighbors, const vector<string> &group, const string &computer) {
    for (const string el : group) {
        if (find(neighbors.at(computer).begin(), neighbors.at(computer).end(), el) == neighbors.at(computer).end()) {
            return false;
        }
    }

    return true;
}

vector<string> findMaxExtend(const unordered_map<string,vector<string>> &neighbors, vector<string> &group) {
    vector<string> oldGroup;

    while (oldGroup != group) {
        oldGroup = group;
        
        unordered_set<string> possibleNeighbours;
        for (unsigned int i = 0; i < group.size(); ++i) {
            for (const string &neigh : neighbors.at(group[i])) {
                if (find(group.begin(), group.end(), neigh) == group.end()) {// If not already in the group
                    possibleNeighbours.insert(neigh);
                }
            }
        }

        for (const string &candidate : possibleNeighbours) {
            if (isConnectedToAll(neighbors, group, candidate)) {
                group.push_back(candidate);
            }
        }
    }

    return group;
}

pair<int64_t, string> countStars(const vector<string> &text) {
    pair<int64_t, string> stars = make_pair(0,"");
    
    unordered_map<string,vector<string>> neighbors;
    unordered_set<array<string, 3>, ArrayHash> groups;

    loadData(text, neighbors);

    // Process groups
    for (const auto &[key, val] : neighbors) {
        if (val.size() < 2) continue;

        for (unsigned int i = 0; i < val.size(); ++i) {
            vector<string> iNeighbors = neighbors[val[i]];
            for (unsigned int j = i + 1; j < val.size(); ++j) {
                if (find(iNeighbors.begin(), iNeighbors.end(), val[j]) != iNeighbors.end()) {
                    array<string, 3> group = {key, val[i], val[j]};
                    sort(group.begin(), group.end());
                    groups.insert(group);
                }
            }
        }
        
    }

    int gc = 0;
    vector<string> maxGroup;

    for (const auto& group : groups) {
        int count = 0;
        if (startsWithT(group[0])) count++;
        if (startsWithT(group[1])) count++;
        if (startsWithT(group[2])) count++;

        if (count >= 1) {++gc;}

        if (find(maxGroup.begin(), maxGroup.end(), group[0]) != maxGroup.end() ||
            find(maxGroup.begin(), maxGroup.end(), group[1]) != maxGroup.end() ||
            find(maxGroup.begin(), maxGroup.end(), group[2]) != maxGroup.end()) {
            continue;
        }

        vector<string> gp = {group[0], group[1], group[2]};
        vector<string> maxExtend = findMaxExtend(neighbors, gp);

        if (maxExtend.size() > maxGroup.size()) maxGroup = maxExtend;
    }

    sort(maxGroup.begin(),maxGroup.end());

    stars.first = gc;
    stars.second = maxGroup[0];
    for (unsigned int i = 1; i < maxGroup.size(); ++i) stars.second += "," + maxGroup[i] ;

    return stars;
}