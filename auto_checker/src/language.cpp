#include "checker/language.hpp"
#include "checker/util.hpp"

namespace checker {

Lang detectLanguage(const std::string &path) {
    if (endsWith(path, ".c") && !endsWith(path, ".cpp"))
        return Lang::C;
    if (endsWith(path, ".cpp") || endsWith(path, ".cc") || endsWith(path, ".cxx"))
        return Lang::CPP;
    return Lang::UNKNOWN;
}

} // namespace checker
