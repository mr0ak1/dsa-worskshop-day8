 #include <stdio.h>
#include <stdlib.h>

#define MAX 100   

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

// Queue implementation for BFS
struct Queue {
    int items[MAX];
    int front, rear;
};

// Create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Enqueue an element
void enqueue(struct Queue* queue, int value) {
    if (queue->rear == MAX - 1)
        printf("\nQueue is full!\n");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// Dequeue an element
int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
        return item;
    }
}

// Function to perform BFS traversal from a given start vertex
void BFS(struct Graph* graph, int startVertex) {
    int visited[MAX] = {0};  // Array to keep track of visited vertices
    struct Queue* queue = createQueue();  // Create a queue for BFS

    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex
        struct AdjListNode* temp = graph->array[currentVertex].head;
        while (temp) {
            int adjVertex = temp->dest;

            // If the adjacent vertex has not been visited, mark it visited and enqueue it
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Main function to demonstrate graph operations with switch cases
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
        printf("3. Perform BFS\n");
        printf("4. Exit\n");
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
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
