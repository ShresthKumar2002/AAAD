#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define U 3 // Number of vertices in the first set (left side)
#define V 3 // Number of vertices in the second set (right side)
#define TOTAL (U + V + 2) // Total vertices including source and sink

#define SOURCE (U + V) // Index of source vertex
#define SINK (U + V + 1) // Index of sink vertex

// Queue implementation
struct Queue {
    int items[TOTAL];
    int front, rear;
};

void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(struct Queue* q) {
    return q->rear == -1;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == TOTAL - 1)
        return;
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(struct Queue* q) {
    int item;
    if (isEmpty(q)) {
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
        return item;
    }
}

// BFS function to check for paths in the residual graph
int bfs(int rGraph[TOTAL][TOTAL], int s, int t, int parent[]) {
    bool visited[TOTAL];
    memset(visited, 0, sizeof(visited));

    struct Queue q;
    initQueue(&q);
    enqueue(&q, s);
    visited[s] = true;
    parent[s] = -1;

    while (!isEmpty(&q)) {
        int u = dequeue(&q);

        for (int v = 0; v < TOTAL; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return 1;
                }
                enqueue(&q, v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return 0;
}

// Edmonds-Karp implementation for maximum flow
int edmondsKarp(int graph[TOTAL][TOTAL], int s, int t) {
    int u, v;

    // Create residual graph
    int rGraph[TOTAL][TOTAL];
    for (u = 0; u < TOTAL; u++)
        for (v = 0; v < TOTAL; v++)
            rGraph[u][v] = graph[u][v];

    int parent[TOTAL];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = (path_flow < rGraph[u][v]) ? path_flow : rGraph[u][v];
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

// Main function to set up the bipartite graph
int main() {
    // Bipartite graph with source and sink
    int graph[TOTAL][TOTAL] = {0};

    // Connect source to all vertices in the first set (U)
    for (int i = 0; i < U; i++) {
        graph[SOURCE][i] = 1;
    }

    // Connect all vertices in the second set (V) to sink
    for (int i = 0; i < V; i++) {
        graph[U + i][SINK] = 1;
    }

    // Add edges between U and V
    // Example: U0 -> V0, U0 -> V1, U1 -> V1, U2 -> V2
    graph[0][U] = 1;
    graph[0][U + 1] = 1;
    graph[1][U + 1] = 1;
    graph[2][U + 2] = 1;

    // Compute and print maximum bipartite matching
    printf("The maximum bipartite matching is %d\n", edmondsKarp(graph, SOURCE, SINK));

    return 0;
}
