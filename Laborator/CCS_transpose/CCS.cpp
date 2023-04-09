#include <iostream>

using namespace std;

class SparseMatrix {

public:
    SparseMatrix(int size, double* values, int* row_indices, int* column_indices) :
            size(size),
            values(new double[column_indices[size]]),
            row_indices(new int[column_indices[size]]),
            column_indices(new int[size + 1]) {
        for (int i = 0; i < column_indices[size]; i++) {
            this->values[i] = values[i];
            this->row_indices[i] = row_indices[i];
        }
        for (int i = 0; i < size + 1; i++) {
            this->column_indices[i] = column_indices[i];
        }
    }

    SparseMatrix transpose() const {
        int num_rows = this->size;
        int num_cols = this->column_indices[size];

        double* transposed_values = new double[this->values.size()];
        int* transposed_row_indices = new int[this->values.size()];
        int* transposed_column_indices = new int[num_rows + 1];
        for (int i = 0; i < num_rows + 1; i++) {
            transposed_column_indices[i] = 0;
        }

        // Compute the number of non-zero elements in each column of the original matrix
        int* col_count = new int[num_cols];
        for (int i = 0; i < num_cols; i++) {
            col_count[i] = 0;
        }
        for (int i = 0; i < this->column_indices[size]; i++) {
            col_count[this->column_indices[i]]++;
        }

        // Compute the starting position of each column in the transposed matrix
        for (int i = 1; i <= num_rows; i++) {
            transposed_column_indices[i] = transposed_column_indices[i - 1] + col_count[i - 1];
        }

        // Compute the transposed matrix
        for (int i = 0; i < num_cols; i++) {
            for (int j = this->column_indices[i]; j < this->column_indices[i + 1]; j++) {
                int row = this->row_indices[j];
                int dest = transposed_column_indices[row];

                transposed_values[dest] = this->values[j];
                transposed_row_indices[dest] = i;
                transposed_column_indices[row]++;
            }
        }

        SparseMatrix transposed_matrix(num_cols, transposed_values, transposed_row_indices, transposed_column_indices);

        delete[] col_count;
        delete[] transposed_values;
        delete[] transposed_row_indices;
        delete[] transposed_column_indices;

        return transposed_matrix;
    }

    ~SparseMatrix() {
        delete[] values;
        delete[] row_indices;
        delete[] column_indices;
    }

    int size;
    int* column_indices;
    double* values;
    int* row_indices;
};
