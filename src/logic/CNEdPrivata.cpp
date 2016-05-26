/***************************************\
|      ::CASELLA NON EDIFICABILE::      |
|          OPZIONE PRIVATIZZATA         |
\***************************************/

#include "CNEdPrivata.h"

CNEdPrivata::CNEdPrivata(string nome, CNEdTasPrivata *soc, int ind, int numGiocatori): CNEdificabile(nome, ind, numGiocatori), societa(soc) {

}

// denaro / costoQuota == quante quote da 10% puo` comprare il giocatore
// #quote*10 + quotaAttuale == percentuale massima a cui puo` aspirare
//                             il giocatore
// ho sempre e solo una sola azione disponibile : modificare le quote
// di partecipazione degli Azionisti
Andata CNEdPrivata::sceltaOpzione(Giocatore *g) {

  int quotaMassima = (g->getDenaro()/societa->getCostoQuota())*10 + societa->getQuotaAzionista(g->getNumGiocatore());

  return Andata(Andata::Priv, g, this, 0, societa->getCostoQuota(), societa->getQuotaAzionista(g->getNumGiocatore()), quotaMassima, societa->getQuotaPrivata());

}

void CNEdPrivata::eseguiAzione(const Ritorno& r) {

  int percentualeQuota = r.value;

  if(percentualeQuota > 0)
    acquistaQuota(r.giocatore, percentualeQuota);

  else
    vendiQuota(r.giocatore, -percentualeQuota);

}

void CNEdPrivata::acquistaQuota(Giocatore *g, int percentualeQuota) {

  societa->incrementaAzionista(g, percentualeQuota);

}

void CNEdPrivata::vendiQuota(Giocatore *g, int percentualeQuota) {

  societa->decrementaAzionista(g, percentualeQuota);

}
