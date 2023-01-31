#ifndef SRC_MODEL_MODEL_CAVE_H_
#define SRC_MODEL_MODEL_CAVE_H_

#include <stdlib.h>
#include <time.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <locale>
#include <random>
#include <string>
#include <vector>

#include "matrix.h"

namespace maze {
class ModelCave {
public:
  ModelCave()
      : row_(0), col_(0), limit_birth_(0), limit_death_(0), chance_value_(0) {}
  ModelCave(size_t rows, size_t cols, std::vector<size_t> array);
  ~ModelCave() { matrix_value_.Clear(); }
  ModelCave(ModelCave const &) = default;
  ModelCave(ModelCave &&) = default;
  ModelCave &operator=(ModelCave const &) = default;
  ModelCave &operator=(ModelCave &&) = default;
  void GeneratorCave(size_t row_value, size_t col_value, int chance_value);
  void NextState();
  void SetChance(int chance_value);
  void SetLimitBirth(int birth_value);
  void SetLimitDeath(int death_value);
  std::vector<size_t> GetIndexArray();

private:
  MyMatrix matrix_value_;
  size_t row_;
  size_t col_;
  std::vector<size_t> index_array_;
  int limit_birth_;
  int limit_death_;
  int chance_value_;
  void SetMatrix();
  void SetRow(size_t row_value);
  void SetCol(size_t col_value);
};
} // namespace maze

#endif // SRC_MODEL_MODEL_CAVE_H_
