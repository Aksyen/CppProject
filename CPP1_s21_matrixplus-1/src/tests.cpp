/*
Примеры макросов GTest:
ASSERT_EQ(val1, val2) — проверяет, что val1 равно val2. Если значения не равны,
тест завершается неудачно.
ASSERT_TRUE(condition) — проверяет, что условие
истинно. Если оно ложно, тест завершается неудачно.
ASSERT_THROW(statement,
exception_type) — проверяет, что выражение выбрасывает исключение определённого
типа.
EXPECT_EQ(val1, val2) — аналогично ASSERT_EQ, но тест продолжает
выполняться даже если проверка не пройдена.
*/

#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// Тесты на конструкторы
TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, ParamConstructor) {
  S21Matrix matrix(2, 3);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 5;
  S21Matrix matrix2(matrix1);
  EXPECT_EQ(matrix2(0, 0), 5);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 5;
  S21Matrix matrix2(std::move(matrix1));
  EXPECT_EQ(matrix2(0, 0), 5);
  EXPECT_EQ(matrix1.GetRows(), 0);  // Убедимся, что данные перемещены
}

// Тесты на операторы присваивания
TEST(S21MatrixTest, AssignmentOperator) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 5;
  S21Matrix matrix2 = matrix1;
  EXPECT_EQ(matrix2(0, 0), 5);
}

// Тесты на операции сложения
TEST(S21MatrixTest, SumMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1;
  matrix2(0, 0) = 2;
  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 3);
}

TEST(S21MatrixTest, AddOperator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1;
  matrix2(0, 0) = 2;
  S21Matrix result = matrix1 + matrix2;
  EXPECT_EQ(result(0, 0), 3);
}

// Тесты на операции вычитания
TEST(S21MatrixTest, SubMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 5;
  matrix2(0, 0) = 2;
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 3);
}

TEST(S21MatrixTest, SubOperator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 5;
  matrix2(0, 0) = 2;
  S21Matrix result = matrix1 - matrix2;
  EXPECT_EQ(result(0, 0), 3);
}

// Тесты на операции умножения
TEST(S21MatrixTest, MulNumber) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2;
  matrix.MulNumber(5);
  EXPECT_EQ(matrix(0, 0), 10);
}

TEST(S21MatrixTest, MulMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1;
  matrix2(0, 0) = 2;
  matrix1.MulMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 2);
}

// Тесты на оператор сравнения
TEST(S21MatrixTest, EqMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1;
  matrix2(0, 0) = 1;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTest, EqOperator) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1;
  matrix2(0, 0) = 1;
  EXPECT_TRUE(matrix1 == matrix2);
}

// Тесты на исключительные ситуации
TEST(S21MatrixTest, InvalidMatrixDimensions) {
  EXPECT_THROW(S21Matrix(-1, 2), std::invalid_argument);
  EXPECT_THROW(S21Matrix(2, -1), std::invalid_argument);
}

TEST(InverseMatrix_method_1, test_1) {
  S21Matrix Matrix(3, 3);
  Matrix(0, 0) = 2;
  Matrix(0, 1) = 5;
  Matrix(0, 2) = 7;
  Matrix(1, 0) = 6;
  Matrix(1, 1) = 3;
  Matrix(1, 2) = 4;
  Matrix(2, 0) = 5;
  Matrix(2, 1) = -2;
  Matrix(2, 2) = -3;
  S21Matrix Matrix_Copy = Matrix.InverseMatrix();
  S21Matrix Matrix_2(3, 3);
  Matrix_2(0, 0) = 1;
  Matrix_2(0, 1) = -1;
  Matrix_2(0, 2) = 1;
  Matrix_2(1, 0) = -38;
  Matrix_2(1, 1) = 41;
  Matrix_2(1, 2) = -34;
  Matrix_2(2, 0) = 27;
  Matrix_2(2, 1) = -29;
  Matrix_2(2, 2) = 24;
  for (int i = 0; i < Matrix.GetRows(); i++) {
    for (int j = 0; j < Matrix.GetCols(); j++) {
      ASSERT_EQ(Matrix_Copy(i, j), Matrix_2(i, j));
    }
  }
}

TEST(Constructor_default_1, test_1) {
  S21Matrix Matrix;
  ASSERT_EQ(Matrix.GetCols(), 3);
  ASSERT_EQ(Matrix.GetRows(), 3);
}

