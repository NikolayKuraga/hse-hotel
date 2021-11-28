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

void queryAddGuest(std::string strCnn, std::string last_name, std::string first_name, std::string patronymic,
                   std::string passport_series, std::string passport_number, std::string phone)
{
    pqxx::connection cnn(strCnn);
    pqxx::work wrk(cnn);
    wrk.exec((std::string) "SELECT insert_guest(\'" + last_name + "\', \'" + first_name + "\', \'" + patronymic + "\', \'" +
             passport_series + "\', \'" + passport_number + "\', \'" + phone + "\')");
    wrk.commit();
}
