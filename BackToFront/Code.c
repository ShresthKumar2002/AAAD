#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define V 6 // Number of vertices in the graph

int min(int x, int y) {
    return (x < y) ? x : y;
}

void push(int u, int v, int capacity[V][V], int flow[V][V], int excess[], int height[]) {
    int send = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += send;
    flow[v][u] -= send;
    excess[u] -= send;
    excess[v] += send;
}

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

void discharge(int u, int capacity[V][V], int flow[V][V], int excess[], int height[], int list[], int *list_size) {
    while (excess[u] > 0) {
        for (int v = 0; v < V; v++) {
            if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1) {
                push(u, v, capacity, flow, excess, height);
                if (excess[v] > 0 && v != 0 && v != V-1) {
                    // Move v to the front of the list
                    for (int i = 0; i < *list_size; i++) {
                        if (list[i] == v) {
                            for (int j = i; j > 0; j--) {
                                list[j] = list[j-1];
                            }
                            list[0] = v;
                            break;
                        }
                    }
                }
                break;
            }
        }
        if (excess[u] > 0) {
            relabel(u, capacity, flow, height);
        }
    }
}

int relabelToFront(int capacity[V][V], int source, int sink) {
    int flow[V][V];
    int excess[V], height[V], list[V-2];
    int list_size = 0;

    memset(flow, 0, sizeof(flow));
    memset(excess, 0, sizeof(excess));
    memset(height, 0, sizeof(height));

    for (int i = 1; i < V-1; i++) {
        list[list_size++] = i;
    }

    height[source] = V;
    for (int v = 0; v < V; v++) {
        if (capacity[source][v] > 0) {
            flow[source][v] = capacity[source][v];
            flow[v][source] = -capacity[source][v];
            excess[v] = capacity[source][v];
            excess[source] -= capacity[source][v];
        }
    }

    int p = 0;
    while (p < list_size) {
        int u = list[p];
        int old_height = height[u];
        discharge(u, capacity, flow, excess, height, list, &list_size);
        if (height[u] > old_height) {
            int temp = list[p];
            for (int i = p; i > 0; i--) {
                list[i] = list[i-1];
            }
            list[0] = temp;
            p = 0;
        } else {
            p++;
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

    printf("The maximum possible flow is %d\n", relabelToFront(capacity, 0, 5));

    return 0;
}