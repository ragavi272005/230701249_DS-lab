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

    // Initialize each adjacency list as empty by making each head pointer as NULL
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
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

// Function to perform topological sorting
void topologicalSortUtil(int v, struct Graph* graph, int visited[], struct Node** stack) {
    visited[v] = 1;

    struct Node* temp = graph->adjLists[v];
    while (temp) {
        int adjVertex = temp->data;
        if (!visited[adjVertex]) {
            topologicalSortUtil(adjVertex, graph, visited, stack);
        }
        temp = temp->next;
    }

    // Push the current vertex to the stack
    struct Node* newNode = createNode(v);
    newNode->next = *stack;
    *stack = newNode;
}

void topologicalSort(struct Graph* graph) {
    int visited[MAX_VERTICES] = {0};
    struct Node* stack = NULL;

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, graph, visited, &stack);
        }
    }

    // Print the contents of the stack
    printf("Ordering of vertices using topological sorting: ");
    while (stack) {
        printf("%d ", stack->data);
        struct Node* temp = stack;
        stack = stack->next;
        free(temp);
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

    topologicalSort(graph);

    return 0;
}
