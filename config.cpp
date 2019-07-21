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
        if (line.size() && line[0] == '[') {
            cur_section = std::string(line.begin() + 1, line.end() - 1);
        } else if (line.size()) {
            std::string param(line.begin(), std::find(line.begin(), line.end(), '='));
            std::string value(std::find(line.begin(), line.end(), '=') + 1, line.end());
            if (!(param.size() && value.size() && cur_section.size())) {
                throw "bad config";
            }
            m_data[cur_section][param] = value;
        }
    }
}

config::table_type config::get() const {
    return m_data;
}
