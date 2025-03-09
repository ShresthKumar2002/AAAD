#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
typedef struct {
    int source, dest, weight;
} Edge;

// Structure to represent a subset for union-find
typedef struct {
    int parent;
    int rank;
} Subset;

// Function to compare edges based on their weights
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Find function for union-find
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Union function for union-find
void unionSets(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Function to implement Kruskal's algorithm
void kruskalMST(Edge edges[], int V, int E) {
    // Sort all edges in non-decreasing order of weight
    qsort(edges, E, sizeof(Edge), compareEdges);

    Subset subsets[V];
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    Edge result[V - 1];
    int edgeCount = 0, i = 0;

    while (edgeCount < V - 1 && i < E) {
        Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.source);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            result[edgeCount++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    int totalWeight = 0;
    for (int i = 0; i < edgeCount; i++) {
        printf("Edge: (%d, %d) -> Weight: %d\n", result[i].source, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total weight of MST: %d\n", totalWeight);
}

int main() {
    int V, E;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    Edge edges[E];
    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].source, &edges[i].dest, &edges[i].weight);
    }

    kruskalMST(edges, V, E);

    return 0;
}
