#ifndef PROJECT_INCLUDE_MATRIX_STRUCT_H_
#define PROJECT_INCLUDE_MATRIX_STRUCT_H_

#include <stddef.h>

typedef struct matrix {
    size_t rows;
    size_t cols;
    double *matrix;
} matrix_t;

enum errors {
    scanf_err = -1,
    null_pointer_err = 1,
    wrong_matrix_size_err,
    not_square_matrix_err
};

#endif  // PROJECT_INCLUDE_MATRIX_STRUCT_H_
