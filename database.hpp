#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <pqxx/pqxx>
#include <mutex>

class database {
public:
    database(const std::string &opt);
    ~database();
    pqxx::result query(const std::string &query_text);

protected:
private:
    std::mutex _mutex;
    pqxx::connection _connection;
};

#endif // DATABASE_HPP
