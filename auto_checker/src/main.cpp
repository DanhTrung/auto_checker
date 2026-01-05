#include "checker/colors.hpp"
#include "checker/util.hpp"
#include "checker/testcases.hpp"
#include "checker/submission.hpp"
#include "checker/report.hpp"

#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    std::string submissionsDir = "submissions";
    if (argc >= 2) submissionsDir = argv[1];

    std::cout << COLOR_CYAN
              << "=== AUTO CODE CHECKER (MODULAR, COLOR, TLE, JSON) ==="
              << COLOR_RESET << "\n";

    if (!fs::exists(submissionsDir)) {
        std::cout << COLOR_RED << "[ERROR] Không tìm thấy thư mục submissions: "
                  << submissionsDir << COLOR_RESET << "\n";
        return 1;
    }

    auto cases = checker::getTestCases();
    if (cases.empty()) {
        std::cout << COLOR_YELLOW
                  << "[WARN] Không tìm thấy test case hợp lệ trong thư mục tests/"
                  << COLOR_RESET << "\n";
        return 0;
    }

    std::vector<std::string> submissions;
    for (const auto &entry : fs::directory_iterator(submissionsDir)) {
        if (!entry.is_regular_file()) continue;
        std::string path = entry.path().string();
        if (checker::endsWith(path, ".c") || checker::endsWith(path, ".cpp") ||
            checker::endsWith(path, ".cc") || checker::endsWith(path, ".cxx")) {
            submissions.push_back(path);
        }
    }

    if (submissions.empty()) {
        std::cout << COLOR_YELLOW
                  << "[WARN] Không có file .c/.cpp nào trong thư mục submissions/"
                  << COLOR_RESET << "\n";
        return 0;
    }

    std::vector<checker::FileResult> allResults;
    for (const auto &subPath : submissions) {
        allResults.push_back(checker::processSubmission(subPath, cases));
    }

    // Summary
    int totalFiles = (int)allResults.size();
    int filesAllPass = 0, filesCompileErr = 0, filesWrong = 0;

    for (const auto &fr : allResults) {
        if (!fr.compileOk) filesCompileErr++;
        else if (fr.total > 0 && fr.passed == fr.total) filesAllPass++;
        else filesWrong++;
    }

    std::cout << COLOR_CYAN << "\n=== SUMMARY ===" << COLOR_RESET << "\n";
    std::cout << "  Tổng số file chấm: " << totalFiles << "\n";
    std::cout << COLOR_GREEN << "  File ĐÚNG  (pass hết test): " << filesAllPass << COLOR_RESET << "\n";
    std::cout << COLOR_RED   << "  File SAI   (sai test):       " << filesWrong << COLOR_RESET << "\n";
    std::cout << COLOR_RED   << "  File LỖI   (compile error):  " << filesCompileErr << COLOR_RESET << "\n";

    std::cout << "\n  Danh sách file ĐÚNG:\n";
    for (const auto &fr : allResults)
        if (fr.compileOk && fr.total > 0 && fr.passed == fr.total)
            std::cout << COLOR_GREEN << "    - " << fr.filePath << COLOR_RESET << "\n";

    std::cout << "\n  Danh sách file SAI:\n";
    for (const auto &fr : allResults)
        if (fr.compileOk && (fr.total == 0 || fr.passed < fr.total))
            std::cout << COLOR_RED << "    - " << fr.filePath
                      << " (" << fr.passed << "/" << fr.total << " test PASS)"
                      << COLOR_RESET << "\n";

    std::cout << "\n  Danh sách file COMPILE ERROR:\n";
    for (const auto &fr : allResults)
        if (!fr.compileOk)
            std::cout << COLOR_RED << "    - " << fr.filePath << COLOR_RESET << "\n";

    checker::writeJsonReport(allResults);
    return 0;
}
