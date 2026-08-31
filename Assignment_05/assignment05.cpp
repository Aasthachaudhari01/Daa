#include <iostream>
using namespace std;

#define MAX 100
#define INF 99999

int graph[MAX][MAX];
int stage[MAX];
int cost[MAX];
int nextNode[MAX];

int main()
{
    int n, stages, edges;
    int source, destination;


    // Number of nodes
    cout << "\nEnter number of nodes: ";
    cin >> n;

    // Number of stages
    cout << "Enter number of stages: ";
    cin >> stages;

    // Stage of each node
    cout << "\nEnter stage number for each node:\n";

    for (int i = 1; i <= n; i++)
    {
        cout << "Enter stage of node " << i << ": ";
        cin >> stage[i];
    }

    // Initialize graph
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            graph[i][j] = 0;
        }
    }

    // Number of routes
    cout << "\nEnter number of routes: ";
    cin >> edges;

    // Routes
    cout << "\nEnter route details:\n";
    cout << "Format: Source Destination Cost\n";

    for (int i = 0; i < edges; i++)
    {
        int u, v, w;

        cout << "Route " << i + 1 << ": ";
        cin >> u >> v >> w;

        graph[u][v] = w;
    }

    // Source and destination
    cout << "\nEnter source node: ";
    cin >> source;

    cout << "Enter destination node: ";
    cin >> destination;

    // Initialize cost and next node
    for (int i = 1; i <= n; i++)
    {
        cost[i] = INF;
        nextNode[i] = -1;
    }

    // Destination cost is 0
    cost[destination] = 0;

    // Dynamic Programming
    // Process stages from last to first
    for (int s = stages - 1; s >= 1; s--)
    {
        for (int u = 1; u <= n; u++)
        {
            if (stage[u] == s)
            {
                for (int v = 1; v <= n; v++)
                {
                    if (graph[u][v] != 0)
                    {
                        if (graph[u][v] + cost[v] < cost[u])
                        {
                            cost[u] = graph[u][v] + cost[v];
                            nextNode[u] = v;
                        }
                    }
                }
            }
        }
    }

    // Display result
    if (cost[source] == INF)
    {
        cout << "\nNo route exists from "
             << source << " to "
             << destination << ".\n";
    }
    else
    {

        cout << "Source      : " << source << endl;
        cout << "Destination : " << destination << endl;
        cout << "Minimum Cost: " << cost[source] << endl;

        cout << "Optimal Route: ";

        int current = source;

        while (current != -1)
        {
            cout << current;

            if (current == destination)
                break;

            cout << " -> ";
            current = nextNode[current];
        }

    }

    return 0;
}
