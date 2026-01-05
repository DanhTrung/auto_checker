#pragma once
#include <string>
#include <utility>
#include <vector>
#include "checker/types.hpp"

namespace checker {

// xử lý 1 file submission (compile + chạy tất cả test)
FileResult processSubmission(const std::string& submissionPath,
                             const std::vector<std::pair<std::string, std::string>>& cases);

} // namespace checker
