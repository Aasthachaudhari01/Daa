
#include <iostream>
using namespace std;

#define MAX 1000
#define INF 999999

struct Edge {
    int dest, cost;
    Edge* next;
};

Edge* adj[MAX];
int stage[MAX];
int dp[MAX];
int nextNode[MAX];

void addRoute(int u, int v, int cost) {
    Edge* temp = new Edge;
    temp->dest = v;
    temp->cost = cost;
    temp->next = adj[u];
    adj[u] = temp;
}

void dynamicProgramming(int source, int destination,
                        int n, int stages) {
    // Step 1: Initialize DP table
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        nextNode[i] = -1;
    }

    // Base case: Cost from destination to itself is zero
    dp[destination] = 0;

    // Step 2: Process stages backward
    for (int s = stages - 1; s >= 1; s--) {
        for (int u = 1; u <= n; u++) {
            if (stage[u] == s) {
                Edge* temp = adj[u];

                // Step 3: Apply DP recurrence
                while (temp != NULL) {
                    int v = temp->dest;
                    int weight = temp->cost;

                    if (dp[v] != INF) {
                        int newCost = weight + dp[v];

                        if (newCost < dp[u]) {
                            dp[u] = newCost;
                            nextNode[u] = v;
                        }
                    }

                    temp = temp->next;
                }
            }
        }
    }

    // Step 4: Display minimum cost and path
    cout << "\nSource      : " << source;
    cout << "\nDestination : " << destination;

    if (dp[source] == INF) {
        cout << "\nNo route available\n";
        return;
    }

    cout << "\nMinimum Cost: " << dp[source];
    cout << "\nOptimal Route: ";

    int current = source;

    while (current != destination) {
        cout << current << " -> ";
        current = nextNode[current];

        if (current == -1) {
            cout << "No route available\n";
            return;
        }
    }

    cout << destination << endl;
}

int main() {
    int n, stages, routes;
    int source, destination;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter number of stages: ";
    cin >> stages;

    for (int i = 1; i <= n; i++) {
        adj[i] = NULL;
    }

    cout << "\nEnter stage number for each node:\n";

    for (int i = 1; i <= n; i++) {
        cout << "Enter stage of node " << i << ": ";
        cin >> stage[i];
    }

    cout << "\nEnter number of routes: ";
    cin >> routes;

    cout << "\nEnter route details:\n";
    cout << "Format: Source Destination Cost\n";

    for (int i = 1; i <= routes; i++) {
        int u, v, cost;

        cout << "Route " << i << ": ";
        cin >> u >> v >> cost;

        addRoute(u, v, cost);
    }

    cout << "\nEnter source node: ";
    cin >> source;

    cout << "Enter destination node: ";
    cin >> destination;

    dynamicProgramming(source, destination, n, stages);

    return 0;
}
