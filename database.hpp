#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <pqxx/pqxx>

class database
{
public:
    database(const char opt[]);
    database(const std::string &opt);
    ~database();
    pqxx::result query(const std::string &query_text);
    bool is_open();
protected:

private:
    pqxx::connection _connection;
};

#endif // DATABASE_HPP

