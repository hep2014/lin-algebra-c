# Instruction to users (En)

This project implements basic matrix operations in the C programming language. You can build and use the library locally using the provided Makefile.

## Installation Instructions
To build and use the library, you need a C compiler (`gcc`) and `make`.
**Local Build (without installation)**
```
git clone https://github.com/hep2014/lin-algebra-c.git
cd lin-algebra-c
make
```
After that, the dynamic library `libmatrix.so` will be created in the `build/` directory.
To use it in your own C programs:
```
gcc main.c -Lbuild -lmatrix -Iinclude -o main
export LD_LIBRARY_PATH=build:$LD_LIBRARY_PATH
./main
```

**System-wide Installation**
If you want to install the library to your system (`/usr/local/lib` and `/usr/local/include`), run:
```
sudo make install
```
Check that the files were installed:
```
ls /usr/local/lib/libmatrix.so
ls /usr/local/include/matrix.h
```
You can now compile your code without additional flags:
```
gcc main.c -lmatrix -o main
./main
```
To uninstall the library:
```
sudo make uninstall
```
## Library Capabilities

The library operates on objects of type `double**` — an array of pointers to matrix rows, each containing `double` values.  
**Note:** The library does not provide a built-in matrix creation function. You should create matrices manually or use a helper function like the one below:
```
double** createMatrix(int N, int M) {
    double** temporaryMatrix = malloc(N * sizeof(double*));
    if (temporaryMatrix == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    for (int i = 0; i < N; ++i) {
        temporaryMatrix[i] = malloc(M * sizeof(double));
        if (temporaryMatrix[i] == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(1);
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            fscanf(stdin, "%lf", &temporaryMatrix[i][j]);
        }
    }
    return temporaryMatrix;
}
```

**Supported Operations:***
- `double** addMatrices(double** matrixA, double** matrixB, int rows, int cols);`  
    Performs matrix addition of `matrixA` and `matrixB` with identical dimensions.  
    Returns the resulting matrix on success; otherwise, returns an error code.
- `double** subtractMatrices(double** matrixA, double** matrixB, int rows, int cols);`  
    Performs matrix subtraction of `matrixB` from `matrixA`.  
    Returns the resulting matrix on success; otherwise, an error code.
- `double** scalarMultiplyMatrix(double** matrix, int rows, int cols, double scalar);`  
    Multiplies a matrix by a scalar value.  
    Returns the result on success; error code otherwise.
- `double** transposeMatrix(double** matrix, int rows, int cols);`  
    Computes the transpose of the given matrix.  
    Returns a new transposed matrix, or an error code.
- `double** multiplyMatrices(double** matrixA, int rowsA, int colsA, double** matrixB, int rowsB, int colsB);`  
    Performs matrix multiplication of `matrixA × matrixB`.  
    Returns the resulting matrix if dimensions are compatible.
- `double Determinant(double** matrix, int m);`  
    Calculates the determinant of an `m × m` square matrix.  
    For `m=1`, `2`, etc., returns the correct determinant.  
    Returns a `double` value or an error code.
- `double** invertMatrix(double** matrix, int m);`  
    Computes the inverse of an `m × m` matrix.  
    Returns the inverted matrix or an error code if inversion is not possible.
- `double** identityMatrix(int N);`  
    Creates an `N × N` identity matrix.  
    Returns the new matrix or an error code.
- `double matrixTrace(double** matrix, int size);`  
    Computes the trace (sum of diagonal elements) of a square matrix.  
    Returns the result as a `double`.
**Error Codes:**
- `EINVAL` — invalid arguments (e.g. mismatched matrix dimensions)
- `ENOMEM` — memory allocation failure
# Инструкция для пользователей (Ru)

Данный проект содержит в себе реализацию базовых операций с матрицами на языке С. Проект можно установить локально и использовать локально, используя представленный Makefile. 

## Инструкция по установке

Для сборки и использования библиотеки необходимо наличие компилятора `gcc` и утилиты `make`. 

