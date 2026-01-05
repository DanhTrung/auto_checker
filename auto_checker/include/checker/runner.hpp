#pragma once
#include <string>
#include "checker/types.hpp"

namespace checker {

// chạy 1 test case cho exePath, trả về TestResult
TestResult runSingleTest(const std::string& exePath,
                         const std::string& inputFile,
                         const std::string& expectedFile,
                         int id);

} // namespace checker
