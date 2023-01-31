#ifndef SRC_MODEL_MATRIX_H_
#define SRC_MODEL_MATRIX_H_

#include <cmath>
#include <iomanip>
#include <iostream>

namespace maze {

#include <cmath>
#include <iomanip>
#include <iostream>

class MyMatrix {
public:
  MyMatrix();
  MyMatrix(int rows, int cols);
  MyMatrix(int rows, int cols, const double data_massive[]);
  MyMatrix(const MyMatrix &other);
  MyMatrix &operator=(const MyMatrix &other);
  MyMatrix(MyMatrix &&other);
  MyMatrix &operator=(MyMatrix &&other);

  ~MyMatrix();

  // General methods
  bool EqualMatrix(const MyMatrix &other);
  void SumMatrix(const MyMatrix &other);
  void SubMatrix(const MyMatrix &other);
  void MulNumber(const double num);
  void MulMatrix(const MyMatrix &other);
  MyMatrix Transpose();
  double Determinant();
  MyMatrix CalcComplements();
  MyMatrix InverseMatrix();
  void OutputMatrix();
  void Clear() { MemoryFree(); }

  // Operators reloading
  MyMatrix operator+(const MyMatrix &other);
  MyMatrix operator-(const MyMatrix &other);
  MyMatrix operator*(const MyMatrix &other);
  friend MyMatrix operator*(const double num, const MyMatrix &matrix);
  friend MyMatrix operator*(const MyMatrix &matrix, const double num);
  bool operator==(const MyMatrix &other);
  MyMatrix &operator+=(const MyMatrix &other);
  MyMatrix &operator-=(const MyMatrix &other);
  MyMatrix &operator*=(const MyMatrix &other);
  MyMatrix &operator*=(const double num);
  double &operator()(int i, int j);

  // Accessors and Mutators
  int get_rows();
  int get_cols();
  void set_rows(int value_rows);
  void set_cols(int value_cols);
  double **get_matrix() { return matrix_; }

protected:
  void MemoryAllocation();
  void MemoryFree();
  MyMatrix CreateMinorMatrix(int size, int rows_index, int cols_index);

private:
  int rows_, cols_;
  double **matrix_;
};

MyMatrix operator*(const double num, const MyMatrix &matrix);
MyMatrix operator*(const MyMatrix &matrix, const double num);

} // namespace maze

#endif //  SRC_MODEL_MATRIX_H_
