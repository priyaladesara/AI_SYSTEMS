#include <iostream>
#include <queue>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

// Function to generate possible next states
vector<string> generate1(string current) {
    vector<string> nextStates;
    int blankIndex = current.find('_'); 
    int row = blankIndex / 3;
    int col = blankIndex % 3;
    string p;

    if (row > 0) { // Move up
        p = current;
        swap(p[blankIndex], p[blankIndex - 3]);
        nextStates.push_back(p);
    }
    if (row < 2) { // Move down
        p = current;
        swap(p[blankIndex], p[blankIndex + 3]);
        nextStates.push_back(p);
    }
    if (col > 0) { // Move left
        p = current;
        swap(p[blankIndex], p[blankIndex - 1]);
        nextStates.push_back(p);
    }
    if (col < 2) { // Move right
        p = current;
        swap(p[blankIndex], p[blankIndex + 1]);
        nextStates.push_back(p);
    }
    return nextStates;
}

// Function to print a state in matrix form
void printMatrix(string state) {
    for (int i = 0; i < 9; i++) {
        if (state[i] == '_')
            cout << "  ";
        else
            cout << state[i] << " ";
        
        if ((i + 1) % 3 == 0) cout << endl;
    }
    cout << "-------------------" << endl;
}

// Function to check if transformation is possible
bool canTransform(string st, string ta) {
    if (st == ta) {
        cout << "Initial state is already the target state:" << endl;
        printMatrix(st);
        return true;
    }
    queue<pair<string, vector<string>>> q;
    unordered_set<string> visited;
    q.push({st, {st}});
    visited.insert(st);
    
    while (!q.empty()) {
        auto [current, path] = q.front();
        q.pop();
        
        printMatrix(current);
        
        vector<string> nextStates = generate1(current);
        for (const string &next : nextStates) {
            if (next == ta) {
                path.push_back(next);
                printMatrix(next);
                cout << "Solution Found!" << endl;
                return true;
            }
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                auto newPath = path;
                newPath.push_back(next);
                q.push({next, newPath});
            }
        }
    }
    return false;
}

// Function to read board as a string
string readBoard() {
    string board = "";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            string token;
            cin >> token;
            if (token == "0") {
                token = "_"; 
            }
            board += token;
        }
    }
    return board;
}

// Main function
int main() {
    cout << "Enter the start state (3x3 matrix, use 0 for blank):" << endl;
    string start = readBoard();
    cout << "Enter the target state (3x3 matrix, use 0 for blank):" << endl;
    string target = readBoard();
    
    if (!canTransform(start, target)) {
        cout << "It is NOT possible to transform the initial state to the target state." << endl;
    }
    
    return 0;
}
