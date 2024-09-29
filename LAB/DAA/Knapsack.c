#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *value;
int *weight;

int compare(const void* a, const void* b) {
    int i = *(int*)a;
    int j = *(int*)b;
    double r1 = (double)value[i] / weight[i];
    double r2 = (double)value[j] / weight[j];
    if (r1 > r2) return -1;
    if (r1 < r2) return 1;
    return 0;
}

double fractionalKnapsack(int W, int n, int value[], int weight[]) {
    int index[n];
    for (int i = 0; i < n; i++) {
        index[i] = i;
    }

    qsort(index, n, sizeof(int), compare);

    double total_value = 0.0;
    int current_weight = 0;

    for (int i = 0; i < n; i++) {
        int item = index[i];
        if (current_weight + weight[item] <= W) {
            current_weight += weight[item];
            total_value += value[item];
        } else {
            int remaining_capacity = W - current_weight;
            total_value += value[item] * ((double)remaining_capacity / weight[item]);
            break;
        }
    }

    return total_value;
}

int main() {
    int n, W;

    srand(time(0));

    printf("Enter the number of items: ");
    scanf("%d", &n);

    printf("Enter the maximum weight capacity of the knapsack: ");
    scanf("%d", &W);

    value = (int*)malloc(n * sizeof(int));
    weight = (int*)malloc(n * sizeof(int));

    printf("Generated random values and weights of the items:\n");
    for (int i = 0; i < n; i++) {
        value[i] = 100;
        weight[i] = rand() % 2000+1 ;
        //printf("Item %d - Value: %d, Weight: %d\n", i + 1, value[i], weight[i]);
    }

    clock_t start = clock();

    double max_value = fractionalKnapsack(W, n, value, weight);

    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("The maximum value that can be achieved is: %.2f\n", max_value);
    printf("Time taken to execute: %.6f seconds\n", time_taken);

    free(value);
    free(weight);

    return 0;
}
