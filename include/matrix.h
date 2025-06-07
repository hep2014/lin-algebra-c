#ifndef matrix_h
#define matrix_h


double** addMatrices(double** matrixA, double** matrixB, int rows, int cols);
double** transposeMatrix(double** matrix, int rows, int cols);
double** multiplyMatrices(double** matrixA, int rowsA, int colsA,
                         double** matrixB, int rowsB, int colsB);
double** scalarMultiplyMatrix(double** matrix, int rows, int cols, double scalar);
double** subtractMatrices(double** matrixA, double** matrixB, int rows, int cols);
double** identityMatrix(int N);
double Determinant(double** matrix, int m);
double** invertMatrix(double** mas, int m);
double matrixTrace(double** matrix, int size);


#endif
