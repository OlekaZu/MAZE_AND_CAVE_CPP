#include "find_way.h"
using namespace maze;

void FindWay::SetStartPosition(std::pair<size_t, size_t> start) {
  start_point_ = start;
}
void FindWay::SetFinishPosition(std::pair<size_t, size_t> finish) {
  finish_point_ = finish;
}
std::vector<std::pair<size_t, size_t>>
FindWay::SolveLabyrinth(size_t rows, size_t cols,
                        std::vector<size_t> vertical_borders,
                        std::vector<size_t> horizontal_borders) {
  labyrinth_matrix_ = new MyMatrix(rows, cols);
  (*labyrinth_matrix_)(start_point_.first, start_point_.second) = kStart;
  (*labyrinth_matrix_)(finish_point_.first, finish_point_.second) = kFinish;
  vertical_borders_ = vertical_borders;
  horizontal_borders_ = horizontal_borders;
  auto first_check = CheckNeigbors(start_point_.first, start_point_.second);
  if (first_check.first) {
    solving_.push_back(start_point_);
    solving_.push_back(finish_point_);
  } else {
    StartWaveAlgorithm();
    ReverseWay();
  }
  return solving_;
}

void FindWay::StartWaveAlgorithm() {
  ++count_step_;
  bool stop = false;
  int count_wave = 0;
  int count_deadway = 0;
  for (size_t i = 0; i < static_cast<size_t>(labyrinth_matrix_->get_rows());
       ++i) {
    for (size_t j = 0; j < static_cast<size_t>(labyrinth_matrix_->get_cols());
         ++j) {
      if ((*labyrinth_matrix_)(i, j) == count_step_) {
        ++count_wave;
        auto result = CheckNeigbors(i, j);
        stop = result.first;
        if (stop)
          break;
        if (result.second)
          ++count_deadway;
      }
    }
    if (stop)
      break;
  }
  if (count_wave == count_deadway)
    throw std::out_of_range("No labyrinth solution!");
  if (!stop)
    StartWaveAlgorithm();
}

std::pair<bool, bool> FindWay::CheckNeigbors(size_t i, size_t j) {
  bool reach_finish = false;
  bool deadwall = false;
  int count_deadwall = 0;
  int cols = labyrinth_matrix_->get_cols();
  int index_i = i * cols;
  if (!vertical_borders_[j + index_i])
    SetWaveNumber(i, j + 1, reach_finish, count_deadwall);
  else
    ++count_deadwall;
  if (j && !vertical_borders_[j + index_i - 1])
    SetWaveNumber(i, j - 1, reach_finish, count_deadwall);
  else
    ++count_deadwall;
  if (!horizontal_borders_[j + index_i])
    SetWaveNumber(i + 1, j, reach_finish, count_deadwall);
  else
    ++count_deadwall;
  if (i && !horizontal_borders_[j + index_i - cols])
    SetWaveNumber(i - 1, j, reach_finish, count_deadwall);
  else
    ++count_deadwall;
  // checking for dead end
  if (count_deadwall == 4)
    deadwall = true;
  return std::make_pair(reach_finish, deadwall);
}

bool FindWay::CheckIsFinish(size_t i, size_t j) {
  return ((*labyrinth_matrix_)(i, j) == kFinish);
}

bool FindWay::CheckIsEmpty(size_t i, size_t j) {
  return !(*labyrinth_matrix_)(i, j);
}

void FindWay::SetWaveNumber(size_t i, size_t j, bool &reach_finish,
                            int &count_deadwall) {
  if (CheckIsFinish(i, j))
    reach_finish = true;
  else if (CheckIsEmpty(i, j))
    (*labyrinth_matrix_)(i, j) = count_step_ + 1;
  else
    ++(count_deadwall);
}

void FindWay::ReverseWay() {
  solving_.push_back(finish_point_);
  int cols = labyrinth_matrix_->get_cols();
  std::pair<size_t, size_t> current_point = finish_point_;
  while (current_point != start_point_) {
    size_t i = current_point.first;
    size_t j = current_point.second;
    int index_i = i * cols;
    if (i && !horizontal_borders_[j + index_i - cols])
      FindPreviousStep(i - 1, j, &current_point);
    if (!horizontal_borders_[j + index_i])
      FindPreviousStep(i + 1, j, &current_point);
    if (j && !vertical_borders_[j + index_i - 1])
      FindPreviousStep(i, j - 1, &current_point);
    if (!vertical_borders_[j + index_i])
      FindPreviousStep(i, j + 1, &current_point);
    solving_.insert(solving_.begin(), current_point);
    --count_step_;
    if (!count_step_)
      count_step_ = static_cast<int>(kStart);
  }
}

void FindWay::FindPreviousStep(size_t i, size_t j,
                               std::pair<size_t, size_t> *current) {
  if (i < static_cast<size_t>(labyrinth_matrix_->get_rows()) &&
      j < static_cast<size_t>(labyrinth_matrix_->get_cols()) &&
      static_cast<int>((*labyrinth_matrix_)(i, j)) == count_step_)
    (*current) = std::make_pair(i, j);
}
