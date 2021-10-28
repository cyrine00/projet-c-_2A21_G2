#include "connection.h"

Connection::Connection()
{
}

bool Connection::createconnection()
{
db = QSqlDatabase::addDatabase("QODBC");

bool test=false;
db.setDatabaseName("gestion_cl");
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("1202");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}
void Connection::closeConnection()
{db.close();}
