#pragma once
#include <string>

namespace checker {

enum class Lang { C, CPP, UNKNOWN };

Lang detectLanguage(const std::string& path);

} // namespace checker
