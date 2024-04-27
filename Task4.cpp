#include <iostream>
#include <vector>

using namespace std;

void partitionAroundK(vector<int>& arr, int low, int high, int k, int& compCount) {
    if (low >= high) return; // Base case to stop recursion

    int pivot = arr[high]; // Use the last element as the pivot
    int i = low - 1;       // Index for the smaller element
    for (int j = low; j < high; j++) {
        compCount++;       // Increment comparison count
        if (arr[j] <= k) { // We use k as the partitioning element
            i++;           // Increment index of smaller element
            swap(arr[i], arr[j]); // Swap if element is less than or equal to k
        }
    }
    swap(arr[i + 1], arr[high]); // Swap the pivot to its correct position

    // Recursively sort elements before partition and after partition
    partitionAroundK(arr, low, i, k, compCount);
    partitionAroundK(arr, i + 2, high, k, compCount); // i + 1 is the pivot
}

void rearrangeArray(vector<int>& arr, int k) {
    int compCount = 0; // Counter for comparisons
    partitionAroundK(arr, 0, arr.size() - 1, k, compCount);
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5, 4, 12};
    int k = 6;
    cout << "Original array: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    rearrangeArray(arr, k);

    cout << "Rearranged array around " << k << ": ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}





