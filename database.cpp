#include "database.hpp"
#include <exception>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <string>

#include <iostream> // debug

database::database(const std::string &opt)
    : _mutex()
    , _connection(opt.c_str()) {}


database::database(const config &cfg)
    : _mutex()
    , _connection(config_to_string(cfg)) {}

database::~database() {
    _connection.disconnect();
}

std::string database::config_to_string(const config &cfg) {
    auto table{cfg.get()};
    const config::table_type::iterator &section{table.find("DATABASE")}; // const auto ...
    const std::unordered_map<std::string, std::string> &record{section->second}; // const auto ...

    /*
     * opt template for constructor connection
     * "dbname = testdb user = postgres password=pass123 host=127.0.0.1 port=5432"
     */

    /*
     * maybe better to create std::vector<std::string> of necessary params
     * and do .find(param) in a cycle?
     */
    if (section != table.end() && record.find("username") != section->second.end() &&
        record.find("password") != section->second.end() && record.find("host") != section->second.end() &&
        record.find("port") != section->second.end() && record.find("database_name") != section->second.end()) {
        std::string response{"dbname = " + record.at("database_name") + " "};
        response.append("user = " + record.at("username") + " ");
        response.append("password=" + record.at("password") + " ");
        response.append("host=" + record.at("host") + " ");
        response.append("port=" + record.at("port"));

        std::cout << response << std::endl; // DEBUG SUKA
        return response;

    } else {
        throw "unable to connect to database";
    }
}

pqxx::result database::query(const std::string &query_text) {
    std::unique_ptr<pqxx::work> trans_obj = {};
    std::lock_guard<std::mutex> guard(_mutex);
    try {
        trans_obj.reset(new pqxx::work(_connection));
        pqxx::result response{trans_obj->exec(query_text)};
        trans_obj->commit();
        return response;
    } catch (...) {
        if (trans_obj) trans_obj->abort();
        throw;
    }
}
