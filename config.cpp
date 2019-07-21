#include "config.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <boost/algorithm/string/trim.hpp>

config::config()
    : m_name() {}

config::config(const std::string &name)
    : m_name(name) {
    try {
        init();
    } catch (...) {
        throw;
    }
}

void config::reset(const std::string &name) {
    m_data = {};
    m_name = name;
    try {
        init();
    } catch (...) {
        throw;
    }
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
    while (std::getline(in, line)) { // better dont touch this
        boost::algorithm::trim(line);
        auto equal_char_iter{std::find(line.begin(), line.end(), '=')};
        auto sharp_char_iter{std::find(line.begin(), line.end(), '#')};
        auto close_char_iter{std::find(line.begin(), line.end(), ']')};
        if (line.size() && line[0] == '[' && close_char_iter != line.end() &&
            std::distance(line.begin(), sharp_char_iter - 1) > 1 && close_char_iter < sharp_char_iter) {
            cur_section = std::string(line.begin() + 1, sharp_char_iter - 1);
        } else if (line[0] == '#' || line.size() == 0) {
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
