#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the adjacency list
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    // Create an array of adjacency lists
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    // Initialize each adjacency list as empty by making each head pointer as NULL
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src also
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Breadth-First Search (BFS) function
void bfs(struct Graph* graph, int startVertex) {
    // Create a queue for BFS
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    // Mark the current node as visited and enqueue it
    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("Breadth First Traversal starting from vertex %d: ", startVertex);

    while (front < rear) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex currentVertex
        // If an adjacent vertex has not been visited, mark it as visited and enqueue it
        struct Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Depth-First Search (DFS) function
void dfs(struct Graph* graph, int startVertex) {
    // Mark the current vertex as visited and print it
    graph->visited[startVertex] = 1;
    printf("%d ", startVertex);

    // Recur for all the vertices adjacent to this vertex
    struct Node* temp = graph->adjLists[startVertex];
    while (temp) {
        int adjVertex = temp->data;
        if (graph->visited[adjVertex] == 0) {
            dfs(graph, adjVertex);
        }
        temp = temp->next;
    }
}

int main() {
    int vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    struct Graph* graph = createGraph(vertices);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    // Perform BFS
    bfs(graph, 0);

    // Reset visited array for DFS
    for (int i = 0; i < vertices; i++) {
        graph->visited[i] = 0;
    }

    // Perform DFS
    printf("Depth First Traversal starting from vertex 0: ");
    dfs(graph, 0);
    printf("\n");

    return 0;
}
