#include "checker/testcases.hpp"
#include "checker/config.hpp"
#include "checker/colors.hpp"
#include "checker/util.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace checker {

std::vector<std::pair<std::string, std::string>> getTestCases() {
    std::vector<std::pair<std::string, std::string>> cases;

    if (!fs::exists(config::TEST_DIR)) {
        std::cout << COLOR_YELLOW << "[WARN] Không tìm thấy thư mục tests/."
                  << COLOR_RESET << "\n";
        return cases;
    }

    for (const auto &entry : fs::directory_iterator(config::TEST_DIR)) {
        std::string name = entry.path().filename().string();

        if (name.rfind("input", 0) == 0 && endsWith(name, ".txt")) {
            std::string suffix = name.substr(5);
            std::string inputFile  = config::TEST_DIR + "/input"  + suffix;
            std::string outputFile = config::TEST_DIR + "/output" + suffix;

            if (fs::exists(outputFile)) {
                cases.push_back({inputFile, outputFile});
            } else {
                std::cout << COLOR_YELLOW << "[WARN] Thiếu file output cho "
                          << inputFile << COLOR_RESET << "\n";
            }
        }
    }

    return cases;
}

} // namespace checker
