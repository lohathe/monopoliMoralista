/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include "Bolla.h"

Andata::Andata(Andata::Tipo t, Giocatore *g, CBase *c, int opz, int cs, int att, int lim, int tot): tipo(t), giocatore(g), casella(c), costo(cs), attuale(att), limite(lim), totale(tot) {

  for(int i=0; i<4; i++)
    edificabili[i] = false;

  edificabili[opz] = true;

}

Andata::~Andata() {}

Ritorno::Ritorno(Giocatore *g, int n, int v): giocatore(g), value(v) {

  for(int i=0; i<5; i++)
    operazioni[i] = false;

  if(n!=-1)
    operazioni[n] = true;

}

Ritorno::~Ritorno() {}

