 /*****************************
 *     GIOCATORE GRAFICO      *
 *         HEADER             * 
 *                            *
 *****************************/

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
