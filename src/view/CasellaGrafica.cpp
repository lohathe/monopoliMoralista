/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include"CasellaGrafica.h"
#include<QPixmap>
#include<QLabel>

QString string2QString(string);

CasellaGrafica::CasellaGrafica(QString s,CBase * c, const vector<GiocatoreGraf *>& ped, QWidget * Parent): QWidget(Parent), casella(c), pedine(ped), sfondo(new QPixmap(s)), sfondoGrande(new QPixmap(s + "G"))
{
  setFixedSize(120,130);
  //fissa la dimensione della cella
}

void CasellaGrafica::paintEvent(QPaintEvent * /*e*/)
{
  QPainter painter(this);
  painter.setFont(QFont("AnyStyle", 7, 7, true));
  painter.drawText(QRect(5,10,120,20),Qt::AlignLeft,string2QString(casella->getNomeCasella()));
  painter.drawPixmap(QRect(0,30,120,100),*sfondo, QRect(0,0,120,100));
  //painter.fillRect(QRect(0,100,120,30), Qt::white);
  vector<bool>::const_iterator it=casella->presenti.begin();
  for (int i=0; it<casella->presenti.end(); ++i, ++it)
    {
      if (*it)
	{
	  painter.drawPixmap(QRect((0+29*i),94,35,35),*(pedine[i]->avatar_piccolo));
	}
    }
    //disegnamo uno ad uno le pedine dei giocatori che si trovano sulla cella
    //logica, sappiamo se un giocatore si trova sulla cella ispezionando
    //l'array booleano "presenti" della cella logica stessa
  painter.drawRect(QRect(0,0,119,129));
}

CasellaGrafica::~CasellaGrafica()
{

delete sfondo;
delete sfondoGrande;
}
