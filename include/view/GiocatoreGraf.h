/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#ifndef GIOCATOREGRAF_H
#define GIOCATOREGRAF_H
#include<QPixmap>
#include<QString>

class GiocatoreGraf
{
 public:

   QPixmap * avatar_piccolo;

   QPixmap * avatar_grande;

  //pedina per le celle
  //immagine per il turno

   GiocatoreGraf(QString, QString);
   //costruttore

   ~GiocatoreGraf();
   //distruttore
};

#endif
