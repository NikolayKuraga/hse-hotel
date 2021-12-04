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

bool queryCheckDB(std::string connection, std::string dbToConnect, std::string dbToCheck);
void queryCreateDB(std::string connection, std::string dbToConnect, std::string dbToCreate);
void queryDropDB(std::string connection, std::string dbToConnect, std::string dbToDrop);
void queryAddGuest(std::string connection, std::string dbToConnect,
                   std::string lst_name, std::string fst_name, std::string patronimic,
                   std::string passport_series, std::string passport_number, std::string phone);
std::vector<std::vector<std::string>> queryPrintGuests(std::string connection, std::string dbToConnect);
//std::vector<std::vector<std::string>> queryPrintGuests_(std::string connection, std::string dbToConnect);
void queryDeleteGuest(std::string connection, std::string dbToConnect,
                      std::string lst_name, std::string fst_name);

#endif//DBI_HPP
