#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int heapify(int arr[], int n, int i) {
    int count = 0;
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
        count++;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
        count++;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        count += heapify(arr, n, largest);
    }
    return count;
}

int heap_sort_count(int arr[], int n) {
    int totalComparisons = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        totalComparisons += heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        totalComparisons += heapify(arr, i, 0);
    }
    return totalComparisons;
}

int bubble_sort_count(int arr[], int n) {
    int totalComparisons = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            totalComparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    return totalComparisons;
}

int selection_sort_count(int arr[], int n) {
    int totalComparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            totalComparisons++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[min_idx], arr[i]);
    }
    return totalComparisons;
}

int insertion_sort_count(int arr[], int n) {
    int totalComparisons = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            totalComparisons++;
        }
        arr[j + 1] = key;
    }
    return totalComparisons;
}

void test_comparisons() {
    const int numTests = 30;
    srand(time(NULL)); // Seed random number generator

    for (int size = 1; size <= numTests; ++size) {
        vector<int> testArray(size);
        // Fill array with random numbers
        generate(testArray.begin(), testArray.end(), rand);

        vector<int> original = testArray; // Copy to keep original data for each sort

        cout << "Testing size: " << size << endl;

        // Heap Sort Test
        auto start = chrono::high_resolution_clock::now();
        int comparisons = heap_sort_count(&testArray[0], size);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        cout << "Heap Sort comparisons: " << comparisons << ", time: " << elapsed_seconds.count() << " s" << endl;

        // Bubble Sort Test
        testArray = original;
        start = chrono::high_resolution_clock::now();
        comparisons = bubble_sort_count(&testArray[0], size);
        end = chrono::high_resolution_clock::now();
        elapsed_seconds = end - start;
        cout << "Bubble Sort comparisons: " << comparisons << ", time: " << elapsed_seconds.count() << " s" << endl;

        // Selection Sort Test
        testArray = original;
        start = chrono::high_resolution_clock::now();
        comparisons = selection_sort_count(&testArray[0], size);
        end = chrono::high_resolution_clock::now();
        elapsed_seconds = end - start;
        cout << "Selection Sort comparisons: " << comparisons << ", time: " << elapsed_seconds.count() << " s" << endl;

        // Insertion Sort Test
        testArray = original;
        start = chrono::high_resolution_clock::now();
        comparisons = insertion_sort_count(&testArray[0], size);
        end = chrono::high_resolution_clock::now();
        elapsed_seconds = end - start;
        cout << "Insertion Sort comparisons: " << comparisons << ", time: " << elapsed_seconds.count() << " s" << endl;
    }
}

int main() {
    test_comparisons(); // Call the test function

    return 0;
}



