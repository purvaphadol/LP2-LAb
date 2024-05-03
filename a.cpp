#include<bits/stdc++.h>
using namespace std;

struct City {
    string name;
    unordered_map<string, int> neighbors;
};

// Define the map of Romania as a graph with a subset of cities
unordered_map<string, City> romania_map = {
    {"Arad", {"Arad", {{"Sibiu", 140}, {"Timisoara", 118}}}},
    {"Sibiu", {"Sibiu", {{"Arad", 140}, {"Fagaras", 99}}}},
    {"Timisoara", {"Timisoara", {{"Arad", 118}, {"Lugoj", 111}}}},
    {"Fagaras", {"Fagaras", {{"Sibiu", 99}, {"Bucharest", 211}}}},
    {"Bucharest", {"Bucharest", {{"Fagaras", 211}}}}
};

// Heuristic values for each city
unordered_map<string, int> heuristic_values = {
    {"Arad", 366},
    {"Sibiu", 253},
    {"Timisoara", 329},
    {"Fagaras", 176},
    {"Bucharest", 0}
};

vector<string> astar(const string& start, const string& goal) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    unordered_map<string,int> costsofar;
    unordered_map<string,string> camefrom;

    pq.push({0, start});
    costsofar[start] = 0;

    while (!pq.empty()) {
        string curr = pq.top().second;
        pq.pop();

        if (curr == goal) {
            break;
        }

        for (const auto& negih : romania_map[curr].neighbors) {
            string nextcity = negih.first;
            int newcost = heuristic_values[nextcity] + negih.second + costsofar[curr];

            if (!costsofar.count(nextcity) || newcost < costsofar[nextcity]) {
                costsofar[nextcity] = newcost;
                int prio = heuristic_values[nextcity] + newcost;
                pq.push({prio, nextcity});
                camefrom[nextcity] = curr;
            }
        }
    }

    vector<string> path;
    string curr = goal;
    while (curr != start) {
        path.push_back(curr);
        curr = camefrom[curr];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    string start = "Arad";
    string goal = "Bucharest";

    vector<string> path = astar(start, goal);

    if (!path.empty()) {
        cout << "Path from " << start << " to " << goal << ":" << endl;
        for (const auto& city : path) {
            cout << city << " ";
        }
        cout << endl;
    } else {
        cout << "No path found!" << endl;
    }
    return 0;
}

