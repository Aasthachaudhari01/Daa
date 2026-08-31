#include <iostream>
using namespace std;

#define MAX 100
#define INF 99999

int graph[MAX][MAX];
int dist[MAX];
bool visited[MAX];
int parent[MAX];
int n;

// Find node with minimum distance
int findMinNode()
{
    int min = INF;
    int node = -1;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && dist[i] < min)
        {
            min = dist[i];
            node = i;
        }
    }

    return node;
}

// Dijkstra's Algorithm
void dijkstra(int source)
{
    // Initialize
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[source] = 0;

    // Find shortest paths
    for (int i = 0; i < n - 1; i++)
    {
        int u = findMinNode();

        if (u == -1)
            break;

        visited[u] = true;

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] != 0 && !visited[v])
            {
                if (dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}

// Print shortest path
void printPath(int node)
{
    if (parent[node] == -1)
    {
        cout << node;
        return;
    }

    printPath(parent[node]);
    cout << " -> " << node;
}

int main()
{
    int source, destination;
    int edges;
    int u, v, weight;

    cout << "Smart City Emergency Route System\n";

    cout << "\nEnter number of intersections: ";
    cin >> n;

    // Initialize graph
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            graph[i][j] = 0;
        }
    }

    cout << "Enter number of roads: ";
    cin >> edges;

    cout << "\nEnter road details:\n";
    cout << "Format: source destination travel_time\n";

    for (int i = 0; i < edges; i++)
    {
        cin >> u >> v >> weight;

        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    cout << "\nEnter ambulance source node: ";
    cin >> source;

    cout << "Enter hospital destination node: ";
    cin >> destination;

    // Run Dijkstra
    dijkstra(source);

    // Display result
    if (dist[destination] == INF)
    {
        cout << "\nNo route available to the hospital.\n";
    }
    else
    {
        cout << "\nFastest Route:\n";
        printPath(destination);

        cout << "\nShortest Travel Time: "
             << dist[destination]
             << " minutes\n";
    }

    return 0;
}
