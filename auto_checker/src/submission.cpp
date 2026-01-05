#include "checker/submission.hpp"
#include "checker/colors.hpp"
#include "checker/compiler.hpp"
#include "checker/runner.hpp"

#include <iostream>

namespace checker {

FileResult processSubmission(const std::string &submissionPath,
                             const std::vector<std::pair<std::string, std::string>> &cases) {
    FileResult fr;
    fr.filePath = submissionPath;

    std::cout << COLOR_CYAN << "\n[FILE] " << submissionPath << COLOR_RESET << "\n";

    std::string exePath;
    if (!compileSource(submissionPath, exePath)) {
        fr.compileOk = false;
        fr.total = 0;
        fr.passed = 0;
        std::cout << COLOR_RED << "  => Bỏ qua file này vì COMPILE ERROR."
                  << COLOR_RESET << "\n";
        return fr;
    }

    int testId = 1;
    for (const auto &tc : cases) {
        fr.total++;
        TestResult tr = runSingleTest(exePath, tc.first, tc.second, testId++);
        fr.tests.push_back(tr);
        if (tr.status == "PASS") fr.passed++;
    }

    std::cout << "  => Kết quả: "
              << fr.passed << "/" << fr.total << " test PASS\n";

    return fr;
}

} // namespace checker
