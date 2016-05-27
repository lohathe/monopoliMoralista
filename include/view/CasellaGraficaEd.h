/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/


#ifndef CASELLAGRAFICAED_H
#define CASELLAGRAFICAED_H

#include"CEdificabile.h"
#include"CasellaGrafica.h"

//eredita da CasellaGrafica e ridefinisce la funzione PaintEvent in modo che stampi
//l'albergo se il terreno è edificato

class CasellaGraficaEd: public CasellaGrafica
{
private:

  const CEdificabile * casella;
  QPixmap * albergo;
  QPixmap * timbro;
 public:
  CasellaGraficaEd(QString, QString, QString, CEdificabile *,const vector<GiocatoreGraf*> &, QWidget* =0);
  ~CasellaGraficaEd();
  virtual void paintEvent(QPaintEvent * e);
};

#endif
