#ifndef AVIS_H
#define AVIS_H
#include<QString>

class Avis
{
public:
    Avis();
    Avis(QString ,QString ,QString ,QString ,QString ,QString ,QString , QString ,QString ,QString );
    QString Acceuil_telephonique,Amabilite,Disponibilite,Espace_vert,Espace_jeux,Parking,recommandation,revisiter,positif,negatif;
    bool ajouter();

};

#endif // AVIS_H
