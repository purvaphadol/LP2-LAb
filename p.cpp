#include <iostream>
#include <fstream>
#include <limits.h>
using namespace std;
#define V 5

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;
    for (int i = 0; i < V; i++)
        if (mstSet[i] == false && key[i] < min)
            min = key[i], min_index = i;
    return min_index;
}

void printMST(int parent[], int graph[V][V]) {
    cout << "Edge \tWeight\n";
    int total_cost = 0;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
        total_cost += graph[i][parent[i]];
    }
    cout << "Total Cost: " << total_cost << endl;
}

void primMST(int graph[V][V]) {
    int parent[V];                                                                                                                                                           
    int key[V];
    bool mstSet[V];

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int i = 0; i < V; i++)
            if (graph[u][i] && mstSet[i] == false && graph[u][i] < key[i])
                parent[i] = u, key[i] = graph[u][i];
    }

    printMST(parent, graph);
}

int main() {
    int graph[V][V];
    ifstream inputFile("in.txt");
    if (!inputFile) {
        cerr << "Unable to open file input.txt";
        return 1;
    }

    // Read graph from file
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            inputFile >> graph[i][j];

    inputFile.close();

    primMST(graph);
    return 0;
}