TEST(Constructor_default_2, test_1) {
  S21Matrix Matrix(5, 5);
  ASSERT_EQ(Matrix.GetRows(), 5);
  ASSERT_EQ(Matrix.GetCols(), 5);
  Matrix(3, 2) = 6.54321;
  ASSERT_DOUBLE_EQ(Matrix(3, 2), 6.54321);
}

TEST(Constructor_default_3, test_3) {
  ASSERT_ANY_THROW(S21Matrix Matrix(0, -243));
}

TEST(Constructor_copying, test_1) {
  S21Matrix Matrix(2, 2);
  for (int i = 0; i < Matrix.GetRows(); i++) {
    for (int j = 0; j < Matrix.GetCols(); j++) {
      Matrix(i, j) = 3.14;
    }
  }
  S21Matrix Matrix2(Matrix);
  for (int i = 0; i < Matrix.GetRows(); i++) {
    for (int j = 0; j < Matrix.GetCols(); j++) {
      ASSERT_EQ(Matrix(i, j), Matrix2(i, j));
    }
  }
}

TEST(Constructor_copying, test_2) {
  S21Matrix M1(2, 2);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 3.15;
    }
  }
  S21Matrix M2 = M1;
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      ASSERT_EQ(M1(i, j), M2(i, j));
    }
  }
}

TEST(Constructor_move, test_1) {
  S21Matrix M1(2, 2);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 3.15;
    }
  }
  S21Matrix M2 = std::move(M1);

  ASSERT_EQ(M2.GetRows(), 2);
  ASSERT_EQ(M2.GetCols(), 2);
  ASSERT_EQ(M1.GetRows(), 0);
  ASSERT_EQ(M1.GetCols(), 0);
}

TEST(Constructor_move, test_2) {
  S21Matrix M1(2, 2);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 3.15;
    }
  }
  S21Matrix M2(std::move(M1));

  ASSERT_EQ(M2.GetRows(), 2);
  ASSERT_EQ(M2.GetCols(), 2);
  ASSERT_EQ(M1.GetRows(), 0);
  ASSERT_EQ(M1.GetCols(), 0);
}

TEST(Test_EqMatrix, test_1) {
  S21Matrix M(3, 3);
  S21Matrix M2(2, 2);
  ASSERT_EQ(M.EqMatrix(M2), false);
}

TEST(Test_EqMatrix, test_2) {
  S21Matrix M(3, 3);
  S21Matrix M2(3, 3);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 3.146743;
    }
  }
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      M2(i, j) = 3.146743;
    }
  }
  ASSERT_EQ(M.EqMatrix(M2), true);
}

TEST(Test_SumMatrix, test_1) {
  S21Matrix M1(3, 3);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 2.15;
    }
  }
  S21Matrix M2(M1);
  M2.SumMatrix(M1);
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      ASSERT_EQ(M2(i, j), 4.3);
    }
  }
}

TEST(Test_SumMatrix, test_2) {
  S21Matrix M;
  S21Matrix M2(2, 2);
  ASSERT_ANY_THROW(M.SumMatrix(M2));
}

TEST(Test_SubMatrix, test_1) {
  S21Matrix M1(3, 3);
  for (int i = 0; i < M1.GetRows(); i++) {
    for (int j = 0; j < M1.GetCols(); j++) {
      M1(i, j) = 2.15;
    }
  }
  S21Matrix M2(M1);
  M2.SubMatrix(M1);
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      ASSERT_EQ(M2(i, j), 0);
    }
  }
}

TEST(Test_SubMatrix, test_2) {
  S21Matrix M;
  S21Matrix M2(2, 2);
  ASSERT_ANY_THROW(M.SubMatrix(M2));
}

TEST(Test_MulNumber, test_1) {
  S21Matrix M(4, 4);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 5;
    }
  }
  M.MulNumber(10);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      ASSERT_DOUBLE_EQ(M(i, j), 50);
    }
  }
}

TEST(Test_MulNumber, test_2) {
  S21Matrix M;
  M.SetRows(1);
  M.SetCols(1);
  M(0, 0) = 1;
  ASSERT_DOUBLE_EQ(M(0, 0), 1);
}

TEST(Test_MulMatrix, test_1) {
  S21Matrix M(2, 4);
  S21Matrix M2(4, 2);
  M.MulMatrix(M2);
  ASSERT_EQ(M.GetCols(), 2);
  ASSERT_EQ(M.GetRows(), 2);
}

