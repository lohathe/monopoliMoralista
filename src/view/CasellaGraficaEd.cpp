/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include"CasellaGraficaEd.h"

QString string2QString(string);

CasellaGraficaEd::CasellaGraficaEd(QString sf, QString alb, QString tmb, CEdificabile * cas, const vector<GiocatoreGraf*> & pedine, QWidget * parent): CasellaGrafica(sf, cas, pedine, parent), casella(cas), albergo(new QPixmap(alb)), timbro(new QPixmap(tmb))
{}

void CasellaGraficaEd::paintEvent(QPaintEvent * e)
{
  QPainter painter(this);
  CasellaGrafica::paintEvent(e);

  if (casella->getProprietario()!=0)
    {
      painter.drawPixmap(QRect(0,30,120,70),*timbro);
	painter.setFont(QFont("AnyStyle", 12, QFont::Bold));
	
	  painter.rotate(-26);
	  painter.drawText(-35, 75, 120, 30, Qt::AlignHCenter, string2QString((casella->getProprietario())->getNomeGiocatore()));
	  painter.setFont(QFont("AnyStyle", 7, 7, true));
	  painter.rotate(26);
      if(casella->isEdificata())
	  painter.drawPixmap(QRect(90,0,30,30),*albergo);
    }
}

//elimino tutto quello che non si rimuove automaticamente e che non viene rimosso da
//~CasellaGrafica() che viene invocato automaticamente
CasellaGraficaEd::~CasellaGraficaEd()
{
  delete albergo;
  delete timbro;
}
