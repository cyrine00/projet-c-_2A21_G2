#include "avis.h"
#include<QSqlQuery>
#include<QtDebug>

Avis::Avis()
{
    Acceuil_telephonique="";
    Amabilite="";
    Disponibilite="";
    Espace_vert="";
    Espace_jeux="";
    Parking="";
    recommandation="";
    revisiter="";
    positif="";
    negatif="";

}

Avis::Avis(QString Acceuil_telephonique,QString Amabilite,QString Disponibilite,QString Espace_vert,QString Espace_jeux,QString Parking,QString recommandation, QString revisiter,QString positif,QString negatif)
{
    this->Acceuil_telephonique=Acceuil_telephonique;
    this->Amabilite=Amabilite;
    this->Disponibilite=Disponibilite;
    this->Espace_vert=Espace_vert;
    this->Espace_jeux=Espace_jeux;
    this->Parking=Parking;
    this->recommandation=recommandation;
    this->revisiter=revisiter;
    this->positif=positif;
    this->negatif=negatif;

}
bool Avis::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO AVIS (Acceuil_telephonique, Amabilite, Disponibilite,Espace_vert,Espace_jeux,Parking,recommandation,revisiter,positif,negatif) ");
    query.bindValue(0, Acceuil_telephonique);
    query.bindValue(1, Amabilite);
    query.bindValue(2, Disponibilite);
    query.bindValue(3, Espace_vert);
    query.bindValue(4, Espace_jeux);
    query.bindValue(5, Parking);
    query.bindValue(6, recommandation);
    query.bindValue(7, revisiter);
    query.bindValue(8, positif);
    query.bindValue(9, negatif);

    return query.exec();

}
