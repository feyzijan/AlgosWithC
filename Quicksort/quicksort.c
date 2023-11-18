#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int quickSortCalls = 0; // global var for calls

// struct for array items
typedef struct {
    double val1;
    double val2;
    double val3;
} item;


// Function to swap two items  - called in oarttion
void swap(item *a, item *b) {
    item temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array - called in quicksort
int partition(item arr[], int low, int high) {
    double pivot = arr[high].val2;  // last element is piivot
    int i = (low - 1);  // track correct position for pivot


    // find right position then swap 
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].val2 <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1); // pivots position
}


// Function to implement Recursive quicsort
void quickSort(item arr[], int low, int high) {
    quickSortCalls++; // global var increment
    if (low < high) {
        int pi = partition(arr, low, high); // pivot index
        quickSort(arr, low, pi - 1); // sort left
        quickSort(arr, pi + 1, high); // sort right
    }
}

int main(int argc, char *argv[]) {
    
    // open file
    char *inputFile = argv[1];
    FILE *file = fopen(inputFile, "r");

    // get size
    int n;
    fscanf(file, "%d", &n);

    // allocate memory and populate array
    item *items = malloc(n * sizeof(item));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf %lf %lf", &items[i].val1, &items[i].val2, &items[i].val3);
    }

    fclose(file);

    // Implement quicksort
    quickSort(items, 0, n-1);


    // Print sorted array based on arg 2 
    if (argc == 3 && strcmp(argv[2], "p") == 0) {
        for (int i = 0; i < n; i++) {
            printf("%.4f\t%.4f\t%.4f\n", items[i].val1, items[i].val2, items[i].val3);
        }
    }

    // Print quicksort calls
    printf("%d\n", quickSortCalls);

    // Free memory
    free(items);

    return 0;
}