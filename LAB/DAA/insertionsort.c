#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n) {
    int i,j,k;
    for (i = 1; i < n; i++) {
        k = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > k) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = k;
    }
}

int main() {
    int n;
    printf("Enter the size: ");
    scanf("%d", &n);

    int arr[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
    clock_t start, end;
    start = clock();
    insertionSort(arr, n);
    end = clock();

    double tt = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Time taken: %f seconds\n", tt);

    return 0;
}
// sort given set of elements using insertion sort algorithm and find the time complexity for different values of n
//source code
//times new roman 12
//table
//graph
//best case worst case avg case table

