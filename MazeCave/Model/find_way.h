#ifndef SRC_MODEL_MODEL_FIND_WAY_H_
#define SRC_MODEL_MODEL_FIND_WAY_H_

#include <vector>

#include "matrix.h"

namespace maze {
constexpr double kStart = 13.13;
constexpr double kFinish = 99.99;

class FindWay {
public:
  FindWay() {}
  FindWay(const FindWay &other) = default;
  FindWay(FindWay &&other) = default;
  FindWay &operator=(const FindWay &other) = default;
  FindWay &operator=(FindWay &&other) = default;
  ~FindWay() { delete labyrinth_matrix_; }

  void SetStartPosition(std::pair<size_t, size_t> start);
  void SetFinishPosition(std::pair<size_t, size_t> finish);
  std::vector<std::pair<size_t, size_t>>
  SolveLabyrinth(size_t rows, size_t cols, std::vector<size_t> vertical_borders,
                 std::vector<size_t> horizontal_borders);

private:
  MyMatrix *labyrinth_matrix_ = nullptr;
  std::vector<std::pair<size_t, size_t>> solving_;
  std::pair<size_t, size_t> start_point_;
  std::pair<size_t, size_t> finish_point_;
  std::vector<size_t> vertical_borders_;
  std::vector<size_t> horizontal_borders_;
  int count_step_ = 0;
  void StartWaveAlgorithm();
  std::pair<bool, bool> CheckNeigbors(size_t i, size_t j);
  bool CheckIsFinish(size_t i, size_t j);
  bool CheckIsEmpty(size_t i, size_t j);
  void SetWaveNumber(size_t i, size_t j, bool &reach_finish,
                     int &count_deadwall);
  void ReverseWay();
  void FindPreviousStep(size_t i, size_t j, std::pair<size_t, size_t> *current);
};
} // namespace maze

#endif // SRC_MODEL_MODEL_FIND_WAY_H_
