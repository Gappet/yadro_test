
#pragma once
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Sheet.h"

class ErrorFormatTable : public std::invalid_argument {
 public:
  using std::invalid_argument::invalid_argument;
};

class CSVReader {
 public:
  CSVReader(std::string& filename);

  std::shared_ptr<Sheet> convSheet() const;

 private:
  std::vector<std::pair<std::string, std::vector<std::string>>> table_;
};
