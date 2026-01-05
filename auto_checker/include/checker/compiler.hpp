#pragma once
#include <string>

namespace checker {

// compile 1 source -> output exePath. return true nếu compile ok
bool compileSource(const std::string& submissionPath, std::string& exePath);

} // namespace checker
