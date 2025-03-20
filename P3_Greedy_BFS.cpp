#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>


using namespace std;

// Define a Min-Heap priority queue using a custom comparator
typedef pair<int, char> pi; // (heuristic, node)

// Best First Search Function
void best_first_search(unordered_map<char, vector<pair<char, int>>> &graph, 
                       unordered_map<char, int> &heuristic, char start, char goal) {
    
    priority_queue<pi, vector<pi>, greater<pi>> open_list; // Min-Heap (Priority Queue)
    unordered_set<char> closed_set; // Set for visited nodes

    // Push the start node into OPEN list
    open_list.push({heuristic[start], start});

    while (!open_list.empty()) {
        auto [h, node] = open_list.top(); // Extract node with lowest heuristic value
        open_list.pop();

        if (closed_set.find(node) != closed_set.end())
            continue; // Skip if already visited

        cout << "Visiting: " << node << endl;
        
        if (node == goal) {
            cout << "Goal reached!" << endl;
            return;
        }

        closed_set.insert(node); // Mark node as visited

        // Explore neighbors
        for (auto &[neighbor, cost] : graph[node]) {
            if (closed_set.find(neighbor) == closed_set.end()) {
                open_list.push({heuristic[neighbor], neighbor}); // Push with heuristic value
            }
        }
    }
}

int main() {
    // Graph Representation (Adjacency List)
    unordered_map<char, vector<pair<char, int>>> graph = {
        {'S', {{'A', 7}, {'B', 2}, {'C', 3}}},
        {'A', {{'D', 4}}},
        {'B', {{'D', 4}, {'H', 1}}},
        {'C', {{'L', 2}}},
        {'D', {{'F', 5}}},
        {'H', {{'G', 3}}},
        {'L', {{'I', 4}, {'J', 4}}},
        {'G', {{'E', 2}}},
        {'I', {{'K', 4}}},
        {'J', {{'K', 4}}},
        {'K', {{'E', 5}}},
        {'E', {}} // Goal Node
    };

    // Heuristic Values (h(n))
    unordered_map<char, int> heuristic = {
        {'S', 10}, {'A', 9}, {'B', 7}, {'C', 8}, {'D', 8}, {'F', 6}, {'H', 6}, {'G', 3},
        {'L', 6}, {'I', 4}, {'J', 4}, {'K', 3}, {'E', 0}
    };

    // Run Best First Search
    best_first_search(graph, heuristic, 'S', 'E');

    return 0;
}
