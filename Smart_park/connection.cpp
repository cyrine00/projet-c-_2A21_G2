#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test=false;
 QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("SOURCE_PROJET2A");
db.setUserName("hamza");
db.setPassword("hamza");

if (db.open()) test=true;





    return  test;
}
