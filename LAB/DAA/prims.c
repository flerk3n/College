#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define V 5

int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMST(int parent[], int graph[V][V], int totalWeight) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    
    printf("\nTotal weight of MST: %d\n", totalWeight);  
}

void primMST(int graph[V][V]) {
    int parent[V], key[V], mstSet[V], totalWeight = 0; 
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    for (int i = 1; i < V; i++) 
        totalWeight += graph[i][parent[i]];  

    printMST(parent, graph, totalWeight);
}

int main() {
    srand(time(0));
    int graph[V][V];

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            int weight = rand() % 100 + 1;
            graph[i][j] = graph[j][i] = weight;
        }
    }

    for (int i = 0; i < V; i++)
        graph[i][i] = 0;

    printf("Graph generated (Adjacency Matrix):\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            printf("%d\t", graph[i][j]);
        printf("\n");
    }

    clock_t start = clock();
    primMST(graph);
    clock_t end = clock();

    printf("\nTime taken by Prim's algorithm: %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}
