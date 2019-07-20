#include "database.hpp"
#include <exception>
#include <memory>
#include <mutex>

database::database(const std::string &opt)
    : _mutex()
    , _connection(opt.c_str()) {}

database::~database() {
    _connection.disconnect();
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
