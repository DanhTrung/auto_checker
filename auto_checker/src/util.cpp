#include "checker/util.hpp"
#include <cstdlib>
#include <sys/wait.h>

namespace checker {

bool endsWith(const std::string &s, const std::string &suffix) {
    if (s.size() < suffix.size()) return false;
    return s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool runCommandGetCode(const std::string &cmd, int &exitCode) {
    int ret = std::system(cmd.c_str());
    if (ret == -1) {
        exitCode = -1;
        return false;
    }
    if (WIFEXITED(ret)) exitCode = WEXITSTATUS(ret);
    else exitCode = -1;
    return (exitCode == 0);
}

} // namespace checker
