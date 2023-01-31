#ifndef SRC_MODEL_ELLER_LABYRINTH_H_
#define SRC_MODEL_ELLER_LABYRINTH_H_

#include <iostream>
#include <random>
#include <vector>

namespace maze {
class EllerLabyrinth {
public:
  EllerLabyrinth() {}
  EllerLabyrinth(size_t rows, size_t cols);
  EllerLabyrinth(const EllerLabyrinth &other) = default;
  EllerLabyrinth(EllerLabyrinth &&other) = default;
  EllerLabyrinth &operator=(const EllerLabyrinth &other) = default;
  EllerLabyrinth &operator=(EllerLabyrinth &&other) = default;
  ~EllerLabyrinth() {}
  std::vector<size_t> GetVerticalBorders();
  std::vector<size_t> GetHorizontalBorders();
  void GenerateLabyrinth();

private:
  size_t rows_;
  size_t cols_;
  size_t count_unique_set_ = 1;
  std::vector<size_t> vertical_borders_;
  std::vector<size_t> horizontal_borders_;
  std::vector<size_t> labyrinth_stroke_;
  bool ChooseRandomMean();
  int CountUniqueSet(size_t set_number);
  int CountHorizontalBorder(size_t set_number);
  int GetFirstVeticalBorderPrevStroke();
  int GetFirstHorizontalBorderPrevStroke();
  void MergeSet(size_t index, size_t set_number);
  void SetUniqueSet();
  void SetVerticalBorder();
  void SetHorizontalBorder();
  void RefreshLabyrinthStroke();
  void AddLastStroke();
};
} // namespace maze
#endif // SRC_MODEL_ELLER_LABYRINTH_H_