TEST(Test_MulMatrix, test_2) {
  S21Matrix M(2, 4);
  S21Matrix M2(2, 4);
  ASSERT_ANY_THROW(M.MulMatrix(M2));
}

TEST(Test_MulMatrix, test_3) {
  S21Matrix M(3, 3);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = i + j;
    }
  }
  S21Matrix M2 = M;
  M.MulMatrix(M2);
  ASSERT_DOUBLE_EQ(M(0, 0), 5);
  ASSERT_DOUBLE_EQ(M(0, 1), 8);
  ASSERT_DOUBLE_EQ(M(0, 2), 11);

  ASSERT_DOUBLE_EQ(M(1, 0), 8);
  ASSERT_DOUBLE_EQ(M(1, 1), 14);
  ASSERT_DOUBLE_EQ(M(1, 2), 20);

  ASSERT_DOUBLE_EQ(M(2, 0), 11);
  ASSERT_DOUBLE_EQ(M(2, 1), 20);
  ASSERT_DOUBLE_EQ(M(2, 2), 29);
}

TEST(Test_Transpose, test_1) {
  S21Matrix M(7, 2);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 4;
    }
  }
  S21Matrix M2 = M.Transpose();
  for (int i = 0; i < M.GetCols(); i++) {
    for (int j = 0; j < M.GetRows(); j++) {
      ASSERT_DOUBLE_EQ(M2(i, j), 4);
    }
  }
}

TEST(Test_CalcComplements, test_1) {
  S21Matrix M(3, 3);
  M(0, 0) = 1;
  M(0, 1) = 2;
  M(0, 2) = 3;

  M(1, 0) = 0;
  M(1, 1) = 4;
  M(1, 2) = 2;

  M(2, 0) = 5;
  M(2, 1) = 2;
  M(2, 2) = 1;

  S21Matrix M2 = M.CalcComplements();
  ASSERT_DOUBLE_EQ(M2(0, 0), 0);
  ASSERT_DOUBLE_EQ(M2(0, 1), 10);
  ASSERT_DOUBLE_EQ(M2(0, 2), -20);

  ASSERT_DOUBLE_EQ(M2(1, 0), 4);
  ASSERT_DOUBLE_EQ(M2(1, 1), -14);
  ASSERT_DOUBLE_EQ(M2(1, 2), 8);

  ASSERT_DOUBLE_EQ(M2(2, 0), -8);
  ASSERT_DOUBLE_EQ(M2(2, 1), -2);
  ASSERT_DOUBLE_EQ(M2(2, 2), 4);
}

TEST(Test_Determinant, test_1) {
  S21Matrix M(3, 3);
  M(0, 0) = 3;
  M(0, 1) = 2;
  M(0, 2) = 3;

  M(1, 0) = 4;
  M(1, 1) = 5;
  M(1, 2) = 6;

  M(2, 0) = 7;
  M(2, 1) = 8;
  M(2, 2) = 9;

  double res = M.Determinant();

  ASSERT_NEAR(res, -6, 1e-6);
}

TEST(Test_Determinant, test_2) {
  S21Matrix M(2, 3);
  M(0, 0) = 8;
  M(0, 1) = 800;
  M(0, 2) = 5;

  M(1, 0) = 5;
  M(1, 1) = 5;
  M(1, 2) = 3;

  ASSERT_ANY_THROW(M.Determinant());
}

TEST(Method_Determinant, test_3) {
  S21Matrix M(2, 2);
  M(0, 0) = 1;
  M(0, 1) = 2;

  M(1, 0) = 4;
  M(1, 1) = 5;

  double res = M.Determinant();
  ASSERT_NEAR(res, -3.0, 1e-6);
}

TEST(Test_InverseMatrix, test_1) {
  S21Matrix M(3, 3);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 0;
    }
  }
  ASSERT_ANY_THROW(M.InverseMatrix());
}

TEST(Test_Operator_assignment_move, test_1) {
  S21Matrix M(4, 4);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 38.456;
    }
  }
  S21Matrix M2;
  M2 = std::move(M);
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      ASSERT_DOUBLE_EQ(M2(i, j), 38.456);
    }
  }
  ASSERT_EQ(M.GetRows(), 0);
  ASSERT_EQ(M.GetCols(), 0);
}

