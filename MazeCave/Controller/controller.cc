#include "controller.h"
using namespace maze;

void Controller::OpenFile(std::string file_path) {
  parse_file_ = std::make_unique<ParseFile>();
  parse_file_->ReadData(file_path);
}

std::pair<std::vector<size_t>, std::vector<size_t>> Controller::GetMaze() {
  return std::make_pair(parse_file_->GetMazeVert(),
                        parse_file_->GetMazeHoriz());
}

std::vector<size_t> Controller::GetCave() { return parse_file_->GetCave(); }

size_t Controller::GetRows() { return parse_file_->GetRows(); }

size_t Controller::GetColumns() { return parse_file_->GetColunms(); }

std::pair<std::vector<size_t>, std::vector<size_t>>
Controller::GenerateIdealLabyrinth(size_t rows, size_t cols) {
  ideal_labyrinth_ = std::make_unique<EllerLabyrinth>(rows, cols);
  ideal_labyrinth_->GenerateLabyrinth();
  return std::make_pair(ideal_labyrinth_->GetVerticalBorders(),
                        ideal_labyrinth_->GetHorizontalBorders());
}

std::vector<std::pair<size_t, size_t>> Controller::SolveLabyrinth(
    std::pair<size_t, size_t> start, std::pair<size_t, size_t> finish,
    size_t rows, size_t cols,
    std::pair<std::vector<size_t>, std::vector<size_t>> maze_map) {
  solve_labyrinth_ = std::make_unique<FindWay>();
  solve_labyrinth_->SetStartPosition(start);
  solve_labyrinth_->SetFinishPosition(finish);
  auto result = solve_labyrinth_->SolveLabyrinth(rows, cols, maze_map.first,
                                                 maze_map.second);
  return result;
}

void Controller::CreateCave(size_t rows, size_t cols,
                            std::vector<size_t> cave_array) {
  model_cave_ = std::make_unique<maze::ModelCave>(rows, cols, cave_array);
}
void Controller::GenerateCave(int row_value, int col_value, int chance_value) {
  if (model_cave_.get() == nullptr)
    model_cave_ = std::make_unique<maze::ModelCave>();
  model_cave_->GeneratorCave(row_value, col_value, chance_value);
}

std::vector<size_t> Controller::GetCaveArray() {
  return model_cave_->GetIndexArray();
}

void Controller::StepDrawCave(int birth_value, int death_value) {
  model_cave_->SetLimitBirth(birth_value);
  model_cave_->SetLimitDeath(death_value);
  model_cave_->NextState();
}

void Controller::CheckMaze() { parse_file_->CheckMaze(); }
void Controller::CheckCave() { parse_file_->CheckCave(); }
