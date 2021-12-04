#include "dbi.hpp"

bool queryCheckDB(std::string connection, std::string dbToConnect, std::string dbToCheck)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    pqxx::result r = wrk.exec((std::string) "SELECT check_db(\'" + dbToCheck + "\');");
    wrk.commit();
    return r.begin()[0].as<bool>();
}

void queryCreateDB(std::string connection, std::string dbToConnect, std::string dbToCreate)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    wrk.exec("SELECT create_db(\'" + dbToCreate + "\');");
    wrk.commit();
}

void queryDropDB(std::string connection, std::string dbToConnect, std::string dbToDrop)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    wrk.exec("SELECT drop_db(\'" + dbToDrop + "\');");
    wrk.commit();
}

void queryAddGuest(std::string connection, std::string dbToConnect,
                   std::string last_name, std::string first_name, std::string patronymic,
                   std::string passport_series, std::string passport_number, std::string phone)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    wrk.exec((std::string) "SELECT insert_guest(\'" +
             last_name + "\', \'" + first_name + "\', \'" + patronymic + "\', \'" +
             passport_series + "\', \'" + passport_number + "\', \'" + phone + "\')");
    wrk.commit();
}
/*
std::string queryPrintGuests(std::string connection, std::string dbToConnect)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    pqxx::result r = wrk.exec("SELECT * FROM print_table(NULL::guest);");
    wrk.commit();
    std::string strOut;
    for(pqxx::result::const_iterator it = r.cbegin(); it != r.cend(); ++it) {
        for(pqxx::row_size_type column = 0; column < r.columns(); ++column) {
            strOut = strOut + it[column].c_str() + ' ';
        }
        strOut = strOut + '\n';
    }
    return strOut;
}*/

std::vector<std::vector<std::string>> queryPrintGuests(std::string connection, std::string dbToConnect)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    pqxx::result r = wrk.exec("SELECT * FROM print_table(NULL::guest);");
    wrk.commit();
    std::vector<std::vector<std::string>> tbl;
    for(pqxx::result::const_iterator it = r.cbegin(); it != r.cend(); ++it) {
        std::vector<std::string> row;
        for(pqxx::row_size_type column = 0; column < r.columns(); ++column) {
            row.push_back(it[column].c_str());
        }
        tbl.push_back(row);
    }
    return tbl;
}

void queryDeleteGuest(std::string connection, std::string dbToConnect,
                      std::string last_name, std::string first_name)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    wrk.exec((std::string) "SELECT delete_guest(\'" + last_name + "\', \'" + first_name + "\')");
    wrk.commit();
}