TEST(Test_Operator_brackets, test_1) {
  S21Matrix M(4, 4);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 38;
    }
  }
  ASSERT_DOUBLE_EQ(M(2, 2), 38);
}

TEST(Test_Operator_Sum, test_1) {
  S21Matrix M(6, 6);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 10;
    }
  }
  S21Matrix M2 = M;
  S21Matrix M3 = M2 + M;
  for (int i = 0; i < M3.GetRows(); i++) {
    for (int j = 0; j < M3.GetCols(); j++) {
      ASSERT_EQ(M3(i, j), 20);
    }
  }
}

TEST(Test_Operator_Sub, test_1) {
  S21Matrix M(6, 6);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 32.666554;
    }
  }
  S21Matrix M2 = M;
  S21Matrix M3 = M - M2;
  for (int i = 0; i < M2.GetRows(); i++) {
    for (int j = 0; j < M2.GetCols(); j++) {
      ASSERT_EQ(M3(i, j), 0);
    }
  }
}

TEST(Test_Operator_MulMatrix, test_1) {
  S21Matrix M(4, 5);
  S21Matrix M2(4, 5);

  ASSERT_ANY_THROW(M * M2);
}

TEST(Test_Operator_EqMatrix, test_1) {
  S21Matrix M(3, 3);
  S21Matrix M2(2, 2);

  ASSERT_EQ(M == M2, 0);
}

TEST(Test_Operator_MulNumber, test_1) {
  S21Matrix M(5, 5);
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      M(i, j) = 38;
    }
  }
  S21Matrix M3 = M * 9;
  for (int i = 0; i < M3.GetRows(); i++) {
    for (int j = 0; j < M3.GetCols(); j++) {
      ASSERT_DOUBLE_EQ(M3(i, j), 342);
    }
  }
}

TEST(Test_Operator_MulNumber, test_2) {
  S21Matrix M(1, 1);
  M(0, 0) = 1;
  S21Matrix M3(1, 1);
  M3 = 9 * M;
  ASSERT_DOUBLE_EQ(M3(0, 0), 9);
}

TEST(Test_Operator_SumMatrix_Assignment, test_1) {
  S21Matrix M(3, 3);
  S21Matrix M2(3, 4);

  ASSERT_ANY_THROW(M += M2);
}

TEST(Test_Operator_SubMatrix_Assignment, test_1) {
  S21Matrix M(3, 3);
  S21Matrix M2(3, 4);

  ASSERT_ANY_THROW(M -= M2);
}

TEST(Test_Operator_MulNumber_Assignment, test_1) {
  S21Matrix M(3, 3);
  M(0, 0) = 1;
  M(0, 1) = 2;
  M(0, 2) = 3;
  M(1, 0) = 1;
  M(1, 1) = 2;
  M(1, 2) = 3;
  M(2, 0) = 1;
  M(2, 1) = 2;
  M(2, 2) = 3;
  M *= 2;
  S21Matrix M1(3, 3);
  M1(0, 0) = 1 * 2;
  M1(0, 1) = 2 * 2;
  M1(0, 2) = 3 * 2;
  M1(1, 0) = 1 * 2;
  M1(1, 1) = 2 * 2;
  M1(1, 2) = 3 * 2;
  M1(2, 0) = 1 * 2;
  M1(2, 1) = 2 * 2;
  M1(2, 2) = 3 * 2;
  for (int i = 0; i < M.GetRows(); i++) {
    for (int j = 0; j < M.GetCols(); j++) {
      ASSERT_DOUBLE_EQ(M(i, j), M1(i, j));
    }
  }
}

TEST(Test_Operator_MulMatrix_Assignment, test_1) {
  S21Matrix M(4, 5);
  S21Matrix M2(4, 5);

  ASSERT_ANY_THROW(M *= M2);
}

TEST(Test_Operator_MulMatrix_Assignment, test_2) {
  S21Matrix M(2, 8);
  S21Matrix M2;
  ASSERT_ANY_THROW(M *= M2);
  ASSERT_ANY_THROW(M2 *= M);
}

TEST(Test_SetRows, test_1) {
  S21Matrix M(5, 5);
  ASSERT_ANY_THROW(M.SetRows(0));
}

TEST(Test_SetCols, test_1) {
  S21Matrix M(5, 5);
  ASSERT_ANY_THROW(M.SetCols(0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
