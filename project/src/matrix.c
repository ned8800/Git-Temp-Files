#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrix_struct.h"

static double add_double(double a, double b) {
    return a + b;
}

static double subtract_double(double a, double b) {
    return a - b;
}

static matrix_t* math_operation_with_matrix(\
const matrix_t* first, const matrix_t* second, double (*operation_func)(double, double)) {
    if (first == NULL || second == NULL || \
    first->rows != second->rows || first->cols != second->cols) {
        return NULL;
    }
    matrix_t *new_matrix_struct = create_matrix(first->rows, first->cols);
    if (new_matrix_struct == NULL) {
        return NULL;
    }
    for (int i = 0; i < (int)new_matrix_struct->rows; i++) {
        for (int j = 0; j < (int)new_matrix_struct->cols; j++) {
            new_matrix_struct->matrix[i*(first->cols)+j] = \
            operation_func(first->matrix[i*(first->cols)+j], second->matrix[i*(first->cols)+j]);
        }
    }
    return new_matrix_struct;
}

matrix_t* create_matrix_from_file(const char* path_file) {
    FILE *stream = fopen(path_file, "r");
    if (stream == NULL) {
        return NULL;
    }
    size_t rows = 0;
    size_t cols = 0;
    int success_read_args = fscanf(stream, "%zu %zu\n", &rows, &cols);
    if (success_read_args != 2 || rows == 0 || cols == 0) {
        fclose(stream);
        return NULL;
    }
    matrix_t *new_matrix_struct = malloc(sizeof(matrix_t));
    if (new_matrix_struct == NULL) {
        fclose(stream);
        return NULL;
    }
    new_matrix_struct->rows = rows;
    new_matrix_struct->cols = cols;
    double *new_matrix = (double *)malloc(rows*cols*sizeof(double));
    for (int i = 0; i < (int)new_matrix_struct->rows; i++) {
        for (int j = 0; j < (int)new_matrix_struct->cols; j++) {
            if (fscanf(stream, "%lf\n", &new_matrix[i*cols+j]) == scanf_err) {
                free(new_matrix);
                free(new_matrix_struct);
                fclose(stream);
                return NULL;
            }
        }
    }
    new_matrix_struct->matrix = new_matrix;
    fclose(stream);
    return new_matrix_struct;
}

matrix_t* create_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }
    matrix_t *new_matrix_struct = malloc(sizeof(matrix_t));
    if (new_matrix_struct == NULL) {
        return NULL;
    }
    new_matrix_struct->rows = rows;
    new_matrix_struct->cols = cols;
    double *new_matrix = (double *)malloc(rows*cols*sizeof(double));
    for (int i = 0; i < (int)rows; i++) {
        for (int j = 0; j < (int)cols; j++) {
            new_matrix[i*cols+j] = 0;
        }
    }
    new_matrix_struct->matrix = new_matrix;
    return new_matrix_struct;
}

void free_matrix(matrix_t* matrix) {
    if (matrix != NULL) {
        free(matrix->matrix);
        free(matrix);
    }
}

int get_rows(const matrix_t* matrix, size_t* rows) {
    if (matrix == NULL) {
        return null_pointer_err;
    }
    *rows = matrix->rows;
    return 0;
}

int get_cols(const matrix_t* matrix, size_t* cols) {
    if (matrix == NULL) {
        return null_pointer_err;
    }
    *cols = matrix->cols;
    return 0;
}

int get_elem(const matrix_t* matrix, size_t row, size_t col, double* val) {
    if (matrix == NULL) {
        return null_pointer_err;
    }
    if (row >= matrix->rows || col >= matrix->cols) {
        return wrong_matrix_size_err;
    }
    *val = matrix->matrix[row*(matrix->cols)+col];
    return 0;
}

int set_elem(matrix_t* matrix, size_t row, size_t col, double val) {
    if (matrix == NULL) {
        return null_pointer_err;
    }
    if (row >= matrix->rows || col >= matrix->cols) {
        return wrong_matrix_size_err;
    }
    matrix->matrix[row*(matrix->cols)+col] = val;
    return 0;
}

matrix_t* mul_scalar(const matrix_t* matrix, double val) {
    if (matrix == NULL) {
        return NULL;
    }
    matrix_t *new_matrix_struct = create_matrix(matrix->rows, matrix->cols);
    if (new_matrix_struct == NULL) {
        return NULL;
    }
    if (new_matrix_struct->rows == 1 && new_matrix_struct->cols == 1) {
        new_matrix_struct->matrix[0] = matrix->matrix[0] * val;
    } else {  // почему-то make check не проходит для матрицы 1 на 1 без этой конструкции
        for (int i = 0; i < (int)new_matrix_struct->rows; i++) {
            for (int j = 0; j < (int)new_matrix_struct->cols; j++) {
                new_matrix_struct->matrix[i*(matrix->cols)+j] = matrix->matrix[i*(matrix->cols)+j] * val;
            }
        }
    }
    return new_matrix_struct;
}

