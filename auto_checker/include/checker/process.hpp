cat > include/checker/process.hpp <<'EOF'
#pragma once

#include <string>
#include <vector>
#include "checker/types.hpp"

namespace checker {

/**
 * @brief Chạy một tiến trình con bằng fork/exec.
 *
 * - Hỗ trợ redirect stdin / stdout / stderr
 * - Chờ tiến trình kết thúc bằng waitpid
 * - Trả về exit code hoặc signal
 */
ProcResult runProcess(const std::vector<std::string>& args,
                      const char* stdin_path,
                      const char* stdout_path,
                      const char* stderr_path);

} // namespace checker
EOF
