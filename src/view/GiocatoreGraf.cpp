/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include"GiocatoreGraf.h"

GiocatoreGraf::GiocatoreGraf(QString percorso1, QString percorso2):  avatar_piccolo(new QPixmap(percorso1)), avatar_grande(new QPixmap(percorso2))
{}

//distruttore, elimina le pixmaps
GiocatoreGraf::~GiocatoreGraf()
{
  delete avatar_piccolo;
  delete avatar_grande;
}
