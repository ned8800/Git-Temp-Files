#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>
#include "matrix_struct.h"

// Init/release operations
matrix_t* create_matrix_from_file(const char* path_file);
matrix_t* create_matrix(size_t rows, size_t cols);
void free_matrix(matrix_t* matrix);

// Basic operations
int get_rows(const matrix_t* matrix, size_t* rows);
int get_cols(const matrix_t* matrix, size_t* cols);
int get_elem(const matrix_t* matrix, size_t row, size_t col, double* val);
int set_elem(matrix_t* matrix, size_t row, size_t col, double val);

// Math operations
matrix_t* mul_scalar(const matrix_t* matrix, double val);
matrix_t* transp(const matrix_t* matrix);

matrix_t* sum(const matrix_t* first, const matrix_t* second);
matrix_t* sub(const matrix_t* first, const matrix_t* second);
matrix_t* mul(const matrix_t* first, const matrix_t* second);

// Extra operations
int det(const matrix_t* matrix, double* val);
matrix_t* adj(const matrix_t* matrix);
matrix_t* inv(const matrix_t* matrix);

#endif  // PROJECT_INCLUDE_MATRIX_H_
