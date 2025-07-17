#include "s21_matrix_oop.h"

void S21Matrix::S21CreateMatrix(int rows, int cols) {
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; ++i) {
    matrix_[i] = new double[cols]();  // Инициализация нулями
  }
}

S21Matrix::S21Matrix() : rows_(3), cols_(3) { S21CreateMatrix(rows_, cols_); }

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument(
        "Number of rows and columns must be greater than zero");
  }
  rows_ = rows;
  cols_ = cols;
  S21CreateMatrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  // Выделяем память для новой матрицы
  S21CreateMatrix(rows_, cols_);

  // Копируем данные из матрицы объекта other
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  // Обнуляем поля объекта other, чтобы он больше не владел ресурсами
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

int S21Matrix::GetRows() const { return this->rows_; }
int S21Matrix::GetCols() const { return this->cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Number of rows must be greater than 0");
  }
  // Изменяем размер матрицы по строкам
  ResizeMatrix(rows, cols_);
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Number of columns must be greater than 0");
  }
  // Изменяем размер матрицы по столбцам
  ResizeMatrix(rows_, cols);
}

void S21Matrix::ResizeMatrix(int new_rows, int new_cols) {
  // Создаем новую матрицу с новыми размерами
  S21Matrix new_matrix(new_rows, new_cols);
  // Копируем элементы из старой матрицы в новую
  for (int i = 0; i < std::min(rows_, new_rows); ++i) {
    for (int j = 0; j < std::min(cols_, new_cols); ++j) {
      new_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  // Теперь используем конструктор перемещения для переноса результата
  *this = std::move(new_matrix);
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {  // Если указатель не пустой, освобождаем память
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];  // Удаляем каждую строку
    }
    delete[] matrix_;  // Удаляем массив указателей
  }
  rows_ = 0;
  cols_ = 0;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = true;
  // Проверяем размеры матриц
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;  // Если размеры не совпадают, матрицы не равны
  }

  // Проверяем каждый элемент матрицы
  for (int i = 0; result && i < rows_; ++i) {
    for (int j = 0; result && j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        result =
            false;  // Если хотя бы один элемент не совпадает, матрицы не равны
      }
    }
  }

  // Если все элементы совпадают, возвращаем true
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  // Проверяем, что размеры матриц совпадают
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition.");
  }

  // Поэлементное сложение
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  // Проверяем, что размеры матриц совпадают
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition.");
  }

  // Поэлементное сложение
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  // Проверяем возможность умножения матриц
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns of the first matrix must be equal to the number "
        "of rows of the second matrix.");
  }

  // Создаем временную матрицу для хранения результата
  S21Matrix result(rows_, other.cols_);

  // Выполняем умножение матриц
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  // Теперь используем конструктор перемещения для переноса результата
  *this = std::move(result);  // Здесь вызывается конструктор перемещения
}

S21Matrix S21Matrix::Transpose() {
  // Создаем новую матрицу размером cols_ x rows_ (транспонированную)
  S21Matrix result(cols_, rows_);

  // Перемещаем элементы: строка -> столбец и столбец -> строка
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];  // Меняем строки и столбцы местами
    }
  }

  // Возвращаем транспонированную матрицу
  return result;
}

S21Matrix S21Matrix::GetMinor(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);

  for (int i = 0, minor_i = 0; i < rows_; ++i) {
    if (i == row) continue;  // Пропускаем строку row

    for (int j = 0, minor_j = 0; j < cols_; ++j) {
      if (j == col) continue;  // Пропускаем столбец col

      minor.matrix_[minor_i][minor_j] = matrix_[i][j];
      minor_j++;
    }
    minor_i++;
  }

  return minor;
}

double S21Matrix::Determinant() {
  // Проверяем, что матрица квадратная
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Determinant can only be calculated for square matrices.");
  }

  // Базовый случай: определитель матрицы 1x1 — это сам элемент
  if (rows_ == 1) {
    return matrix_[0][0];
  }

  // Базовый случай: определитель матрицы 2x2
  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }

  // Рекурсивный случай: разложение определителя по первой строке
  double det = 0.0;

  for (int j = 0; j < cols_; ++j) {
    // Вычисляем минор для элемента matrix_[0][j]
    S21Matrix minor = GetMinor(0, j);

    // Определяем знак для члена разложения
    double sign = (j % 2 == 0) ? 1.0 : -1.0;

    // Рекурсивно вычисляем определитель минорной матрицы
    det += sign * matrix_[0][j] * minor.Determinant();
  }

  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  // Проверяем, что матрица квадратная
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Complements can only be calculated for square matrices.");
  }

  // Создаем матрицу для хранения алгебраических дополнений
  S21Matrix result(rows_, cols_);

  // Вычисляем алгебраическое дополнение для каждого элемента
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      // Вычисляем минор для элемента (i, j)
      S21Matrix minor = GetMinor(i, j);
      // Вычисляем знак (-1)^(i+j)
      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      // Вычисляем алгебраическое дополнение: знак * определитель минора
      result.matrix_[i][j] = sign * minor.Determinant();
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  // Проверяем, что матрица квадратная
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Inverse matrix can only be calculated for square matrices.");
  }

  // Вычисляем определитель матрицы
  double det = this->Determinant();
  if (det == 0) {
    throw std::invalid_argument(
        "Inverse matrix does not exist for singular matrices (determinant is "
        "zero).");
  }

  // Вычисляем матрицу алгебраических дополнений
  S21Matrix complements = this->CalcComplements();

  // Транспонируем матрицу алгебраических дополнений
  S21Matrix transposed = complements.Transpose();

  // Делим каждый элемент транспонированной матрицы на определитель
  for (int i = 0; i < transposed.rows_; ++i) {
    for (int j = 0; j < transposed.cols_; ++j) {
      transposed.matrix_[i][j] /= det;
    }
  }

  return transposed;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  // Создаем копию текущей матрицы
  S21Matrix result(*this);

  // Используем функцию SumMatrix для сложения
  result.SumMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);

  // Используем функцию SubMatrix для вычитания
  result.SubMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  // Создаем копию текущей матрицы
  S21Matrix result(*this);

  // Используем функцию MulNumber для умножения
  result.MulNumber(num);

  // Возвращаем результат
  return result;
}

S21Matrix operator*(const double num, S21Matrix& matrix) {
  S21Matrix result(matrix.GetRows(), matrix.GetCols());
  for (int i = 0; i < matrix.GetRows(); ++i) {
    for (int j = 0; j < matrix.GetCols(); ++j) {
      result(i, j) = matrix(i, j) * num;
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);

  // Используем функцию MulMatrix для умножения
  result.MulMatrix(other);

  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  // Проверка на самоприсваивание
  if (this != &other) {
    // Освобождаем старую память
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    // Копируем размеры матрицы
    rows_ = other.rows_;
    cols_ = other.cols_;

    // Выделяем новую память для копирования данных
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {  // Защита от самоприсваивания
    // Освобождаем ресурсы текущего объекта
    if (matrix_ != nullptr) {
      for (int i = 0; i < rows_; ++i) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
    }

    // Копируем данные из другого объекта
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    // Обнуляем другой объект, чтобы избежать повторного удаления
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  // Проверяем допустимость индексов
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Matrix indices are out of range");
  }
  return matrix_[i][j];
}
