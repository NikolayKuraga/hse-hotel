#include "dbi.hpp"

bool queryCheckDB(std::string strCnn)
{
    pqxx::connection cnn(strCnn);
    pqxx::work wrk(cnn);
    pqxx::result r = wrk.exec("SELECT check_db();");
    wrk.commit();
    return r.begin()[0].as<bool>();
}

void queryCreateDB(std::string strCnn)
{
    pqxx::connection cnn(strCnn);
    pqxx::work wrk(cnn);
    wrk.exec("SELECT create_db();");
    wrk.commit();
}

void queryDropDB(std::string strCnn)
{
    pqxx::connection cnn(strCnn);
    pqxx::work wrk(cnn);
    wrk.exec("SELECT drop_db();");
    wrk.commit();
}
