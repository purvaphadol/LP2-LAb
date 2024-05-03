#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <queue>
using namespace std;

map<int, list<int>> m; 

void addEdge(int x, int y){
    m[x].push_back(y);
    m[y].push_back(x);
}

void dfs_helper(int src, map<int, bool> &visited)
{
    cout << src << " ";
    visited[src] = true;

    for(auto i : m[src]){
        if(!visited[i]){
            dfs_helper(i , visited);
        }
    }
}

void dfs(int src){
    map<int, bool> visited;
    dfs_helper(src, visited);
}

void bfs_recursive(queue<int> &q, map<int, bool> &visited)
{
    if(q.empty())
        return;
    
    int front_ele = q.front();
    q.pop();
    cout << front_ele << " ";

    for(auto i : m[front_ele]){
        if(!visited[i]){
            q.push(i);
            visited[i] = true;
        }
    }
    bfs_recursive(q, visited);
}

void bfs(int src){
    map<int, bool> visited;
    queue<int> q;
    
    q.push(src);
    visited[src] = true;

    bfs_recursive(q, visited);
}

int main(){
    ifstream inputFile("input.txt"); // Assuming input is stored in "input.txt"
    int x, y;
    while(inputFile >> x >> y){
        addEdge(x, y);
    }
    inputFile.close();

    cout << "DFS Traversal: ";
    dfs(0);
    cout << endl;

    cout << "BFS Traversal: ";
    bfs(0);
    cout << endl;
}


