#pragma once
#include <string>
#include <utility>
#include <vector>

namespace checker {

// trả về list (inputFile, expectedOutputFile)
std::vector<std::pair<std::string, std::string>> getTestCases();

} // namespace checker
