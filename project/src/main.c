#include <stdio.h>
#include "matrix.h"
#include "matrix_struct.h"

void print_matrix(const matrix_t* matrix) {
    if (matrix == NULL) {
        return;
    }
    for (int i = 0; i < (int)matrix->rows; i++) {
        for (int j = 0; j < (int)matrix->cols; j++) {
            printf("%f ", matrix->matrix[i*(matrix->cols) + j]);
        }
    }
    printf("\n");
}

int main(void) {
    // matrix_t *first = create_matrix(1, 1);
    // first->matrix[0] = -100;
    // matrix_t *adj = adj(first);
    // print_matrix(adj);
    // double determinant = 0;
    // det(first, &determinant);
    // printf("%f\n", determinant);
    // matrix_t *inv_matrix = mul_scalar(adj, 1 / determinant);
    // print_matrix(inv_matrix);
    // matrix_t *my_inv = inv(first);
    // print_matrix(my_inv);

    matrix_t *matrix_from_file = create_matrix_from_file( \
    "project/tests/data/test_matrix_inverse/case_1/in.txt");
    print_matrix(matrix_from_file);
    matrix_t *inv_matrix_file = inv(matrix_from_file);
    print_matrix(inv_matrix_file);
    free_matrix(matrix_from_file);
    free_matrix(inv_matrix_file);

    matrix_t *mul_scalar_test = create_matrix(1, 1);
    mul_scalar_test->matrix[0] = -100;
    matrix_t *mul_scalar_res = mul_scalar(mul_scalar_test, 2);
    print_matrix(mul_scalar_res);
    free_matrix(mul_scalar_test);
    free_matrix(mul_scalar_res);
    return 0;
}
