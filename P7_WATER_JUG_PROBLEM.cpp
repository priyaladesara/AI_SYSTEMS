#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

typedef tuple<int, int, string> State;

vector<string> rules = {
    "(0) Initial State",
    "(1) Fill 4L jug",
    "(2) Fill 3L jug",
    "(3) Pour some water from 4L",
    "(4) Pour some water from 3L",
    "(5) Empty 4L jug",
    "(6) Empty 3L jug",
    "(7) Pour water from 3L to 4L until 4L is full",
    "(8) Pour water from 4L to 3L until 3L is full",
    "(9) Pour all water from 3L to 4L",
    "(10) Pour all water from 4L to 3L"
};

vector<State> water_jug_bfs(int jug1, int jug2, int target_x, int target_y) {
    set<pair<int, int>> visited;
    queue<tuple<int, int, vector<State>, string>> q;
    
    vector<State> initial_path = {make_tuple(jug1, jug2, rules[0])};
    q.push(make_tuple(jug1, jug2, initial_path, ""));

    while (!q.empty()) {
        int x, y;
        vector<State> path;
        string rule;
        tie(x, y, path, rule) = q.front();
        q.pop();

        if (visited.count({x, y}))
            continue;

        visited.insert({x, y});

        if (x == target_x && y == target_y)
            return path;

        vector<pair<pair<int, int>, string>> next_states = {
            {{4, y}, rules[1]},
            {{x, 3}, rules[2]},
            {{x - min(x, 1), y}, rules[3]},
            {{x, y - min(y, 1)}, rules[4]},
            {{0, y}, rules[5]},
            {{x, 0}, rules[6]},
            {{x - min(x, 3 - y), y + min(x, 3 - y)}, rules[7]},
            {{x + min(y, 4 - x), y - min(y, 4 - x)}, rules[8]},
            {{(x + y <= 3) ? 0 : x - (3 - y), (x + y <= 3) ? x + y : 3}, rules[9]},
            {{(x + y <= 4) ? x + y : 4, (x + y <= 4) ? 0 : y - (4 - x)}, rules[10]}
        };

        for (auto &state : next_states) {
            if (!visited.count(state.first)) {
                vector<State> new_path = path;
                new_path.push_back(make_tuple(state.first.first, state.first.second, state.second));
                q.push(make_tuple(state.first.first, state.first.second, new_path, state.second));
            }
        }
    }

    return {};
}

int main() {
    int initial_x = 0, initial_y = 0;
    int final_x = 3, final_y = 1;

    vector<State> solution = water_jug_bfs(initial_x, initial_y, final_x, final_y);

    if (!solution.empty()) {
        cout << "Steps to reach the goal:" << endl;
        for (size_t i = 0; i < solution.size(); ++i) {
            int step_x, step_y;
            string rule;
            tie(step_x, step_y, rule) = solution[i];
            cout << "Step " << i << ": (" << step_x << ", " << step_y << ") - Rule applied: " << rule << endl;
        }
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
