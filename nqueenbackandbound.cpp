#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
    // Check if there is a queen in the same row
    for (int i = 0; i < col; ++i)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (int i = row, j = col; i < N && j >= 0; ++i, --j)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQueensUtil(vector<vector<int>>& board, int col, int N, int& solutions) {
    if (col >= N) {
        ++solutions;
        cout << "Solution " << solutions << ":\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j)
                cout << board[i][j] << " ";
            cout << endl;
        }
        cout << endl;
        return true;
    }

    bool res = false;
    for (int i = 0; i < N; ++i) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 1;

            res = solveNQueensUtil(board, col + 1, N, solutions) || res;

            board[i][col] = 0; // Backtrack
        }
    }

    return res;
}

void solveNQueens(int N) {
    vector<vector<int>> board(N, vector<int>(N, 0));
    int solutions = 0;

    solveNQueensUtil(board, 0, N, solutions);

    if (solutions == 0)
        cout << "No solution exists\n";
    else
        cout << "Total solutions: " << solutions << endl;
}

int main() {
    int N = 4;
    solveNQueens(N);
    return 0;
}
