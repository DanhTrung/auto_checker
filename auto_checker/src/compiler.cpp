#include "checker/compiler.hpp"
#include "checker/config.hpp"
#include "checker/colors.hpp"
#include "checker/language.hpp"
#include "checker/util.hpp"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace checker {

bool compileSource(const std::string &submissionPath, std::string &exePath) {
    fs::create_directories(config::BUILD_DIR);
    exePath = config::BUILD_DIR + "/" + config::EXE_NAME;

    Lang lang = detectLanguage(submissionPath);
    std::string cmd;

    if (lang == Lang::C) {
        cmd = "gcc \"" + submissionPath + "\" -o \"" + exePath + "\" -O2 -std=c11";
    } else if (lang == Lang::CPP) {
        cmd = "g++ \"" + submissionPath + "\" -o \"" + exePath + "\" -O2 -std=c++17";
    } else {
        std::cout << COLOR_RED << "[ERROR] Không nhận diện được ngôn ngữ file: "
                  << submissionPath << COLOR_RESET << "\n";
        return false;
    }

    std::cout << COLOR_CYAN << "  -> Compiling: " << cmd << COLOR_RESET << "\n";

    int exitCode = 0;
    bool ok = runCommandGetCode(cmd, exitCode);
    if (!ok) {
        std::cout << COLOR_RED << "  => COMPILE ERROR (exit code "
                  << exitCode << ")" << COLOR_RESET << "\n";
        return false;
    }
    return true;
}

} // namespace checker
