 #include <stdio.h>
#include <limits.h>

#define MAX 100


int minDistance(int dist[], int visited[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int V) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}

// Function that implements Dijkstra's algorithm for a graph represented using an adjacency matrix
void dijkstra(int graph[MAX][MAX], int V, int src) {
    int dist[MAX];  // Array to hold the shortest distance from source to i
    int visited[MAX];  // visited[i] is true if vertex i is included in the shortest path tree

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited, V);

        // Mark the picked vertex as processed
        visited[u] = 1;

        // Update dist[] value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if it is not in visited, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the shortest distance array
    printSolution(dist, V);
}

int main() {
    int V, src;
    int graph[MAX][MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the adjacency matrix (use 0 for no edge):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, V, src);

    return 0;
}
