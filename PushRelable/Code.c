#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define V 6 // Number of vertices in the graph

int min(int x, int y) {
    return (x < y) ? x : y;
}

// A function to push flow from u to v
void push(int u, int v, int capacity[V][V], int flow[V][V], int excess[], int height[]) {
    int send = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += send;
    flow[v][u] -= send;
    excess[u] -= send;
    excess[v] += send;
}

// A function to relabel vertex u
void relabel(int u, int capacity[V][V], int flow[V][V], int height[]) {
    int min_height = INT_MAX;
    for (int v = 0; v < V; v++) {
        if (capacity[u][v] - flow[u][v] > 0) {
            min_height = min(min_height, height[v]);
        }
    }
    if (min_height < INT_MAX) {
        height[u] = min_height + 1;
    }
}

// Initialize preflow
void initializePreflow(int source, int capacity[V][V], int flow[V][V], int excess[], int height[]) {
    memset(flow, 0, sizeof(int) * V * V);
    memset(excess, 0, sizeof(int) * V);
    memset(height, 0, sizeof(int) * V);

    height[source] = V;
    for (int v = 0; v < V; v++) {
        flow[source][v] = capacity[source][v];
        flow[v][source] = -capacity[source][v];
        excess[v] = capacity[source][v];
    }
}

// Main function to implement push-relabel algorithm
int pushRelabel(int capacity[V][V], int source, int sink) {
    int flow[V][V];
    int excess[V], height[V];

    initializePreflow(source, capacity, flow, excess, height);

    while (true) {
        bool pushed_or_relabelled = false;
        for (int u = 0; u < V; u++) {
            if (u != source && u != sink && excess[u] > 0) {
                for (int v = 0; v < V; v++) {
                    if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v]) {
                        push(u, v, capacity, flow, excess, height);
                        pushed_or_relabelled = true;
                    }
                }
                if (!pushed_or_relabelled) {
                    relabel(u, capacity, flow, height);
                    pushed_or_relabelled = true;
                }
            }
        }
        if (!pushed_or_relabelled) {
            break;
        }
    }

    int max_flow = 0;
    for (int v = 0; v < V; v++) {
        max_flow += flow[source][v];
    }
    return max_flow;
}

// Driver program to test above functions
int main() {
    int capacity[V][V] = {{0, 16, 13, 0, 0, 0},
                          {0, 0, 10, 12, 0, 0},
                          {0, 4, 0, 0, 14, 0},
                          {0, 0, 9, 0, 0, 20},
                          {0, 0, 0, 7, 0, 4},
                          {0, 0, 0, 0, 0, 0}};

    printf("The maximum possible flow is %d\n", pushRelabel(capacity, 0, 5));

    return 0;
}