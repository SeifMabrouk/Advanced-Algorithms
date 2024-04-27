#include <iostream>
#include <vector>
#include <pthread.h>

using namespace std;

struct Matrix {
    int rows;
    int cols;
    vector<vector<int>> data;

    Matrix(int r, int c) : rows(r), cols(c), data(r, vector<int>(c, 0)) {}
};

struct ThreadParam {
    int rowStart;
    int rowEnd;
    const Matrix* A;
    const Matrix* B;
    Matrix* result;
};

void* multiplyRows(void* arg) {
    ThreadParam* params = (ThreadParam*)arg;
    const Matrix* A = params->A;
    const Matrix* B = params->B;
    Matrix* result = params->result;
    int rowStart = params->rowStart;
    int rowEnd = params->rowEnd;

    for (int i = rowStart; i <= rowEnd; ++i) {
        for (int j = 0; j < B->cols; ++j) {
            result->data[i][j] = 0;
            for (int k = 0; k < A->cols; ++k) {
                result->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }
    return nullptr;
}

int main() {
    int rowA = 3, colA = 2, rowB = 2, colB = 3;
    Matrix A(rowA, colA);
    Matrix B(rowB, colB);
    Matrix result(rowA, colB);

    // Initialize matrices A and B
    A.data = {{1, 4}, {2, 5}, {3, 6}};
    B.data = {{8, 7, 6}, {5, 4, 3}};

    int numThreads = rowA;
    vector<pthread_t> threads(numThreads);
    vector <ThreadParam> threadParams(numThreads);

    // Create and launch threads for each row of the result matrix
    for (int i = 0; i < numThreads; ++i) {
        threadParams[i].rowStart = i;
        threadParams[i].rowEnd = i;  // Each thread handles one row
        threadParams[i].A = &A;
        threadParams[i].B = &B;
        threadParams[i].result = &result;

        pthread_create(&threads[i], nullptr, multiplyRows, &threadParams[i]);
    }

    // Wait for all threads to complete their tasks
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // Printing the resulting matrix
    cout << "Resulting Matrix: " << endl;
    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.cols; ++j) {
            cout << result.data[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

