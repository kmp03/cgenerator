#include "database.hpp"
#include <exception>
#include <memory>
#include "custom_mutex.hpp"

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

pqxx::result database::query(const std::string &query_text)
{

    std::unique_ptr<pqxx::work> trans_obj = {};

    custom_mutex cmutex = {};
    cmutex.lock();
    try {
        trans_obj.reset(new  pqxx::work(_connection));
        pqxx::result response{trans_obj->exec(query_text)} ;
        trans_obj->commit();
        cmutex.unlock();
        return response;
    } catch (...) {
       if (trans_obj) trans_obj->abort();
       cmutex.unlock();
       throw;
    }
}


bool database::is_open()
{
    return _connection.is_open();
}

