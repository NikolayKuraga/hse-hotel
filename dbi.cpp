#include "dbi.hpp"

pqxx::result query(std::string strCnn)
{
    pqxx::connection cnn(strCnn);
    pqxx::work wrk(cnn);
    pqxx::result r = wrk.exec("SELECT * FROM list");
    wrk.commit();
    return r;
}
