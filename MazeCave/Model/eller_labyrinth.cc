#include "eller_labyrinth.h"
using namespace maze;

EllerLabyrinth::EllerLabyrinth(size_t rows, size_t cols)
    : rows_(rows), cols_(cols) {
  if (rows_ == 0 || cols_ == 0)
    throw std::out_of_range(
        "Input the right size of labyrinth: rows > 0 and cols > 0");
  if (rows_ > 50 || cols_ > 50)
    throw std::out_of_range(
        "Input the right size of labyrinth: rows and cols ");
  for (size_t i = 0; i < cols_; ++i)
    labyrinth_stroke_.push_back(0);
}

std::vector<size_t> EllerLabyrinth::GetVerticalBorders() {
  return vertical_borders_;
}

std::vector<size_t> EllerLabyrinth::GetHorizontalBorders() {
  return horizontal_borders_;
}

void EllerLabyrinth::GenerateLabyrinth() {
  for (size_t i = 0; i < rows_ - 1; ++i) {
    SetUniqueSet();
    SetVerticalBorder();
    SetHorizontalBorder();
    RefreshLabyrinthStroke();
  }
  AddLastStroke();
}

bool EllerLabyrinth::ChooseRandomMean() {
  std::random_device rd;
  std::uniform_int_distribution<int> uniform_dist(0, 1);
  bool mean = uniform_dist(rd);
  return mean;
}

int EllerLabyrinth::CountUniqueSet(size_t set_number) {
  int count = 0;
  for (size_t i = 0; i < cols_; ++i) {
    if (labyrinth_stroke_[i] == set_number)
      ++count;
  }
  return count;
}

int EllerLabyrinth::CountHorizontalBorder(size_t set_number) {
  int count = 0;
  for (size_t i = 0; i < cols_; ++i) {
    int index = GetFirstHorizontalBorderPrevStroke() + i;
    if (labyrinth_stroke_[i] == set_number && horizontal_borders_[index] == 1)
      ++count;
  }
  return count;
}

void EllerLabyrinth::MergeSet(size_t index, size_t set_number) {
  size_t next_set_number = labyrinth_stroke_[index + 1];
  for (size_t i = 0; i < cols_; ++i) {
    if (labyrinth_stroke_[i] == next_set_number)
      labyrinth_stroke_[i] = set_number;
  }
}

int EllerLabyrinth::GetFirstVeticalBorderPrevStroke() {
  return vertical_borders_.size() - cols_;
}

int EllerLabyrinth::GetFirstHorizontalBorderPrevStroke() {
  return horizontal_borders_.size() - cols_;
}

void EllerLabyrinth::SetUniqueSet() {
  for (size_t i = 0; i < cols_; ++i) {
    if (!labyrinth_stroke_[i]) {
      labyrinth_stroke_[i] = count_unique_set_;
      ++count_unique_set_;
    }
  }
}

void EllerLabyrinth::SetVerticalBorder() {
  for (size_t i = 0; i < cols_ - 1; ++i) {
    if (labyrinth_stroke_[i] == labyrinth_stroke_[i + 1] ||
        ChooseRandomMean() == true) {
      vertical_borders_.push_back(1);
    } else {
      vertical_borders_.push_back(0);
      MergeSet(i, labyrinth_stroke_[i]);
    }
  }
  vertical_borders_.push_back(1);
}

void EllerLabyrinth::SetHorizontalBorder() {
  for (size_t i = 0; i < cols_; ++i) {
    if (CountUniqueSet(labyrinth_stroke_[i]) != 1 && ChooseRandomMean() == true)
      horizontal_borders_.push_back(1);
    else
      horizontal_borders_.push_back(0);
  }
  for (size_t i = 0; i < cols_; ++i) {
    int index = GetFirstHorizontalBorderPrevStroke() + i;
    if (CountUniqueSet(labyrinth_stroke_[i]) ==
        CountHorizontalBorder(labyrinth_stroke_[i]))
      horizontal_borders_[index] = 0;
  }
}

void EllerLabyrinth::RefreshLabyrinthStroke() {
  for (size_t i = 0; i < cols_; ++i) {
    // delete set_number where bottom border was
    int index = GetFirstHorizontalBorderPrevStroke() + i;
    if (horizontal_borders_[index] == 1)
      labyrinth_stroke_[i] = 0;
  }
}

void EllerLabyrinth::AddLastStroke() {
  SetUniqueSet();
  SetVerticalBorder();
  // add bottom borders
  size_t k = cols_;
  while (k--)
    horizontal_borders_.push_back(1);
  // delete vertical border if k|n
  for (size_t i = 0; i < cols_ - 1; ++i) {
    int index = GetFirstVeticalBorderPrevStroke() + i;
    if (labyrinth_stroke_[i] != labyrinth_stroke_[i + 1] &&
        vertical_borders_[index] == 1) {
      vertical_borders_[index] = 0;
      MergeSet(i, labyrinth_stroke_[i]);
    }
  }
}
