
#include <iostream>
#include <queue>
using namespace std;

#define MAX 1000
#define INF 999999

struct Edge {
    int dest, cost;
    Edge* next;
};

Edge* adj[MAX];
int dist[MAX], parent[MAX], stage[MAX];

void addRoute(int u, int v, int cost) {
    Edge* temp = new Edge;
    temp->dest = v;
    temp->cost = cost;
    temp->next = adj[u];
    adj[u] = temp;
}

void dijkstra(int source, int destination, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    priority_queue<pair<int, int>,
                   greater<pair<int, int> > > pq;

    dist[source] = 0;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (cost != dist[u])
            continue;

        if (u == destination)
            break;

        Edge* temp = adj[u];

        while (temp != NULL) {
            int v = temp->dest;
            int newCost = dist[u] + temp->cost;

            if (newCost < dist[v]) {
                dist[v] = newCost;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }

            temp = temp->next;
        }
    }

    cout << "\nSource      : " << source;
    cout << "\nDestination : " << destination;

    if (dist[destination] == INF) {
        cout << "\nNo route available\n";
        return;
    }

    cout << "\nMinimum Cost: " << dist[destination];

    int path[MAX], count = 0;
    int current = destination;

    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    cout << "\nOptimal Route: ";

    for (int i = count - 1; i >= 0; i--) {
        cout << path[i];

        if (i > 0)
            cout << " -> ";
    }

    cout << endl;
}

int main() {
    int n, stages, routes;
    int source, destination;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter number of stages: ";
    cin >> stages;

    for (int i = 1; i <= n; i++)
        adj[i] = NULL;

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

    dijkstra(source, destination, n);

    return 0;
}
