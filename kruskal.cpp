#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const int MAX_VERTICES = 100;
const int MAX_EDGES = 10000;

// Structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Function to find the Minimum Spanning Tree (MST) using Kruskal's algorithm
void KruskalMST(Edge edges[], int V, int E) {
    // Array to store the parent of each vertex
    int parent[MAX_VERTICES]; 
    
    // Initialize each vertex as its own parent initially
    for (int i = 0; i < V; ++i)
        parent[i] = i;

    // Array to store the edges of the MST
    Edge result[MAX_VERTICES]; 
    
    // Variable to keep track of the number of edges in the MST
    int e = 0;
    
    // Variable to store the total weight of the MST
    int totalWeight = 0;

    // Sort the edges in non-decreasing order of weight
    sort(edges, edges + E, [](const Edge &a, const Edge &b) {
        return a.weight < b.weight;
    });

    // Iterate through the sorted edges
    int i = 0; 
    while (e < V - 1 && i < E) {
        // Select the next edge with the smallest weight    evile
        Edge next_edge = edges[i++];

        // Find the root parent of the source and destination vertices
        int x = next_edge.source;
        int y = next_edge.destination;

        // Path compression: Update the parent of each vertex
        while (parent[x] != x)
            x = parent[x];
        while (parent[y] != y)
            y = parent[y];

        // If adding the edge does not create a cycle, include it in the MST
        if (x != y) {
            result[e++] = next_edge;
            totalWeight += next_edge.weight; // Add edge weight to total weight
            parent[y] = x;          // Merge the sets
        }
    }

    // Output the edges of the MST
    cout << "Edges in the MST:" << endl;
    for (i = 0; i < e; ++i)
        cout << result[i].source << " - " << result[i].destination << "   Weight: " << result[i].weight << endl;

    // Output the total weight of the MST
    cout << "Total Weight of MST: " << totalWeight << endl;
}

// Main function
int main() {
    ifstream inputFile("kruin.txt"); // Open the input file
    if (!inputFile) {
        cerr << "Failed to open the input file." << endl;
        return 1;
    }

    int V, E;
    inputFile >> V >> E; // Read number of vertices (V) and edges (E)

    // Read edges from the file
    Edge edges[MAX_EDGES];
    for (int i = 0; i < E; ++i) {
        inputFile >> edges[i].source >> edges[i].destination >> edges[i].weight;
    }

    inputFile.close(); // Close the input file

    // Call the KruskalMST function to find the MST
    KruskalMST(edges, V, E);

    return 0;
}
/*
// Example graph with 5 vertices and 7 edges
    int V = 5, E = 7;
    Edge edges[MAX_EDGES] = {
        {0, 1, 1},
        {0, 2, 7},
        {0, 3, 10},
        {0, 4, 5},
        {1, 2, 3},
        {2, 3, 4},
        {3, 4, 2}
    };

    // Call the KruskalMST function to find the MST
    KruskalMST(edges, V, E);

    return 0;
    */