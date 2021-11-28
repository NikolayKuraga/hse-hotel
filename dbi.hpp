#ifndef DBI_HPP
#define DBI_HPP

#include <iostream>
#include <pqxx/pqxx>

#define CNN_STR_CLIENT   "hostaddr = 127.0.0.1 \
                          port     = 5432      \
                          user     = client    \
                          password = client    \
                          dbname   = client    "
#define CNN_STR_CLIENTDB "hostaddr = 127.0.0.1 \
                          port     = 5432      \
                          user     = client    \
                          password = client    \
                          dbname   = clientdb  "

bool queryCheckDB(std::string strCnn);
void queryCreateDB(std::string strCnn);
void queryDropDB(std::string strCnn);
void queryAddGuest(std::string strCnn, std::string first_name, std::string last_name, std::string patronimic,
                   std::string passport_series, std::string passport_number, std::string phone);

#endif//DBI_HPP
