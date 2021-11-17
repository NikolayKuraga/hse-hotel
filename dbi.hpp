#ifndef DBI_HPP
#define DBI_HPP

#include <iostream>
#include <pqxx/pqxx>

#define CONNECTION_STRING "hostaddr = 127.0.0.1 \
                           port     = 5432      \
                           user     = client    \
                           password = client    \
                           dbname   = client    "

pqxx::result query(std::string strCnn = CONNECTION_STRING);

#endif//DBI_HPP
