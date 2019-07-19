#include "database.hpp"
#include <exception>

database::database(const char opt[]) :
    _connection(opt)
{

}

database::database(const std::string &opt) :
    _connection(opt.c_str())
{

}

database::~database()
{
    _connection.disconnect();
}

pqxx::result database::query(const char query_text[])
{
    try {
        pqxx::work trans_obj (this->_connection);
        pqxx::result response {trans_obj.exec(query_text)} ;
        trans_obj.commit();
        return response;
    } catch (const std::exception &e) {
        return pqxx::result {};
    }
}

pqxx::result database::query(const std::string &query_text)
{
    return database::query(query_text.c_str());
}

