#include "config.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

//#include <boost/spirit/include/classic.hpp>
//#include <boost/spirit/include/qi.hpp>

config::config()
    : m_name() {
    init();
}

config::config(const std::string &name)
    : m_name(name) {
    init();
}

void config::reset(const std::string &name) {
    m_data = {};
    m_name = name;
    init();
}

/*
 * this method fills m_data
 */
void config::init() {
    std::ifstream in(m_name);
    if (!in.is_open()) {
        throw "cant open file";
    }
    std::string line;
    std::string cur_section{};
    while (std::getline(in, line)) {
        auto equal_char_iter{std::find(line.begin(), line.end(), '=')};
        auto sharp_char_iter{std::find(line.begin(), line.end(), '#')};
        if (line.size() && line[0] == '[' && std::find(line.begin(), line.end(), ']') != line.end() &&
            std::distance(line.begin(), sharp_char_iter - 1) > 1) {
            cur_section = std::string(line.begin() + 1, sharp_char_iter - 1);
        } else if ((sharp_char_iter != line.end() && equal_char_iter == line.end()) || line.size() == 0) {
            // do nothing
        } else if (line.size() && equal_char_iter != line.end()) {
            std::string param(line.begin(), equal_char_iter);
            std::string value(equal_char_iter + 1, sharp_char_iter);
            if (!(param.size() && value.size() && cur_section.size())) {
                throw "bad config";
            }
            m_data[cur_section][param] = value;
        } else {
            throw "bad config";
        }
    }
}

config::table_type config::get() const {
    return m_data;
}
