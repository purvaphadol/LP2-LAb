#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void findZero(vector<vector<int>> board, int &x, int &y){
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board.size(); j++){
            if (board[i][j] == 0){
                x = i;
                y = j;
                return;
            }
        }
    }
}

void printBoard(vector<vector<int>> board){
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board.size(); j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isGoalState(vector<vector<int> > &board, vector<vector<int> > &goal) {
     return board == goal;
}

int findMisplacedTiles(vector<vector<int>> &board, vector<vector<int> > &goal){
    int count = 0;

    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board.size(); j++){
            if (board[i][j] != goal[i][j])
                count++;
        }
    }

    return count;
}

void aStar(vector<vector<int>> &board, vector<vector<int>> &goal, int depth, int x, int y){
    priority_queue<pair<int, vector<vector<int>>>,   // f(n), board
                   vector<  pair<int, vector<vector<int>>> >,
                   greater< pair<int, vector<vector<int>>>> > pq;

    int h = findMisplacedTiles(board, goal);

    pq.push({depth + h, board}); // depth + heuristic

    while (!pq.empty()){
        vector<vector<int>> curr = pq.top().second;

        pq.pop();
        
        printBoard(curr);

        int x, y;
        findZero(curr, x, y);

        if(isGoalState(curr, goal)){
            cout << "Goal State Reached" << endl;
            return;
        }

        int dx[] = {0, 0, -1, 1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++){
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < curr.size() && newY >= 0 && newY < curr[newX].size()){
                swap(curr[x][y], curr[newX][newY]);
                int g = depth + 1; // Update depth
                h = findMisplacedTiles(curr, goal);
                pq.push({g + h, curr});
                swap(curr[x][y], curr[newX][newY]);
            }
        }
    }
    return;
}

int main() {
    //definig the initial state
    // 0 -> blank space -> move this

    vector<vector<int>> board = {
        {1, 2, 3},
        {0, 4, 6},
        {7, 5, 8}
    };

    //goal state
    // vector<vector<int>> goal = {
    //     {1, 2, 3},
    //     {8, 0, 4},
    //     {7, 6, 5}
    // };

    vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    int x, y;

    //finding the empty box -> find black space -> put co-ordinate of blanck space in x y -> x=2,y=1
    findZero(board, x, y);


    aStar(board, goal, 0, x, y);

    return 0;
}