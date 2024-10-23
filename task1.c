 #include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum number of vertices in the graph

// Structure to represent an adjacency list node
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure to represent a graph
struct Graph {
    int vertices;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* createNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = V;

    // Create an array of adjacency lists
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Function to add an edge to the graph (undirected graph)
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Add an edge from dest to src (since it's an undirected graph)
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to print the adjacency list representation of the graph
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->vertices; ++v) {
        struct AdjListNode* temp = graph->array[v].head;
        printf("\nVertex %d: ", v);
        while (temp) {
            printf("-> %d ", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function to perform BFS traversal from a given source
void BFS(struct Graph* graph, int startVertex) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex
        struct AdjListNode* temp = graph->array[currentVertex].head;
        while (temp) {
            int adjVertex = temp->dest;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Function to perform DFS traversal from a given source
void DFSUtil(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    // Recur for all adjacent vertices
    struct AdjListNode* temp = graph->array[vertex].head;
    while (temp) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int visited[MAX] = {0};
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");
}

// Main function to demonstrate all graph operations with switch cases
int main() {
    struct Graph* graph;
    int V, choice, src, dest, startVertex;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    graph = createGraph(V);

    while (1) {
        printf("\nGraph Operations Menu:\n");
        printf("1. Add Edge\n");
        printf("2. Display Graph\n");
        printf("3. Breadth-First Search (BFS)\n");
        printf("4. Depth-First Search (DFS)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source and destination vertices: ");
                scanf("%d %d", &src, &dest);
                if (src >= V || dest >= V) {
                    printf("Invalid vertices! Please enter vertices between 0 and %d.\n", V - 1);
                } else {
                    addEdge(graph, src, dest);
                }
                break;
            case 2:
                printf("Graph representation:\n");
                printGraph(graph);
                break;
            case 3:
                printf("Enter the starting vertex for BFS: ");
                scanf("%d", &startVertex);
                if (startVertex >= V) {
                    printf("Invalid vertex! Please enter a vertex between 0 and %d.\n", V - 1);
                } else {
                    BFS(graph, startVertex);
                }
                break;
            case 4:
                printf("Enter the starting vertex for DFS: ");
                scanf("%d", &startVertex);
                if (startVertex >= V) {
                    printf("Invalid vertex! Please enter a vertex between 0 and %d.\n", V - 1);
                } else {
                    DFS(graph, startVertex);
                }
                break;
            case 5:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
