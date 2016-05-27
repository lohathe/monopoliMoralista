/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include"TavoloDaGioco.h"

TavoloDaGioco::TavoloDaGioco(TurnoGrafico * tur, vector<CasellaGrafica *> & cas, InfoGiocatori * i): QWidget(0),  t(tur), caselle(cas), Info(i)
{
  setWindowTitle("Monopoly");
  setFixedSize(1020,700);
  
  QGridLayout * lay=new QGridLayout();
  
  connect(t, SIGNAL(chiudi()), this, SLOT(close()));
  connect(t, SIGNAL(aggiornaInfoGiocatori(int)), Info, SLOT(abilitaGiocatore(int)));
  
  Info->show();
  
  lay->addWidget(t,1,2,3,5);
  lay->addWidget(Info, 0, 0, 5, 1);

  int cont=0;
  while(cont<20)
    {
  
   for (int i =0; i<7; ++i)
    {
      lay->addWidget(caselle[cont],0,i+1,1,1);
      cont++;
    }
  for (int j=1; j<5; ++j)
    {
      lay->addWidget(caselle[cont],j,7,1,1);
    cont++;
    }
  for (int k=5; k>-1; --k)
    {
      lay->addWidget(caselle[cont],4,k+1,1,1);
      cont++;
    }
  for (int l=3; l>0; --l)
    {
      lay->addWidget(caselle[cont],l,1,1,1);
      cont++;
    }
    }
  setLayout(lay);
}

