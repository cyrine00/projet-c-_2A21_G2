#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Projet2A14");
db.setUserName("azizallani");//inserer nom de l'utilisateur
db.setPassword("azizallani");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
