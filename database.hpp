#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <pqxx/pqxx>

class database
{
private:
    pqxx::connection _connection;
public:
    database(const char opt[]);
    database(const std::string &opt);
    ~database();
    pqxx::result query(const char query_text[]);
    pqxx::result query(const std::string &query_text);
    bool is_open()
    {
        return _connection.is_open();
    }
};

#endif // DATABASE_HPP

