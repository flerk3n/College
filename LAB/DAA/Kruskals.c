#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define V 5
#define E 10

struct Edge {
    int src, dest, weight;
};

struct Graph {
    struct Edge edge[E];
};

int find(int parent[], int i) {
    if (parent[i] == i) return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
    else { parent[rootY] = rootX; rank[rootX]++; }
}

int compare(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void KruskalMST(struct Graph* graph) {
    struct Edge result[V - 1];
    int parent[V], rank[V] = {0}, e = 0, i = 0, totalWeight = 0;

    for (int v = 0; v < V; v++) parent[v] = v;
    qsort(graph->edge, E, sizeof(graph->edge[0]), compare);

    while (e < V - 1) {
        struct Edge next_edge = graph->edge[i++];
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);
        if (x != y) { result[e++] = next_edge; Union(parent, rank, x, y); 
        totalWeight += next_edge.weight;}
    }

    printf("Edge \tWeight\n");
    for (i = 0; i < e; i++) printf("%d - %d \t%d\n", result[i].src, result[i].dest, result[i].weight);
    printf("\nTotal weight of MST: %d\n", totalWeight); 
}

int main() {
    srand(time(0));
    struct Graph graph;

    for (int i = 0; i < E; i++) {
        graph.edge[i].src = rand() % V;
        graph.edge[i].dest = rand() % V;
        while (graph.edge[i].src == graph.edge[i].dest)
            graph.edge[i].dest = rand() % V;
        graph.edge[i].weight = rand() % 100 + 1;
    }

    printf("Graph generated (Edge List):\n");
    for (int i = 0; i < E; i++) printf("%d - %d \t%d\n", graph.edge[i].src, graph.edge[i].dest, graph.edge[i].weight);
    

    clock_t start = clock();
    KruskalMST(&graph);
    clock_t end = clock();
    
    printf("\nTime taken by Kruskal's algorithm: %f seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    

    return 0;
}