matrix_t* transp(const matrix_t* matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    matrix_t *new_matrix_struct = create_matrix(matrix->cols, matrix->rows);
    if (new_matrix_struct == NULL) {
        return NULL;
    }
    for (int i = 0; i < (int)new_matrix_struct->rows; i++) {
        for (int j = 0; j < (int)new_matrix_struct->cols; j++) {
            new_matrix_struct->matrix[i*(matrix->rows)+j] = matrix->matrix[j*(matrix->cols)+i];
        }
    }
    return new_matrix_struct;
}

matrix_t* sum(const matrix_t* first, const matrix_t* second) {
    return math_operation_with_matrix(first, second, add_double);
}

matrix_t* sub(const matrix_t* first, const matrix_t* second) {
    return math_operation_with_matrix(first, second, subtract_double);
}

matrix_t* mul(const matrix_t* first, const matrix_t* second) {
    if (first == NULL || second == NULL) {
        return NULL;
    }
    matrix_t *new_matrix_struct = create_matrix(first->rows, second->cols);
    if (new_matrix_struct == NULL) {
        return NULL;
    }
    for (int i = 0; i < (int)new_matrix_struct->rows; i++) {
        for (int j = 0; j < (int)new_matrix_struct->cols; j++) {
            for (int k = 0; k < (int)first->cols; k++) {
                new_matrix_struct->matrix[i*(new_matrix_struct->cols)+j] += \
                first->matrix[i*(first->cols)+k] * second->matrix[k*(second->cols)+j];
            }
        }
    }
    return new_matrix_struct;
}

static matrix_t* get_cropped_matrix(const matrix_t* matrix, size_t row, size_t col) {
    if (matrix == NULL || matrix->rows == 1 || matrix->cols == 1) {
        return NULL;
    }
    matrix_t *new_matrix_struct = create_matrix(matrix->rows - 1, matrix->cols - 1);
    if (new_matrix_struct == NULL) {
        return NULL;
    }
    size_t original_row = 0;
    size_t original_col = 0;
    for (int i = 0; i < (int)new_matrix_struct->rows; i++) {
        if (i == (int)row) {
            original_row++;
        }
        for (int j = 0; j < (int)new_matrix_struct->cols; j++) {
            if (j == (int)col) {
                original_col++;
            }
            new_matrix_struct->matrix[i*(new_matrix_struct->cols)+j] = \
            matrix->matrix[original_row*(matrix->cols)+original_col];
            original_col++;
        }
        original_row++;
        original_col = 0;
    }
    return new_matrix_struct;
}

static double get_matrix_det(const matrix_t* matrix, size_t size) {
    if (matrix == NULL) {
        return null_pointer_err;
    }
    double determinant = 0;
    int coef = 1;
    if (size == 1) {
        return matrix->matrix[0];
    } else if (size == 2) {
        return matrix->matrix[0] * matrix->matrix[3] - \
        matrix->matrix[1] * matrix->matrix[2];
    } else {
        for (int col = 0; col < (int)size; col++) {
            matrix_t *new_matrix_struct = get_cropped_matrix(matrix, 0, col);
            determinant += (coef * matrix->matrix[col] * get_matrix_det(new_matrix_struct, size-1));
            coef = -coef;
            free_matrix(new_matrix_struct);
        }
    }
    return determinant;
}

int det(const matrix_t* matrix, double* val) {
    if (matrix == NULL) {
        return null_pointer_err;
    }
    if (matrix->rows != matrix->cols) {
        return not_square_matrix_err;
    }
    *val = get_matrix_det(matrix, matrix->rows);
    return 0;
}

matrix_t* adj(const matrix_t* matrix) {
    if (matrix == NULL || matrix->rows != matrix->cols) {
        return NULL;
    }
    matrix_t *new_matrix_struct = create_matrix(matrix->rows, matrix->cols);
    if (new_matrix_struct == NULL) {
        return NULL;
    }
    if (matrix->rows == 1) {
        new_matrix_struct->matrix[0] = 1.0;
        return new_matrix_struct;
    }
    double algebraic_complement;
    for (size_t i = 0; i < new_matrix_struct->rows; i++) {
        for (size_t j = 0; j < new_matrix_struct->cols; j++) {
            matrix_t* temp_matrix_for_crop = get_cropped_matrix(matrix, i, j);
            if (temp_matrix_for_crop == NULL) {
                free_matrix(new_matrix_struct);
                return NULL;
            }
            algebraic_complement = get_matrix_det(temp_matrix_for_crop, temp_matrix_for_crop->rows);
            if ((i + j) % 2 != 0) {
                algebraic_complement *= -1;
            }
            new_matrix_struct->matrix[i*(matrix->cols)+j] = algebraic_complement;
            free_matrix(temp_matrix_for_crop);
        }
    }
    matrix_t *new_matrix_transp = transp(new_matrix_struct);
    free_matrix(new_matrix_struct);
    return new_matrix_transp;
}

matrix_t* inv(const matrix_t* matrix) {
    if (matrix == NULL || matrix->rows != matrix->cols) {
        return NULL;
    }
    double determinant = 0;
    int success_det = det(matrix, &determinant);
    if (determinant == 0 || success_det != 0) {
        return NULL;
    }
    matrix_t *adj_matrix = adj(matrix);
    if (adj_matrix == NULL) {
        return NULL;
    }
    matrix_t *inv_matrix = mul_scalar(adj_matrix, 1 / determinant);
    free_matrix(adj_matrix);
    return inv_matrix;
}
