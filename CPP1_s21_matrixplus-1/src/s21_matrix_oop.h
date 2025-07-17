#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
  const double EPS{1e-6};

  // Приватная функция для создания матрицы
  void S21CreateMatrix(int rows, int cols);

  // Приватная функция для пересоздания матрицы
  void ResizeMatrix(int new_rows, int new_cols);

  // Приватная функция для получение минора
  S21Matrix GetMinor(int row, int col) const;

 public:
  // Базовый конструктор
  S21Matrix();

  // Параметризированный конструктор
  S21Matrix(int rows, int cols);

  // Конструктор копирования
  S21Matrix(const S21Matrix& other);

  // Конструктор переноса
  S21Matrix(S21Matrix&& other);

  // Деструктор
  ~S21Matrix();

  // methods
  // Проверяет матрицы на равенство между собой
  bool EqMatrix(const S21Matrix& other);

  // Прибавляет вторую матрицу к текущей
  void SumMatrix(const S21Matrix& other);

  // Вычитает из текущей матрицы другую
  void SubMatrix(const S21Matrix& other);

  // Умножает текущую матрицу на число
  void MulNumber(const double num);

  // Умножает текущую матрицу на вторую
  void MulMatrix(const S21Matrix& other);

  // Создает новую транспонированную матрицу из текущей и возвращает ее
  S21Matrix Transpose();

  // Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
  S21Matrix CalcComplements();

  // Вычисляет и возвращает определитель текущей матрицы
  double Determinant();

  //Вычисляет и возвращает обратную матрицу
  S21Matrix InverseMatrix();

  // Accessor and Mutator

  int GetRows() const;     // Accessor для поля rows_
  void SetRows(int rows);  // Mutator для поля rows_
  int GetCols() const;     // Accessor для поля cols_
  void SetCols(int cols);  // Mutator для поля cols_

  // operators

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix operator*(const double num);
  friend S21Matrix operator*(const double num, S21Matrix& matrix);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  double& operator()(int i, int j);
};

#endif  // S21_MATRIX_OOP_H