#include "checker/report.hpp"
#include "checker/config.hpp"
#include "checker/colors.hpp"

#include <fstream>
#include <iostream>

namespace checker {

void writeJsonReport(const std::vector<FileResult> &results) {
    std::ofstream fout(config::REPORT_JSON);
    if (!fout) {
        std::cerr << COLOR_RED
                  << "[ERROR] Không ghi được file report.json"
                  << COLOR_RESET << "\n";
        return;
    }

    fout << "{\n";
    fout << "  \"submissions\": [\n";

    for (size_t i = 0; i < results.size(); ++i) {
        const auto &fr = results[i];

        std::string status;
        if (!fr.compileOk) status = "COMPILE_ERROR";
        else if (fr.total > 0 && fr.passed == fr.total) status = "OK";
        else status = "WRONG";

        fout << "    {\n";
        fout << "      \"file\": \"" << fr.filePath << "\",\n";
        fout << "      \"compile_ok\": " << (fr.compileOk ? "true" : "false") << ",\n";
        fout << "      \"status\": \"" << status << "\",\n";
        fout << "      \"passed\": " << fr.passed << ",\n";
        fout << "      \"total\": " << fr.total << ",\n";
        fout << "      \"tests\": [\n";

        for (size_t j = 0; j < fr.tests.size(); ++j) {
            const auto &tr = fr.tests[j];
            fout << "        {\n";
            fout << "          \"name\": \""   << tr.name   << "\",\n";
            fout << "          \"status\": \"" << tr.status << "\"";
            if (!tr.reason.empty()) {
                fout << ",\n          \"reason\": \"" << tr.reason << "\"\n";
            } else {
                fout << "\n";
            }
            fout << "        }";
            if (j + 1 < fr.tests.size()) fout << ",";
            fout << "\n";
        }

        fout << "      ]\n";
        fout << "    }";
        if (i + 1 < results.size()) fout << ",";
        fout << "\n";
    }

    fout << "  ]\n";
    fout << "}\n";

    std::cout << COLOR_CYAN << "\n[INFO] Đã ghi JSON report vào "
              << config::REPORT_JSON << COLOR_RESET << "\n";
}

} // namespace checker
