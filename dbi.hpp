#ifndef DBI_HPP
#define DBI_HPP

#include <iostream>
#include <pqxx/pqxx>

// default connection to unspecified database
#define DF_CNN    " hostaddr = 127.0.0.1 \
                    port     = 5432      \
                    user     = client    \
                    password = client "
// default database name
#define DF_DB     " client "

// database queries
bool queryCheckDB(std::string connection, std::string dbToConnect, std::string dbToCheck);
void queryCreateDB(std::string connection, std::string dbToConnect, std::string dbToCreate);
void queryDropDB(std::string connection, std::string dbToConnect, std::string dbToDrop);

// queries for specified table
std::vector<std::vector<std::string>> queryPrintTable(std::string connection, std::string dbToConnect,
                                                      std::string tableName);
bool queryDeleteRow(std::string connection, std::string dbToConnect,
                    std::string table, std::string column, std::string key);

// room queries
void queryAddRoom(std::string connection, std::string dbToConnect,
                  std::string room_id, std::string price_per_day, std::string num_of_rooms,
                  std::string area, std::string service_class, std::string kitchen);

// guest queries
void queryAddGuest(std::string connection, std::string dbToConnect,
                   std::string lst_name, std::string fst_name, std::string patronimic,
                   std::string passport_series, std::string passport_number, std::string phone);
bool queryDeleteGuestByName(std::string connection, std::string dbToConnect,
                            std::string lst_name, std::string fst_name);

#endif//DBI_HPP
