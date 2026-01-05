#pragma once
#include <string>

namespace checker {

bool endsWith(const std::string& s, const std::string& suffix);

// chạy command qua system() và lấy exit code (0 = ok)
bool runCommandGetCode(const std::string& cmd, int& exitCode);

} // namespace checker
