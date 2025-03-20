#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

unordered_map<char, vector<pair<char, int>>> graph = {
    {'A', {{'B', 10}, {'C', 15}, {'D', 20}}},
    {'B', {{'E', 10}}},
    {'C', {{'F', 10}}},
    {'D', {{'F', 5}}},
    {'E', {{'H', 5}}},
    {'F', {{'G', 10}}},
    {'H', {{'G', 5}}},
    {'G', {}}
};

unordered_map<char, int> heuristic = {
    {'A', 40}, {'B', 32}, {'C', 25}, {'D', 35},
    {'E', 19}, {'F', 17}, {'G', 0},  {'H', 10}
};

void aStarSearch(char start, char goal) {
    priority_queue<pair<int, pair<int, char>>, vector<pair<int, pair<int, char>>>, greater<pair<int, pair<int, char>>>> pq;
    unordered_map<char, int> g_cost;
    set<char> visited;
    int iteration = 1;

    pq.push({heuristic[start], {0, start}}); // f(n) = g(n) + h(n)
    g_cost[start] = 0;
    cout << "A* Search Execution:\n";

    while (!pq.empty()) {
        cout << "\nIteration " << iteration << ":\n";

        // Display Open List (Priority Queue)
        cout << "Open List (f=g+h): ";
        vector<pair<int, pair<int, char>>> temp;
        while (!pq.empty()) {
            temp.push_back(pq.top());
            cout << pq.top().second.second << "(f=" << pq.top().first << ", g=" << pq.top().second.first << ") ";
            pq.pop();
        }
        cout << endl;

        for (auto& node : temp) {
            pq.push(node);
        }

        char current = temp[0].second.second;
        int g_current = temp[0].second.first;
        int f_current = temp[0].first;
        pq.pop();

        cout << "Selected Node: " << current << " (f=" << f_current << ", g=" << g_current << ")\n";

        if (visited.find(current) != visited.end()) continue;
        visited.insert(current);

        cout << "Closed List: ";
        for (char node : visited) {
            cout << node << " ";
        }
        cout << endl;

        if (current == goal) {
            cout << "\nGoal Reached!\n";
            return;
        }

        for (auto& neighbor : graph[current]) {
            char next = neighbor.first;
            int cost = neighbor.second;
            int new_g = g_current + cost;
            int new_f = new_g + heuristic[next];

            if (visited.find(next) == visited.end() || new_g < g_cost[next]) {
                g_cost[next] = new_g;
                pq.push({new_f, {new_g, next}});
            }
        }
        iteration++;
    }
    cout << "\nGoal Not Found!\n";
}

int main() {
    char start = 'A';
    char goal = 'G';
    aStarSearch(start, goal);
    return 0;
}
