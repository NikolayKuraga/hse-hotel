#include "dbi.hpp"

// database queries
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

// queries for specified table
std::vector<std::vector<std::string>> queryPrintTable(std::string connection, std::string dbToConnect,
                                                      std::string tableName)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    pqxx::result r = wrk.exec((std::string) "SELECT * FROM print_table(NULL::" + tableName + ");");
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

bool queryDeleteRow(std::string connection, std::string dbToConnect,
                    std::string table, std::string column, std::string key)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    pqxx::result r = wrk.exec((std::string) "SELECT delete_row(\'" +
                              table + "\', \'" + column + "\', \'" + key + "\')");
    wrk.commit();
    return r.begin()[0].as<bool>();
}

// booking queries
void queryAddBook(std::string connection, std::string dbToConnect,
                  std::string book_id, std::string arrival, std::string departure,
                  std::string book_date, std::string room_id, std::string total_cost,
                  std::string bank_card)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    pqxx::result r = wrk.exec((std::string) "");
    wrk.commit();
}

// room queries
void queryAddRoom(std::string connection, std::string dbToConnect,
                  std::string room_id, std::string price_per_day, std::string num_of_rooms,
                  std::string area, std::string service_class, std::string kitchen)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    wrk.exec((std::string) "SELECT insert_hotel_room(\'" +
             room_id + "\', \'" + price_per_day + "\', \'" + num_of_rooms + "\', \'" +
             area + "\', \'" + service_class + "\', \'" + kitchen + "\')");
    wrk.commit();
}

// guest queries
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

bool queryDeleteGuestByName(std::string connection, std::string dbToConnect,
                            std::string last_name, std::string first_name)
{
    pqxx::connection cnn(connection + " dbname = " + dbToConnect);
    pqxx::work wrk(cnn);
    pqxx::result r = wrk.exec((std::string) "SELECT delete_guest_by_name(\'" + last_name + "\', \'" + first_name + "\')");
    wrk.commit();
    return r.begin()[0].as<bool>();
}

