#include "model_cave.h"
using namespace maze;

ModelCave::ModelCave(size_t rows, size_t cols, std::vector<size_t> array)
    : row_(rows), col_(cols), index_array_(array) {
  SetMatrix();
}

void ModelCave::SetMatrix() {
  std::vector<size_t>::iterator iter_value = index_array_.begin();
  matrix_value_ = MyMatrix(static_cast<int>(row_), static_cast<int>(col_));
  for (size_t row_value = 0; row_value < row_; ++row_value) {
    for (size_t col_value = 0; col_value < col_; ++col_value) {
      matrix_value_(row_value, col_value) = *iter_value;
      ++iter_value;
    }
  }
}

void ModelCave::GeneratorCave(size_t row_value, size_t col_value,
                              int chance_value) {
  SetRow(row_value);
  SetCol(col_value);
  SetChance(chance_value);
  MyMatrix tmp(row_, col_);
  matrix_value_ = tmp;
  for (size_t row_value = 0; row_value < row_; ++row_value) {
    for (size_t col_value = 0; col_value < col_; ++col_value) {
      std::random_device rd;
      std::uniform_int_distribution<int> uniform_dist(0, 7);
      if (chance_value > uniform_dist(rd)) {
        matrix_value_(row_value, col_value) = 1;
      } else {
        matrix_value_(row_value, col_value) = 0;
      }
    }
  }
  tmp.Clear();
}

void ModelCave::NextState() {
  MyMatrix tmp_matrix = matrix_value_;
  for (int row_value = 0; row_value < static_cast<int>(row_); ++row_value) {
    for (int col_value = 0; col_value < static_cast<int>(col_); ++col_value) {
      int count_birth = 0;
      for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
          int check_value = 0;
          if ((row_value + i < 0) ||
              (row_value + i > static_cast<int>(row_) - 1) ||
              (col_value + j < 0) ||
              (col_value + j > static_cast<int>(col_) - 1)) {
            check_value = 1;
            count_birth++;
          }
          if ((i != 0 || j != 0) && check_value == 0) {
            if ((int)tmp_matrix(row_value + i, col_value + j) == 1)
              count_birth++;
          }
        }
      }
      if (matrix_value_(row_value, col_value) == 1 &&
          count_birth < limit_death_)
        matrix_value_(row_value, col_value) = 0;
      if (static_cast<int>(matrix_value_(row_value, col_value)) == 0 &&
          count_birth > limit_birth_)
        matrix_value_(row_value, col_value) = 1;
    }
  }
  tmp_matrix.Clear();
}

std::vector<size_t> ModelCave::GetIndexArray() {
  index_array_.clear();
  for (size_t row_value = 0; row_value < row_; ++row_value) {
    for (size_t col_value = 0; col_value < col_; ++col_value) {
      index_array_.push_back(matrix_value_(row_value, col_value));
    }
  }
  return index_array_;
}

void ModelCave::SetRow(size_t row_value) { row_ = row_value; }

void ModelCave::SetCol(size_t col_value) { col_ = col_value; }

void ModelCave::SetChance(int chance_value) { chance_value_ = chance_value; }

void ModelCave::SetLimitBirth(int birth_value) { limit_birth_ = birth_value; }

void ModelCave::SetLimitDeath(int death_value) { limit_death_ = death_value; }
