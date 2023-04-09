#include "CCS.cpp"

void testSparseMatrix() {
    // Test case for a square matrix
    double values[] = {1.0, 2.0, 3.0, 4.0};
    int row_indices[] = {0, 2, 0, 1};
    int column_indices[] = {0, 2, 3, 4};
    SparseMatrix matrix(2, values, row_indices, column_indices);

    SparseMatrix transposed_matrix = matrix.transpose();

    // The transposed matrix should have the same values as the original matrix
    assert(transposed_matrix.size == 2);
    assert(transposed_matrix.column_indices[0] == 0);
    assert(transposed_matrix.column_indices[1] == 2);
    assert(transposed_matrix.column_indices[2] == 4);
    assert(transposed_matrix.values[0] == 1.0);
    assert(transposed_matrix.values[1] == 3.0);
    assert(transposed_matrix.values[2] == 2.0);
    assert(transposed_matrix.values[3] == 4.0);
    assert(transposed_matrix.row_indices[0] == 0);
    assert(transposed_matrix.row_indices[1] == 2);
    assert(transposed_matrix.row_indices[2] == 0);
    assert(transposed_matrix.row_indices[3] == 1);

    // Test case for a non-square matrix
    double values2[] = {1.0, 2.0, 3.0, 4.0};
    int row_indices2[] = {0, 2, 0, 1};
    int column_indices2[] = {0, 2, 4};
    SparseMatrix matrix2(2, values2, row_indices2, column_indices2);

    SparseMatrix transposed_matrix2 = matrix2.transpose();

    // The transposed matrix should have the same values as the original matrix
    assert(transposed_matrix2.size == 2);
    assert(transposed_matrix2.column_indices[0] == 0);
    assert(transposed_matrix2.column_indices[1] == 2);
    assert(transposed_matrix2.column_indices[2] == 4);
    assert(transposed_matrix2.values[0] == 1.0);
    assert(transposed_matrix2.values[1] == 3.0);
    assert(transposed_matrix2.values[2] == 2.0);
    assert(transposed_matrix2.values[3] == 4.0);
    assert(transposed_matrix2.row_indices[0] == 0);
    assert(transposed_matrix2.row_indices[1] == 2);
    assert(transposed_matrix2.row_indices[2] == 0);
    assert(transposed_matrix2.row_indices[3] == 1);
}

int main() {
    testSparseMatrix();

    return 0;
}
