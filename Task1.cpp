#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<char> removeDuplicates(const vector<char>& chars) {
    unordered_set<char> seen;
    vector<char> result;

    for (char c : chars) {
        // Only add characters to result if they haven't been seen before
        if (seen.insert(c).second) {
            result.push_back(c);
        }
    }

    return result;
}

int main() {
    vector<char> chars = {'a', 'b', 'a', 'c', 'b', 'd'};
    vector<char> noDuplicates = removeDuplicates(chars);

    // Print the result
    cout << "Original array: ";
    for (char c : chars) {
        cout << c << " ";
    }
    cout << "\nArray without duplicates: ";
    for (char c : noDuplicates) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}

