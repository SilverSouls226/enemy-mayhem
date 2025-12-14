#ifndef TEXTTABLE_H
#define TEXTTABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class TextTable {
public:
    TextTable(char horizontal = '-', char vertical = '|', char corner = '+')
        : _horizontal(horizontal), _vertical(vertical), _corner(corner) {}

    void add(const std::string &content) {
        _current.push_back(content);
    }

    void endOfRow() {
        _rows.push_back(_current);
        _current.clear();
    }

    friend std::ostream &operator<<(std::ostream &stream, const TextTable &table) {
        std::vector<unsigned int> widths;
        for (auto &row : table._rows) {
            for (size_t i = 0; i < row.size(); i++) {
                if (i >= widths.size()) widths.emplace_back(0);
                widths[i] = std::max(widths[i], static_cast<unsigned int>(row[i].size()));
            }
        }

        auto printLine = [&]() {
            stream << table._corner;
            for (size_t i = 0; i < widths.size(); i++) {
                stream << std::string(widths[i] + 2, table._horizontal) << table._corner;
            }
            stream << "\n";
        };

        printLine();
        for (auto &row : table._rows) {
            stream << table._vertical;
            for (size_t i = 0; i < widths.size(); i++) {
                std::string content = i < row.size() ? row[i] : "";
                stream << " " << std::setw(widths[i]) << std::left << content << " " << table._vertical;
            }
            stream << "\n";
            printLine();
        }

        return stream;
    }

private:
    char _horizontal, _vertical, _corner;
    std::vector<std::vector<std::string>> _rows;
    std::vector<std::string> _current;
};

#endif // TEXTTABLE_H