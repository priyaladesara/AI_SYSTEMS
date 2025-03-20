#include <iostream>
#include <vector>
#include <limits>

// Node class to represent each node in the game tree
class Node {
public:
    char id;
    bool isMaximizer;
    int value;
    std::vector<Node*> children;
    bool isOnOptimalPath; 

    Node(char id, bool isMaximizer) : id(id), isMaximizer(isMaximizer), value(0), isOnOptimalPath(false) {}
    Node(char id, bool isMaximizer, int value) : id(id), isMaximizer(isMaximizer), value(value), isOnOptimalPath(false) {}

    ~Node() {
        for (auto child : children) {
            delete child;
        }
    }
};

// Function to build the game tree
Node* buildGameTree() {
    Node* rootA = new Node('A', true);
    Node* nodeB = new Node('B', false);
    Node* nodeC = new Node('C', false);
    rootA->children = {nodeB, nodeC};

    Node* nodeD = new Node('D', true);
    Node* nodeE = new Node('E', true);
    nodeB->children = {nodeD, nodeE};

    Node* nodeF = new Node('F', true);
    Node* nodeG = new Node('G', true);
    nodeC->children = {nodeF, nodeG};

    nodeD->children = {new Node('H', false, -1), new Node('I', false, 4)};
    nodeE->children = {new Node('J', false, 2), new Node('K', false, 9)};
    nodeF->children = {new Node('L', false, -3), new Node('M', false, -5)};
    nodeG->children = {new Node('N', false, 0), new Node('O', false, 7)};

    return rootA;
}

// Alpha-Beta Pruning function with optimal path tracking
int alphaBeta(Node* node, int alpha, int beta, bool isMaximizingPlayer, Node*& optimalNode) {
    if (node->children.empty()) {
        return node->value;
    }

    Node* bestChild = nullptr;
    if (isMaximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (Node* child : node->children) {
            Node* tempOptimal;
            int eval = alphaBeta(child, alpha, beta, false, tempOptimal);
            if (eval > maxEval) {
                maxEval = eval;
                bestChild = child;
            }
            alpha = std::max(alpha, eval);
            if (beta <= alpha) break; // Beta cut-off (pruning)
        }
        node->value = maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (Node* child : node->children) {
            Node* tempOptimal;
            int eval = alphaBeta(child, alpha, beta, true, tempOptimal);
            if (eval < minEval) {
                minEval = eval;
                bestChild = child;
            }
            beta = std::min(beta, eval);
            if (beta <= alpha) break; // Alpha cut-off (pruning)
        }
        node->value = minEval;
    }

    optimalNode = bestChild;  // Track optimal node
    return node->value;
}

// Function to mark the optimal path
void findOptimalPath(Node* root) {
    Node* current = root;
    current->isOnOptimalPath = true;
    while (current) {
        Node* next = nullptr;
        alphaBeta(current, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), current->isMaximizer, next);
        if (next) {
            next->isOnOptimalPath = true;
            current = next;
        } else {
            break;
        }
    }
}

// Function to print the game tree in ASCII format
void printTree(Node* node, std::string prefix = "", bool isLast = true) {
    std::cout << prefix;
    std::cout << (isLast ? "+-- " : "|-- ");

    if (node->isOnOptimalPath) std::cout << "[OPTIMAL] ";
    std::cout << node->id << " (" << node->value << ")" << std::endl;

    prefix += isLast ? "    " : "|   ";
    
    for (size_t i = 0; i < node->children.size(); i++) {
        printTree(node->children[i], prefix, i == node->children.size() - 1);
    }
}

// Function to explain the optimal path
void explainOptimalPath() {
    std::cout << "\nOptimal Path Explanation (A-B-D-I):" << std::endl;
    std::cout << "1. Node I has terminal value 4.\n";
    std::cout << "2. Node D selects max(-1, 4) = 4.\n";
    std::cout << "3. Node B selects min(4, 9) = 4.\n";
    std::cout << "4. Node A selects max(4, -3) = 4.\n";
    std::cout << "Final optimal path: **A → B → D → I**\n";
}

int main() {
    Node* root = buildGameTree();
    Node* optimalNode = nullptr;

    int optimalValue = alphaBeta(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), root->isMaximizer, optimalNode);
    findOptimalPath(root);

    std::cout << "Game Tree after Alpha-Beta Pruning (Optimal Path Highlighted):\n";
    printTree(root);

    std::cout << "\nThe optimal value guaranteed by the maximizer is: " << optimalValue << std::endl;
    explainOptimalPath();

    delete root;
    return 0;
}
