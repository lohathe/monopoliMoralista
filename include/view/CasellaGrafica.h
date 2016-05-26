/**************************
 *     CASELLA GRAFICA    *
 *        HEADER          *
 *                        *
 *************************/

#ifndef CELLAGRAFICA_H
#define CELLAGRAFICA_H

#include<QWidget>
#include"CBase.h"
#include<QPainter>
#include"GiocatoreGraf.h"

class CasellaGrafica: public QWidget
{
private:
  const CBase * casella;
    //puntatore alla casella logica per fare il display
  //del nome e dei giocatori presenti sulla casella
  
  vector<GiocatoreGraf*> pedine;
  //array dei giocatori grafici usato per fare il display delle
  //pedine presenti sulla cella

  QPixmap * sfondo;
 public:

  //andrebbe messa protetta ma la usa turno grafico per costruire il popup 
  QPixmap * sfondoGrande;
  //sfondo della casella
 
  CasellaGrafica(QString, CBase*, const vector<GiocatoreGraf *> &, QWidget * =0);
  //costruttore che prende una stringa, un puntatore alla cella logica
  //che rappresenta, l'array dei giocatori grafici e il puntatore al padre

  virtual ~CasellaGrafica();
  
  virtual void paintEvent(QPaintEvent *);
  //si preoccupa di disegnare la pixmap di sfondo nel posto prestabilito
};

#endif
