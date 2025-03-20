#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const int N = 3;

int rowMove[] = {0, -1, 0, 1};
int colMove[] = {-1, 0, 1, 0};
string moveNames[] = {"Left", "Up", "Right", "Down"};

struct PuzzleState {
    vector<vector<int>> board;
    int zeroRow, zeroCol, depth;
    string moves;

    bool operator<(const PuzzleState &other) const {
        return board < other.board;
    }
};

void printBoard(const vector<vector<int>> &board) {
    for (auto &row : board) {
        for (int num : row) {
            if (num == 0)
                cout << "  ";
            else
                cout << num << " ";
        }
        cout << endl;
    }
}
bool isGoalState(const vector<vector<int>> &board, const vector<vector<int>> &goal) {
    return board == goal;
}
bool isValidMove(int newRow, int newCol) {
    return newRow >= 0 && newRow < N && newCol >= 0 && newCol < N;
}
void solvePuzzle(vector<vector<int>> startBoard, vector<vector<int>> goalBoard) {
    queue<PuzzleState> q;
    set<vector<vector<int>>> visited;

    int zeroRow, zeroCol;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (startBoard[i][j] == 0) {
                zeroRow = i;
                zeroCol = j;
            }
        }
    }

    PuzzleState start = {startBoard, zeroRow, zeroCol, 0, ""};
    q.push(start);
    visited.insert(startBoard);

    while (!q.empty()) {
        PuzzleState current = q.front();
        q.pop();

        cout << "step " << current.depth << ": " << current.moves << endl;
        printBoard(current.board);
        cout << "------------------------\n";

        if (isGoalState(current.board, goalBoard)) {
            cout << "Solution found\n";
            cout << "Moves: " << current.moves << endl;
            return;
        }
        for (int i = 0; i < 4; i++) {
            int newRow = current.zeroRow + rowMove[i];
            int newCol = current.zeroCol + colMove[i];

            if (isValidMove(newRow, newCol)) {
                vector<vector<int>> newBoard = current.board;
                swap(newBoard[current.zeroRow][current.zeroCol], newBoard[newRow][newCol]);

                if (visited.find(newBoard) == visited.end()) {
                    visited.insert(newBoard);
                    q.push({newBoard, newRow, newCol, current.depth + 1, current.moves + moveNames[i] + " -> "});
                }
            }
        }
    }

    cout << "No solution found!\n";
}

int main() {
    vector<vector<int>> startBoard(3, vector<int>(3));
    vector<vector<int>> goalBoard(3, vector<int>(3));

    cout << "Enter initial state (3x3 matrix):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> startBoard[i][j];

    cout << "Enter goal state (3x3 matrix):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> goalBoard[i][j];

    cout << "Initial State:\n";
    printBoard(startBoard);
    cout << "------------------------\n";

    solvePuzzle(startBoard, goalBoard);

    return 0;
}