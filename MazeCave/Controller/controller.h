#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <memory>

#include "../Model/eller_labyrinth.h"
#include "../Model/find_way.h"
#include "../Model/model_cave.h"
#include "../Model/parse_file.h"

namespace maze {

class Controller {
public:
  void OpenFile(std::string file_path);
  size_t GetRows();
  size_t GetColumns();
  std::pair<std::vector<size_t>, std::vector<size_t>> GetMaze();
  std::vector<size_t> GetCave();
  std::pair<std::vector<size_t>, std::vector<size_t>>
  GenerateIdealLabyrinth(size_t rows, size_t cols);
  std::vector<std::pair<size_t, size_t>>
  SolveLabyrinth(std::pair<size_t, size_t> start,
                 std::pair<size_t, size_t> finish, size_t rows, size_t cols,
                 std::pair<std::vector<size_t>, std::vector<size_t>> maze_map);
  void CreateCave(size_t rows, size_t cols, std::vector<size_t> cave_array);
  void GenerateCave(int row_value, int col_value, int chance_value);
  void StepDrawCave(int birth_value, int death_value);
  std::vector<size_t> GetCaveArray();
  void CheckMaze();
  void CheckCave();

private:
  std::unique_ptr<ParseFile> parse_file_;
  std::unique_ptr<EllerLabyrinth> ideal_labyrinth_;
  std::unique_ptr<ModelCave> model_cave_;
  std::unique_ptr<FindWay> solve_labyrinth_;
};

} // namespace maze

#endif // SRC_CONTROLLER_CONTROLLER_H_
