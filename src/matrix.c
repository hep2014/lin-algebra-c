#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
#include <errno.h>
/*

EN:
In case of error, `errno` is set accordingly:
    - EINVAL for invalid arguments
    - ENOMEM for memory allocation failure

RU:
В случае ошибки устанавливается errno:
    - EINVAL при недопустимых аргументах
    - ENOMEM при ошибке выделения памяти

*/
/*
EN:
This function performs matrix addition. 
It assumes that the matrix is represented as a 2D array of type `double`, 
with `rows` number of rows and `cols` number of columns.

RU:
Данная функция реализует матричное сложение. Предполагается, что матрица задана как 
массив типа double, в котором N строк (rows) и M столбцов (cols).

*/

double** addMatrices(double** matrixA, double** matrixB, int rows, int cols) {
    // Проверка на корректное задание матриц
    // Check if the provided matrices are valid
    if (!matrixA || !matrixB){
        errno = EINVAL;
        return NULL;
    } 
    // Проверка на корректное задание размерностей
    // Check if matrix dimensions are valid
    if (rows < 0 || cols < 0){
        errno = EINVAL;
        return NULL;
    }
    double** result = malloc(rows * sizeof(double*));
    // Проверка на то, успешно ли выделена память 
    // Allocate memory for the result matrix
    if (!result){
        errno = ENOMEM;
        return NULL;
    }
    for (uint64_t i = 0; i < (uint64_t)rows; ++i) {
        result[i] = malloc(cols * sizeof(double));
        // Если не удалось выделить память, то мы освободим выделенную ранее память - защита от утечек
        // If memory allocation fails, free previously allocated memory to prevent leaks
        if (!result[i]) {
            for (uint64_t k = 0; k < i; ++k) {
                free(result[k]);
            }
            free(result);
            errno = ENOMEM;
            return NULL;
        }
        for (uint64_t j = 0; j < (uint64_t)cols; ++j) {
            // Поэлементное сложение происходит здесь 
            // Element-wise matrix addition happens here
            result[i][j] = matrixA[i][j] + matrixB[i][j]; 
        }
    }
    // Return the resulting matrix (as double**)
    // Возвращается матрица, заданная как double** - результат сложения 
    return result; 
}


/*

EN:
This function is not part of the public API.
It is used internally to free memory allocated for a matrix (2D array of doubles).

RU:
Данная функция не видна пользователю. Используется для освобождения памяти, выделенной для матрицы.

*/
static void freeMatrix(double** matrix, int rows) {
    // Safety check
    // Проверка на верное выделение памяти 
    if (!matrix || rows <= 0) return;
    for (uint64_t i = 0; i < (uint64_t)rows; ++i)
        free(matrix[i]);
    free(matrix);
}



/*

EN:
This function transposes the given matrix `matrix` with `rows` number of rows and `cols` number of columns.
It returns a newly allocated transposed matrix of size (cols x rows).

RU:
Данная функция транспонирует заданную матрицу matrix с N количеством строк (rows) и M количеством столбцов (cols).

*/
double** transposeMatrix(double** matrix, int rows, int cols) {
    // Проверка на корректность указателя на матрицу
    // Validate input matrix pointer
    if (!matrix){
        errno = EINVAL;
        return NULL;
    }
    // Проверка на корректность размерностей
    // Validate matrix dimensions
    if (rows <= 0 || cols <= 0){
        errno = ENOMEM;
        return NULL;
    }
    // Выделяем память под транспонированную матрицу (M x N)
    // Allocate memory for transposed matrix (cols x rows)
    double** transposed = malloc(cols * sizeof(double*));
    if (!transposed){
        errno = ENOMEM;
        return NULL;
    } 
    for (uint64_t i = 0; i < (uint64_t)cols; ++i) {
        transposed[i] = malloc(rows * sizeof(double));
        if (!transposed[i]){
            freeMatrix(transposed, cols);
            errno = ENOMEM;
            return NULL;
        }
    }
    // Транспонируем
    // Perform transposition
    for (uint64_t i = 0; i < (uint64_t)rows; ++i)
        for (uint64_t j = 0; j < (uint64_t)cols; ++j)
            transposed[j][i] = matrix[i][j];

    // Функция возвращает транспонированную матрицу
    // Return transposed matrix
    return transposed;
}


/*

EN:
This function multiplies matrix A (rowsA x colsA) by matrix B (rowsB x colsB).
Matrices must be compatible for multiplication: colsA must equal rowsB.

RU:
Данная функция умножает матрицу А на матрицу Б. При этом матрицы должны быть совместимы.

*/

