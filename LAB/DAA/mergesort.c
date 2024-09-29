#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[MAX_SIZE], R[MAX_SIZE];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    printf("Enter the size: ");
    scanf("%d", &n);

    if (n > MAX_SIZE) {
        printf("Size exceeds %d\n", MAX_SIZE);
        return 1;
    }

    int arr[MAX_SIZE];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }

    clock_t start, end;
    start = clock();
    mergeSort(arr, 0, n - 1);
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
