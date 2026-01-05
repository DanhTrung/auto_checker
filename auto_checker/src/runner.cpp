#include "checker/runner.hpp"
#include "checker/config.hpp"
#include "checker/colors.hpp"
#include "checker/util.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace checker {

TestResult runSingleTest(const std::string &exePath,
                         const std::string &inputFile,
                         const std::string &expectedFile,
                         int id) {
    TestResult tr;
    tr.name = fs::path(inputFile).filename().string();
    tr.status = "FAIL";
    tr.reason = "";

    if (!fs::exists(expectedFile)) {
        tr.status = "NO_EXPECTED";
        tr.reason = "Không tìm thấy file output chuẩn";
        std::cout << COLOR_YELLOW << "    [NO_EXPECTED] "
                  << tr.name << COLOR_RESET << "\n";
        return tr;
    }

    std::string userOut = config::BUILD_DIR + "/user_output" + std::to_string(id) + ".txt";
    std::string errFile = config::BUILD_DIR + "/user_error"  + std::to_string(id) + ".txt";

    std::string cmdRun = "timeout " + std::to_string(config::TIME_LIMIT_SECONDS) + "s "
                         "\"" + exePath + "\" < \"" + inputFile +
                         "\" > \"" + userOut + "\" 2>\"" + errFile + "\"";

    int exitCode = 0;
    bool ok = runCommandGetCode(cmdRun, exitCode);

    if (!ok) {
        if (exitCode == 124) {
            tr.status = "TIMEOUT";
            tr.reason = "Quá thời gian " + std::to_string(config::TIME_LIMIT_SECONDS) + "s";
            std::cout << COLOR_YELLOW << "    [TIMEOUT] "
                      << tr.name << COLOR_RESET << "\n";
        } else {
            tr.status = "RUNTIME_ERROR";
            tr.reason = "Exit code " + std::to_string(exitCode);
            std::cout << COLOR_RED << "    [RUNTIME_ERROR] "
                      << tr.name << " (exit " << exitCode << ")" << COLOR_RESET << "\n";
        }
        return tr;
    }

    std::string cmdDiff = "diff -q \"" + userOut + "\" \"" + expectedFile + "\" > /dev/null";
    int diffCode = 0;
    bool same = runCommandGetCode(cmdDiff, diffCode);

    if (same) {
        tr.status = "PASS";
        std::cout << COLOR_GREEN << "    [PASS] " << tr.name << COLOR_RESET << "\n";
    } else {
        tr.status = "FAIL";
        tr.reason = "Output khác đáp án";
        std::cout << COLOR_RED << "    [FAIL] " << tr.name << COLOR_RESET << "\n";
    }

    return tr;
}

} // namespace checker