double** multiplyMatrices(double** matrixA, int rowsA, int colsA,
                          double** matrixB, int rowsB, int colsB) {
    // Несовместимые матрицы
    // Validate dimensions compatibility
    if (colsA != rowsB){
        errno = EINVAL;
        return NULL; 
    }
    // Проверка на корректное задание матриц
    // Check if the provided matrices are valid
    if (!matrixA || !matrixB){
        errno = EINVAL;
        return NULL;
    } 
    // Проверка на корректное задание размерностей
    // Check if matrix dimensions are valid
    if (rowsA <= 0 || colsA <= 0 || rowsB <= 0 || colsB <= 0){
        errno = EINVAL;
        return NULL;
    }
    // Выделение памяти для результирующей матрицы
    // Allocate memory for the result matrix (rowsA x colsB)
    double** result = malloc(rowsA * sizeof(double*));
    if (!result){
        errno = ENOMEM;
        return NULL;
    }
    for (uint64_t i = 0; i < (uint64_t)rowsA; ++i) {
        result[i] = malloc(colsB * sizeof(double));
        if (!result[i]){
            errno = ENOMEM;
            freeMatrix(result, i);
            return NULL;
        }
        // Здесь производится матричное умножение
        // Initialize result cell and compute dot product
        for (uint64_t j = 0; j < (uint64_t)colsB; ++j) {
            result[i][j] = 0.0;
            for (uint64_t k = 0; k < (uint64_t)colsA; ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    // Функция возвращает результат матричного умножения двух матриц 
    return result;
}
/*

EN:
This function performs scalar multiplication of a matrix.
It multiplies each element of the matrix `matrix` (rows x cols) by the given `scalar`.
On success, returns a new matrix (rows x cols) with scaled values.

RU: 
Данная функция реализует умножение матрицы matrix на скаляр scalar.
*/

double** scalarMultiplyMatrix(double** matrix, int rows, int cols, double scalar) {
    // Проверка на корректность указателя на матрицу
    // Validate input matrix pointer
    if (!matrix){
        errno = EINVAL;
        return NULL;
    }
    // Проверка на корректность размерностей
    // Validate matrix dimensions
    if (rows <= 0 || cols <= 0){
        errno = EINVAL;
        return NULL;
    }
    // Выделение памяти для результирующей матрицы
    // Allocate memory for the result matrix
    double** result = malloc(rows * sizeof(double*));
    if (!result){
        errno = ENOMEM;
        return NULL;
    }
    for (uint64_t i = 0; i < (uint64_t)rows; ++i){
        result[i] = malloc(cols * sizeof(double));
        if (!result[i]){
            errno = ENOMEM;
            freeMatrix(result, i);
            return NULL;
        }
        for (uint64_t j = 0; j < (uint64_t)cols; ++j){
            result[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}

/*

EN:
This function performs element-wise subtraction of two matrices: A - B.
Both matrices must have the same dimensions (rows x cols).
On success, returns a newly allocated result matrix C.

RU:
Данная функция реализует вычитание двух матриц: матрицы А и матрицы Б. В случае успеха возвращается результирующая 
матрица С. Размеры матриц А и Б должны совпадать. 

*/
double** subtractMatrices(double** matrixA, double** matrixB, int rows, int cols) {
    // Проверка на корректность указателя на матрицу
    // Validate input matrix pointer
    if (!matrixA || !matrixB){
        errno = EINVAL;
        return NULL;
    }
    // Проверка на корректность размерностей
    // Validate matrix dimensions
    if (rows <= 0 || cols <= 0){
        errno = EINVAL;
        return NULL;
    }
    // Выделение памяти для результирующей матрицы
    // Allocate memory for the result matrix
    double** result = malloc(rows * sizeof(double*));
    if (!result){
        errno = ENOMEM;
        return NULL;
    }

    for (uint64_t i = 0; i < (uint64_t)rows; ++i) {
        result[i] = malloc(cols * sizeof(double));
        // Если не удалось выделить память, то мы освободим выделенную ранее память - защита от утечек
        // If memory allocation fails, free previously allocated memory to prevent leaks
        if (!result[i]) {
            freeMatrix(result, i);
            errno = ENOMEM;
            return NULL;
        }
        for (uint64_t j = 0; j < (uint64_t)cols; ++j) {
            // Поэлементное вычитание происходит здесь 
            result[i][j] = matrixA[i][j] - matrixB[i][j]; 
        }
    }
    // Return the resulting matrix (as double**)
    // Возвращается матрица, заданная как double** - результат вычитания
    return result; 
}


/*
EN:
This function creates an identity matrix of size N x N.
Returns a dynamically allocated 2D array (double**) where diagonal elements are 1 and others are 0.

RU:
Данная функция создаёт единичную матрицу размера NxN. В результате возвращается массив типа double** 
*/

double** identityMatrix(int N){
    // Проверка на корректный размер
    // Validate matrix size
    if (N < 0){
        errno = EINVAL; 
        return NULL; 
    }
    // Выделение памяти для массива строк
    // Allocate memory for row pointers
    double** tempMatrix = malloc(N * sizeof(double*));
    if (!tempMatrix){
        errno = ENOMEM; 
        return NULL; 
    }
    // Выделение памяти под каждую строку
    // Allocate memory for each row
    for (uint64_t i = 0; i < (uint64_t)N; ++i){
        tempMatrix[i] = malloc(N*sizeof(double));
        if (!tempMatrix[i]){
            freeMatrix(tempMatrix, i);
            errno = ENOMEM; 
            return NULL;
        }
    }
    // Заполнение единичной матрицы
    // Fill the matrix: 1s on diagonal, 0s elsewhere
    for (uint64_t i = 0; i < (uint64_t)N; ++i){
        for (uint64_t j = 0; j < (uint64_t)N; ++j){
            if (i == j) {tempMatrix[i][j] = 1;}
            else {tempMatrix[i][j] = 0;}
        } 
    }
    return tempMatrix;
}


/*

RU: 
Данная функция не видна пользователю. Используется как вспомогательная для функции Determinant. 
Возвращает матрицу без i-ой строки и j-го столбца.

*/
static double** GetMatr(double** matrix, int rows, int cols, int row, int col) {
  if (!matrix){
    errno = ENOMEM; 
    return NULL; 
  }
  int di, dj;
  double** p = (double**)malloc((rows - 1) * sizeof(double*));
  if (!p){
    errno = ENOMEM; 
    return NULL; 
  }
  di = 0;
  for (int i = 0; i < rows - 1; i++) { // проверка индекса строки
    if (i == row)  // строка совпала с вычеркиваемой
      di = 1;    // - дальше индексы на 1 больше
    dj = 0;
    p[i] = (double*)malloc((cols - 1) * sizeof(double));
    for (int j = 0; j < cols - 1; j++) { // проверка индекса столбца
      if (j == col)  // столбец совпал с вычеркиваемым
        dj = 1;    // - дальше индексы на 1 больше
      p[i][j] = matrix[i + di][j + dj];
    }
  }
  return p;
}

/*
EN:
This function recursively calculates the determinant of a square matrix of size m x m.
Returns the determinant as a double.

RU: 
Данная функция вычисляет определитель матрицы matrix размера m 
*/
double Determinant(double** matrix, int m) {
    if (!matrix){
        errno = EINVAL;
        return 0.0;
    }
    if (m < 1){
        errno = EINVAL;
        return 0.0;
    }
    if (m == 1)
        return matrix[0][0];
    if (m == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    double det = 0;
    int sign = 1;
    for (uint64_t i = 0; i < (uint64_t)m; i++) {
        double** minor = GetMatr(matrix, m, m, i, 0);
        if (!minor){
            errno = ENOMEM; 
            return 0.0; 
        }
        double minor_det = Determinant(minor, m - 1);
        det += sign * matrix[i][0] * minor_det;
        sign = -sign;
        freeMatrix(minor, m - 1);  // Очищаем каждый minor сразу
    }

    return det;
}

/*
EN:
This function attempts to compute the inverse of a square matrix `mas` of size m x m.
It uses the classical adjugate matrix method (cofactor matrix, transposed, divided by determinant).
Returns the inverse matrix on success, or NULL on error.

RU:
Данная функция вычисляет обратную матрицу для квадратной матрицы `mas` размером m x m.
Используется классический метод: алгебраическое дополнение → транспонирование → деление на определитель.

*/

double** invertMatrix(double** mas, int m) {
    if (!mas || m <= 0) {
        errno = EINVAL;
        return NULL;
    }

    double det = Determinant(mas, m);
    if (det == 0.0) {
        errno = EINVAL; // Matrix is non-invertible
        return NULL;
    }

    double** cofactors = malloc(m * sizeof(double*));
    if (!cofactors) {
        errno = ENOMEM;
        return NULL;
    }

    for (uint64_t i = 0; i < (uint64_t)m; ++i) {
        cofactors[i] = malloc(m * sizeof(double));
        if (!cofactors[i]) {
            freeMatrix(cofactors, i);
            errno = ENOMEM;
            return NULL;
        }

        for (uint64_t j = 0; j < (uint64_t)m; ++j) {
            double** minor = GetMatr(mas, m, m, i, j);
            if (!minor) {
                freeMatrix(cofactors, i + 1);
                errno = ENOMEM;
                return NULL;
            }

            double minor_det = Determinant(minor, m - 1);
            cofactors[i][j] = ((i + j) % 2 == 0 ? 1.0 : -1.0) * minor_det / det;
            freeMatrix(minor, m - 1);
        }
    }

    double** inverse = transposeMatrix(cofactors, m, m);
    freeMatrix(cofactors, m);
    return inverse;
}


/*

EN:
This function calculates the trace of a square matrix of size n x n.
The trace is the sum of all diagonal elements.
Returns the trace as a double.
RU:
Данная функция реализует нахождения следа (trace) матрицы matrix. Матрица должна быть строго квадратной

*/

double matrixTrace(double** matrix, int size){
    if (!matrix || size < 1){
        errno = EINVAL; 
        return 0.0; 
    } 
    double result = 0;
    for (uint64_t i = 0; i < (uint64_t)size; ++i) {
        result += matrix[i][i];
    }
    return result; 
}
Add matrix.c implementation to src/
