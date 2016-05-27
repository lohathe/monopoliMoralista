/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include "CNEdTasPrivata.h"


CNEdTasPrivata::CNEdTasPrivata(string nome, int pedaggio, int costoAzione, int ind, int numGiocatori): CNEdTassa(nome, pedaggio, ind, numGiocatori), costoQuota(costoAzione), quotaPrivata(0) {

  for(int i=0; i<numGiocatori; ++i) {
    membriAzionisti.push_back(0);
    quoteAzionisti.push_back(0);
  }

}


// funzione che aggiunge un nuovo azionista o che 
// aumenta la partecipazione del giocatore
void CNEdTasPrivata::incrementaAzionista(Giocatore *g, int quotaAzione) {

  int indexGiocatore=g->getNumGiocatore();

  // se il giocatore non è già azionista inserisco
  // il suo puntatore nella lista
  if(membriAzionisti[indexGiocatore]!=g) {
    membriAzionisti[indexGiocatore]=g;
    g->aumentaPossedimenti(this);
  }

  // aumento la partecipazione azionaria del giocatore
  // sia che sia un nuovo azionista, sia che sia un vecchio azionista
  quoteAzionisti[indexGiocatore]+=quotaAzione;

  // aggiorno la percentuale privata della societa'
  quotaPrivata+=quotaAzione;

  // il giocatore paga
  g->decurtaDenaro(quotaAzione/10*costoQuota);

}


// funzione che decrementa la
void CNEdTasPrivata::decrementaAzionista(Giocatore *g, int quotaAzione) {

  int indexGiocatore=g->getNumGiocatore();

  // decremento la partecipazione azionaria del giocatore
  quoteAzionisti[indexGiocatore]-=quotaAzione;

  // aggiorno la percentuale privata della societa'
  quotaPrivata-=quotaAzione;

  if(quoteAzionisti[indexGiocatore]==0) {
    // se il giocatore non ha piu' azioni della societa'
    // aggiorno la lista degli azionisti
    membriAzionisti[indexGiocatore]=0;
    g->decurtaPossedimenti(this);
  }

  // il giocatore viene risarcito
  g->aumentaDenaro(quotaAzione/10*costoQuota);

}

int CNEdTasPrivata::getQuotaAzionista(int numGiocatore) const {

  return quoteAzionisti[numGiocatore];

}

// unica azione disponibile è pagamento del pedaggio
Andata CNEdTasPrivata::sceltaOpzione(Giocatore *g) {

  return Andata(Andata::Paga, g, this, 0, quotaPedaggio);

}

// esegue l'azione confermata dall'utente tramite intergaccia grafica
// l'unica azione disponibile e` il pagamento del pedaggio
void CNEdTasPrivata::eseguiAzione(const Ritorno& r) {

  pagaPedaggio(r.giocatore);

}

// pagamento del pedaggio e possibile smistamento
// del denaro tra gli azionisti
void CNEdTasPrivata::pagaPedaggio(Giocatore *g) {

  int provv=quotaPedaggio;
  int soldi=g->decurtaDenaro(provv);

  // nel caso pagando il pedaggio il giocatore finisca i soldi
  // viene considerato morto senza ricevere la sua parte delle 
  // azioni
  vector<Giocatore *>::iterator it=membriAzionisti.begin();
  for(; it<membriAzionisti.end(); ++it)
    if(*it)
      (*it)->aumentaDenaro(static_cast<int>((soldi*quoteAzionisti[(*it)->getNumGiocatore()])/100));

  // NB: se il giocatore e' morto per pagare il pedaggio il metodo
  // Giocatore::decurtaDenaro(int) si preoccupa di segnalare il game-over
  // e rimuovere tutti i possedimenti del giocatore, quota della societa'
  // compresa: il puntatore al giocatore non esiste piu' nella lista 
  // degli azionisti e non andrei ad incrementare i soldi ad un giocatore
  // morto

}

// metodo invocato dal game-over di un giocatore: si elimina la sua quota
// di partecipazione alla societa'
void CNEdTasPrivata::liberaCasella(Giocatore *g) {

  int indexGiocatore=g->getNumGiocatore();

  // aggiorno la percentuale privata della societa'
  quotaPrivata-=quoteAzionisti[indexGiocatore];

  quoteAzionisti[indexGiocatore]=0;
  membriAzionisti[indexGiocatore]=0;

}

int CNEdTasPrivata::getCostoQuota() const {

  return costoQuota;

}

int CNEdTasPrivata::getQuotaPrivata() const {

  return quotaPrivata;

}

int CNEdTasPrivata::valoreCasella(Giocatore *g) {

  return costoQuota*(quoteAzionisti[g->getNumGiocatore()]/10);

}
