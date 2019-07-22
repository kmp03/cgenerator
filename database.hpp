#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <pqxx/pqxx>
#include <mutex>
#include "config.hpp"

class database {
public:
    database(const std::string &opt);
    database(const config &cfg);
    ~database();
    pqxx::result query(const std::string &query_text);

protected:
private:
    std::mutex _mutex;
    pqxx::connection _connection;

    std::string config_to_string(const config &cfg);
};

#endif // DATABASE_HPP