**Локальная сборка (без установки в систему)** 
```bash
git clone https://github.com/hep2014/lin-algebra-c.git
cd lin-algebra-c
make
```
После этого в папке `build/` будет создана динамическая библиотека `libmatrix.so`.
Чтобы использовать её в своих программах:
```
gcc main.c -Lbuild -lmatrix -Iinclude -o main
export LD_LIBRARY_PATH=build:$LD_LIBRARY_PATH
./main
```
**Установка в систему** 
Если вы хотите установить библиотеку в систему (в `/usr/local/lib` и `/usr/local/include`):
```sudo make install``` 
Проверьте, что `libmatrix.so` установлен:
```
ls /usr/local/lib/libmatrix.so
ls /usr/local/include/matrix.h
```
Теперь можно использовать библиотеку без дополнительных флагов:
```
gcc main.c -lmatrix -o main
./main
```
Для удаления установленной библиотеки выполните:
```
sudo make uninstall
```
## Описание возможностей
Библиотека работает с объектами типа ``` double** ``` - массивом указателей на строки матрицы, в каждой строке хранятся числа типа ```double```. Библиотека не содержит реализации создания матрицы, для этого необходимо использовать свой собственный код. Или, к примеру, можно воспользоваться моей реализацией создания: 
```
**
double** createMatrix(int N, int M) {
   double** temporaryMatrix;
   temporaryMatrix = malloc(N * sizeof(double*));
   if (temporaryMatrix == NULL) {
       fprintf(stderr, "Ошибка выделения памяти\n");
       exit(1);
   }
   for (int i = 0; i < N; ++i) {
       temporaryMatrix[i] = malloc(M * sizeof(double));
       if (temporaryMatrix[i] == NULL) {
           fprintf(stderr, "Ошибка выделения памяти\n");
           exit(1);
       }
   }
   for (int i = 0; i < N; ++i) {
       for (int j = 0; j < M; ++j) {
           fscanf(stdin, "%lf", &temporaryMatrix[i][j]);
       }
   }
   return temporaryMatrix;
}
**
```
**Возможности библиотеки:**
- Функция  ```double** addMatrices(double** matrixA, double** matrixB, int rows, int cols);``` производит матричное сложение двух матриц - матрицы А и матрицы В с одинаковым количеством строк rows и столбцов cols. В случае успеха возвращает результирующую матрицу. В случае неудачи возвращает один из двух кодов ошибки, описанных ниже.
- Функция ```double** transposeMatrix(double** matrix, int rows, int cols);``` производит транспонирование матрицы с количеством строк rows и количеством столбцов cols. В случае успеха возвращает результирующую матрицу. В случае неудачи возвращает один из двух кодов ошибки, описанных ниже.
- Функция ```double** multiplyMatrices(double** matrixA, int rowsA, int colsA, double** matrixB, int rowsB, int colsB);``` производит матричное умножение двух матриц - матрицы А (с количеством строк rowsA и количеством столбцов colsA) и матрицы В (с количеством строк rowsB и количеством столбцов colsB). В случае успеха возвращает результирующую матрицу. В случае неудачи возвращает один из двух кодов ошибки, описанных ниже.
- Функция ```double** scalarMultiplyMatrix(double** matrix, int rows, int cols, double scalar);``` умножает матрицу с количеством строк rows и количеством столбцов cols на скаляр scalar. В случае успеха возвращает результирующую матрицу. В случае неудачи возвращает один из двух кодов ошибки, описанных ниже.
- Функция ```double** subtractMatrices(double** matrixA, double** matrixB, int rows, int cols);``` производит матричное вычитание двух матрицы - матрицы А и матрицы В с одинаковым количеством строк (rows) и одинаковым количеством столбцов (cols).  В случае успеха возвращает результирующую матрицу. В случае неудачи возвращает один из двух кодов ошибки, описанных ниже. 
- Функция ```double** identityMatrix(int N);``` создает единичную матрицу размера N. В случае успеха возвращает результирующую матрицу. В случае неудачи возвращает один из двух кодов ошибки, описанных ниже. 
- Функция ```double Determinant(double** matrix, int m);``` вычисляет определитель m-ого порядка матрицы matrix. Порядок определяется следующим образом: при $m=1$ возвращается определитель размера $1 \times 1$, при $m = 2$ возвращается определитель размера $2 \times 2$ и так далее. В случае успеха возвращается число типа ```double```. В случае неудачи возвращает один из двух кодов ошибки, описанных ниже. 
- Функция ```double** invertMatrix(double** mas, int m);``` вычисляет обратную матрицу к матрице mas, размера m.  В случае успеха возвращает результирующую матрицу. В случае неудачи возвращает один из двух кодов ошибки, описанных ниже. 
- Функция ```double matrixTrace(double** matrix, int size);``` вычисляет след матрицы matrix размера size. След - это сумма элементов на главной диагонали. В случае успеха возвращается число типа ```double```. В случае неудачи возвращает один из двух кодов ошибки, описанных ниже. 
**Коды ошибок**: 
- При ошибке, связанной с некорректными аргументами, переданными в функцию, вернётся код ошибки ```EINVAL```
- При ошибке, связанной с невозможностью выделить память, вернётся код ошибки ```ENOMEM``` 







