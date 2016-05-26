/*****************************************\
| CASELLA NON EDIFICABILE : VERSIONE BASE |
|                  header                 |
\*****************************************/

#include "CNEdificabile.h"

CNEdificabile::CNEdificabile(string nome, int ind, int numGiocatori): CBase(nome, ind, numGiocatori) { }


Andata CNEdificabile::sceltaOpzione(Giocatore * g) {

  return Andata(Andata::Null, g, this);

}

void CNEdificabile::liberaCasella(Giocatore */* g */) {}

int CNEdificabile::valoreCasella(Giocatore */* g */) const {

  return 0;

}

void CNEdificabile::eseguiAzione(const Ritorno& /* r */) {}
