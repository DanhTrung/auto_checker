#pragma once
#include <vector>
#include "checker/types.hpp"

namespace checker {

// ghi report.json
void writeJsonReport(const std::vector<FileResult>& results);

} // namespace checker
