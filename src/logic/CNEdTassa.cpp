/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include "CNEdTassa.h"

CNEdTassa::CNEdTassa(string nome, int quota, int ind, int numGiocatori): CNEdificabile(nome, ind, numGiocatori), quotaPedaggio(quota) { }

// crea l'interfaccia grafica che informa l'utente
// di dover pagare la tassa per il pedaggio
Andata CNEdTassa::sceltaOpzione(Giocatore *g) {

  return Andata(Andata::Paga, g, this, 0, quotaPedaggio);

}

// esegue l'azione disponibile
void CNEdTassa::eseguiAzione(const Ritorno& r) {

  pagaPedaggio(r.giocatore);

}

void CNEdTassa::pagaPedaggio(Giocatore *g) {

  g->decurtaDenaro(quotaPedaggio);

}
