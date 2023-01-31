#ifndef SRC_MODEL_PARSE_FILE_H_
#define SRC_MODEL_PARSE_FILE_H_

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace maze {

class ParseFile {
public:
  ParseFile() : rows_(0), columns_(0), map_(0){};
  ~ParseFile(){};
  ParseFile(ParseFile const &) = default;
  ParseFile(ParseFile &&) = default;
  ParseFile &operator=(ParseFile const &) = default;
  ParseFile &operator=(ParseFile &&) = default;
  void ReadData(std::string file_path);
  std::vector<size_t> GetMazeVert();
  std::vector<size_t> GetMazeHoriz();
  std::vector<size_t> GetCave();
  size_t GetRows();
  size_t GetColunms();
  void CheckMaze();
  void CheckCave();

private:
  size_t rows_;
  size_t columns_;
  std::vector<size_t> map_;
  void ClearVars();
};

} // namespace maze

#endif // SRC_MODEL_PARSE_FILE_H_
