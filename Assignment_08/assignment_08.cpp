
#include <iostream>
#include <queue>
#include <deque>
using namespace std;

const int MAX = 15;
const int INF = 1000000000;

int n;
int cost[MAX][MAX];
int bestPath[MAX + 1];
long long bestCost = INF;

struct Node {
    int matrix[MAX][MAX];
    int path[MAX];
    bool visited[MAX];
    int level;
    int currentCity;
    long long pathCost;
    long long bound;
};

struct Compare {
    bool operator()(const Node &a, const Node &b) const {
        return a.bound > b.bound;
    }
};

long long reduceMatrix(int matrix[MAX][MAX]) {
    long long reductionCost = 0;

    // Row reduction
    for (int i = 0; i < n; i++) {
        int minimum = INF;

        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < minimum)
                minimum = matrix[i][j];
        }

        if (minimum != INF && minimum > 0) {
            reductionCost += minimum;

            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != INF)
                    matrix[i][j] -= minimum;
            }
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        int minimum = INF;

        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < minimum)
                minimum = matrix[i][j];
        }

        if (minimum != INF && minimum > 0) {
            reductionCost += minimum;

            for (int i = 0; i < n; i++) {
                if (matrix[i][j] != INF)
                    matrix[i][j] -= minimum;
            }
        }
    }

    return reductionCost;
}

void tspBranchAndBound(int start) {
    priority_queue<Node, deque<Node>, Compare> pq;

    Node root;

    root.level = 0;
    root.currentCity = start;
    root.pathCost = 0;

    for (int i = 0; i < n; i++) {
        root.path[i] = -1;
        root.visited[i] = false;

        for (int j = 0; j < n; j++)
            root.matrix[i][j] = cost[i][j];
    }

    root.path[0] = start;
    root.visited[start] = true;

    root.bound = reduceMatrix(root.matrix);
    pq.push(root);

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        // Prune unpromising nodes
        if (node.bound >= bestCost)
            continue;

        // All cities have been visited
        if (node.level == n - 1) {
            int lastCity = node.currentCity;

            if (cost[lastCity][start] != INF) {
                long long totalCost =
                    node.pathCost + cost[lastCity][start];

                if (totalCost < bestCost) {
                    bestCost = totalCost;

                    for (int i = 0; i < n; i++)
                        bestPath[i] = node.path[i];

                    bestPath[n] = start;
                }
            }

            continue;
        }

        int u = node.currentCity;

        // Try every unvisited city
        for (int v = 0; v < n; v++) {
            if (node.visited[v] ||
                cost[u][v] == INF ||
                node.matrix[u][v] == INF)
                continue;

            Node child = node;

            child.path[child.level + 1] = v;
            child.visited[v] = true;
            child.level++;
            child.currentCity = v;

            child.pathCost =
                node.pathCost + cost[u][v];

            // Block the outgoing edges from city u
            for (int j = 0; j < n; j++)
                child.matrix[u][j] = INF;

            // Block incoming edges to city v
            for (int i = 0; i < n; i++)
                child.matrix[i][v] = INF;

            // Prevent returning to the start too early
            // Keep the return edge for the final city
            if (child.level < n - 1)
                child.matrix[v][start] = INF;

            child.bound =
                node.bound + node.matrix[u][v]
                + reduceMatrix(child.matrix);

            // Add only promising nodes
            if (child.bound < bestCost)
                pq.push(child);
        }
    }
}

int main() {
    cout << "Enter number of cities (maximum "
         << MAX << "): ";
    cin >> n;

    if (n < 2 || n > MAX) {
        cout << "Invalid number of cities.\n";
        return 0;
    }

    cout << "Enter the cost matrix (-1 for no direct route):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];

            if (i == j || cost[i][j] == -1)
                cost[i][j] = INF;
        }
    }

    tspBranchAndBound(0);

    if (bestCost == INF) {
        cout << "\nNo complete tour exists.\n";
    } else {
        cout << "\nOptimal Delivery Route: ";

        for (int i = 0; i <= n; i++)
            cout << bestPath[i] << " ";

        cout << "\nMinimum Delivery Cost: "
             << bestCost << endl;
    }

    return 0;
}
