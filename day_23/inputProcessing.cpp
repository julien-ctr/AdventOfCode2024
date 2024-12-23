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

vector<string> bronKerbosch(const unordered_map<string, vector<string>> &neighbors, 
                            unordered_set<string> &R, 
                            unordered_set<string> &P, 
                            unordered_set<string> &X) {

    // Base case: If P and X are both empty, we can't extend more
    if (P.empty() && X.empty()) {
        return vector<string>(R.begin(), R.end());
    }

    // Select a pivot node from P ⋃ X (pick the node with the most neighbors in P)
    string pivot;
    int maxNeighbors = 0;
    for (const string &candidate : P) {
        int count = count_if(neighbors.at(candidate).begin(), neighbors.at(candidate).end(),
                             [&](const string &neighbor) {return P.count(neighbor);});
        if (count > maxNeighbors) {
            maxNeighbors = count;
            pivot = candidate;
        }
    }

    unordered_set<string> PMinusPivotNeighbors;
    // Update P based on the pivot
    for (const string &v : P) {
        if (find(neighbors.at(v).begin(), neighbors.at(v).end(), pivot) == neighbors.at(v).end()) {
            PMinusPivotNeighbors.insert(v);  // Remove v from P
        }
    }

    vector<string> maxClique;

    // Iterate over all remaining nodes in P
    for (const string& v : PMinusPivotNeighbors) {
        unordered_set<string> newR = R;
        newR.insert(v); // Add v to R (current clique)

        // Create new sets for P and X (P ⋂ N(v) & X ⋂ N(v))
        unordered_set<string> newP, newX;
        for (const string &neighbor : neighbors.at(v)) {
            if (P.count(neighbor)) newP.insert(neighbor);
            if (X.count(neighbor)) newX.insert(neighbor);
        }

        // Recursively call Bron-Kerbosch for the new sets
        vector<string> candidateClique = bronKerbosch(neighbors, newR, newP, newX);

        // If a larger clique is found, update the maxClique
        if (candidateClique.size() > maxClique.size()) {
            maxClique = candidateClique;
        }

        // Move v from P to X
        P.erase(v);
        X.insert(v);
    }

    return maxClique;
}

vector<string> findMaxClique(const unordered_map<string, vector<string>>& neighbors) {
    unordered_set<string> R, P, X;
    vector<string> maxClique;

    // Initialize P with all nodes in the graph
    for (const auto& [key, val] : neighbors) {
        P.insert(key);
    }

    // Start the Bron-Kerbosch algorithm
    maxClique = bronKerbosch(neighbors, R, P, X);

    return maxClique;
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
   
    for (const auto& group : groups) {
        int count = 0;
        if (startsWithT(group[0])) count++;
        if (startsWithT(group[1])) count++;
        if (startsWithT(group[2])) count++;

        if (count >= 1) {++gc;}
    }
    vector<string> maxGroup = findMaxClique(neighbors);

    sort(maxGroup.begin(),maxGroup.end());

    stars.first = gc;
    stars.second = maxGroup[0];
    for (unsigned int i = 1; i < maxGroup.size(); ++i) stars.second += "," + maxGroup[i] ;

    return stars;
}