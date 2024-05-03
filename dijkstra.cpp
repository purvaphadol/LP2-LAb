#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>>& adjMatrix, int src, vector<int>& parent) {
        vector<bool> visited(V, false);
        vector<int> dist(V, INT_MAX);

        dist[src] = 0;

        for (int i = 0; i < V - 1; ++i) {
            int minDist = INT_MAX, minIndex;
            for (int j = 0; j < V; ++j) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    minIndex = j;
                }
            }

            int u = minIndex;
            visited[u] = true;

            for (int v = 0; v < V; ++v) {
                if (!visited[v] && adjMatrix[u][v] && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    parent[v] = u;
                }
            }
        }

        return dist;
    }

    vector<int> reconstructPath(int src, int dest, const vector<int>& parent) {
        vector<int> path;
        for (int v = dest; v != src; v = parent[v])
            path.push_back(v);
        path.push_back(src);
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int V = 6;

    vector<vector<int>> adjMatrix(V, vector<int>(V, 0));
    adjMatrix[0][1] = 4;
    adjMatrix[0][2] = 4;
    adjMatrix[1][0] = 4;
    adjMatrix[1][2] = 2;
    adjMatrix[2][0] = 4;
    adjMatrix[2][1] = 2;
    adjMatrix[2][3] = 3;
    adjMatrix[2][4] = 1;
    adjMatrix[2][5] = 6;
    adjMatrix[3][2] = 3;
    adjMatrix[3][5] = 2;
    adjMatrix[4][2] = 1;
    adjMatrix[4][5] = 3;
    adjMatrix[5][2] = 6;
    adjMatrix[5][3] = 2;
    adjMatrix[5][4] = 3;

    int src, dest;
    cout << "Enter source and destination vertices: ";
    cin >> src >> dest;

    Solution obj;

    vector<int> parent(V, -1);
    vector<int> res = obj.dijkstra(V, adjMatrix, src, parent);

    int totalDistance = res[dest];
    vector<int> path = obj.reconstructPath(src, dest, parent);

    cout << "Shortest path from vertex " << src << " to vertex " << dest << ": ";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1)
            cout << " -> ";
    }
    cout << "\nTotal distance: " << totalDistance << endl;

    return 0;
}

