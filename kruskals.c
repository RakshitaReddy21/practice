#include <stdio.h>
#include <stdlib.h>

// Structure to represent a weighted edge
typedef struct {
    int src, dest, weight;
} Edge;

// Structure to represent a subset for union-find
typedef struct {
    int parent, rank;
} Subset;

// Function prototypes
int find(Subset subsets[], int i);
void unionSets(Subset subsets[], int x, int y);
int compareEdges(const void *a, const void *b);
void kruskal(Edge edges[], int V, int E);

int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges

    Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskal(edges, V, E);

    return 0;
}

// Function to find the subset of an element
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to do union of two subsets
void unionSets(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Function to compare two edges (used for qsort)
int compareEdges(const void *a, const void *b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Function to implement Kruskal's algorithm
void kruskal(Edge edges[], int V, int E) {
    Edge result[V];  // Resultant MST
    int e = 0;       // Count of edges in MST
    int i = 0;       // Initial index of sorted edges
    Subset subsets[V];

    // Initialize subsets
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Sort edges in increasing order of weights
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    // Iterate through sorted edges and build the MST
    while (e < V - 1) {
        Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause a cycle
        if (x != y) {
            result[e++] = next_edge;
            unionSets(subsets, x, y);
        }
    }

    // Print the MST
    printf("Edges in the Minimum Spanning Tree:\n");
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost of Spanning Tree: %d\n", minimumCost);
}

