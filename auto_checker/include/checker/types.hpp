#pragma once
#include <string>
#include <vector>

namespace checker {

struct TestResult {
    std::string name;     // input1.txt
    std::string status;   // PASS / FAIL / TIMEOUT / RUNTIME_ERROR / NO_EXPECTED
    std::string reason;   // mô tả thêm nếu cần
};

struct FileResult {
    std::string filePath;           // submissions/main.c
    bool compileOk = true;          // compile được hay không
    int passed = 0;
    int total  = 0;
    std::vector<TestResult> tests;
};

} // namespace checker
