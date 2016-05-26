#include "Dado.h"
#include<QPainter>

//-----------------CPP Dado--------------------------

Dado::Dado(QWidget * p, bool truccato): QWidget(p), pic(new QPixmap(":/immagini/dado/faccia1.gif")),  lancia(new QPushButton(tr("Lancia!"), this)), risultato(1)
{
  this->setFixedSize(200,75);
  lancia->setGeometry(20,25,100,50);
  if(truccato)
   connect(lancia,SIGNAL(clicked()),this,SLOT(mostraTruccato()));
  else
   connect(lancia,SIGNAL(clicked()),this,SLOT(mostra()));
}

void Dado::paintEvent(QPaintEvent */* e*/)
{
  QPainter painter(this);
  painter.drawPixmap(QRect(130,25,50,50),*pic, QRect(0,0,50,50));
}

void Dado::mostra()
{
  lancia->setDisabled(true);
  risultato=rand()%6+1;
  delete pic;
  QString percorso = ":/immagini/dado/facciax.gif";
  percorso[22]='0'+risultato;
  pic=new QPixmap(percorso);
  this->update();
  emit lanciato(risultato);
}

void Dado::mostraTruccato()
{
  lancia->setDisabled(true);
  emit lanciato(risultato);
}

Dado::~Dado()
{
  delete pic;
}

//usato da turno quando tocca ad un nuovo giocatore
void Dado::abilitaLancio()
{
  lancia->setDisabled(false);
}

void Dado::disabilitaLancio()
{
  lancia->setDisabled(true);
}
