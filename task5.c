 #include <stdio.h>
#include <stdlib.h>

// Function to perform Linear Search
int linearSearch(int arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return i; // Return the index where the element is found
        }
    }
    return -1; // Return -1 if element is not found
}

// Function to perform Binary Search (requires sorted array)
int binarySearch(int arr[], int low, int high, int x) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            return mid; // Element is present at mid
        } else if (arr[mid] < x) {
            low = mid + 1; // Search the right half
        } else {
            high = mid - 1; // Search the left half
        }
    }
    return -1; // Element is not found
}

// Function to sort the array (needed for Binary Search)
void sortArray(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Main function with switch-case for search operations
int main() {
    int n, choice, x, result;
    int arr[100];

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    while (1) {
        printf("\nSearch Operations Menu:\n");
        printf("1. Linear Search\n");
        printf("2. Binary Search\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to search: ");
                scanf("%d", &x);
                result = linearSearch(arr, n, x);
                if (result != -1) {
                    printf("Element found at index %d\n", result);
                } else {
                    printf("Element not found\n");
                }
                break;

            case 2:
                // Sort the array for Binary Search
                sortArray(arr, n);
                printf("Sorted array: ");
                printArray(arr, n);

                printf("Enter the element to search: ");
                scanf("%d", &x);
                result = binarySearch(arr, 0, n - 1, x);
                if (result != -1) {
                    printf("Element found at index %d\n", result);
                } else {
                    printf("Element not found\n");
                }
                break;

            case 3:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
