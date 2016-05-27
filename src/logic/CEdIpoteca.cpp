/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include "CEdIpoteca.h"

// COSTRUTTORE
CEdIpoteca::CEdIpoteca(string nome, int cTerr, int cAlb, int pTerr, int pAlb, int ind, int numGiocatori): CEdificabile(nome, cTerr, cAlb, pTerr, pAlb, ind, numGiocatori), ipotecato(0) {

}

int CEdIpoteca::getIpoteca() const {

  return ipotecato;

}

// metodo che sceglie le possibili azioni (in modo grossolano)
// per poi inviarle all'interfaccia grafica che consultera'
// il parere dell'utente
Andata CEdIpoteca::sceltaOpzione(Giocatore *g) {

  int possiedoDenaro = 1;

  // costoAlbergo/10 == quanto costa un 10% dell'albergo = quota di ipoteca
  // denaro/quotaIpoteca = quante quote di ipoteca puo` pagare
  int ipotecaMinima = g->getDenaro()/(getCostoAlbergo()/10);
  // se il giocatore puo` pagare piu` quote di ipoteca di quanto 
  // effettivamente e` ipotecato il terrno allora puo` riscuotere
  // completamente l'ipoteca
  if(ipotecato < ipotecaMinima*10)
    ipotecaMinima = 0;
  // altrimenti la percentuale di ipoteca piu` bassa che puo`
  // sperare di avere e`: ipoteca attuale - quote di ipoteca
  else
    ipotecaMinima = ipotecato - ipotecaMinima;

  if(!proprietario) {
    // terreno acquistabile ==> Andata::opz=1
    if(g->getDenaro() < getCostoTerreno())
      possiedoDenaro = 0;

    return Andata(Andata::Edif, g, this, 1, getCostoTerreno(), 0, possiedoDenaro, 0);

  }
  else if(proprietario==g && !isEdificata()){
    // terreno edificabile dal proprietario ==> Andata::opz=2
    if(g->getDenaro() < getCostoAlbergo())
      possiedoDenaro = 0;

    return Andata(Andata::Edif, g, this, 2, getCostoAlbergo(), 0, possiedoDenaro, 0);

  }
  else if(proprietario==g && isEdificata()) {
    // terreno già edificato puo` ipotecare l'albergo ==> Andata::opz=3

    return Andata(Andata::Edif, g, this, 3, getCostoAlbergo(), ipotecato, ipotecaMinima, 0);

  }
  else {
    // pagare il pedaggio ==> Andata::opz=0 non definita
    int costo = isEdificata() ? getPedaggioAlbergo() : getPedaggioTerreno();
    return Andata(Andata::Paga, g, this, 0, costo);
  }
}

// metodo richiamato da POPUP
// per eseguire le scelte del giocatore
void CEdIpoteca::eseguiAzione(const Ritorno& r) {

  if(r.operazioni[3]) {
    pagaPedaggio(r.giocatore);
  }
  else if(r.operazioni[0]) {
    compraTerreno(r.giocatore);
  }
  else if(r.operazioni[1]) {
    edificaAlbergo();
  }
  else if(r.operazioni[2]) {
    if(r.value > 0)
      aumentaIpoteca(r.value);
    else 
      decurtaIpoteca(-r.value);
  }

}

void CEdIpoteca::pagaPedaggio(Giocatore *g) {

  // il denaro che deve pagare il giocatore o il massimo che
  // possiede prima di perdere la partita
  int denaro=g->decurtaDenaro(isEdificata()? getPedaggioAlbergo() : getPedaggioTerreno());
  // il guadagno aumenta a seconda dell'ipoteca
  // tiene conto del probabile game-over del giocatore-non-proprietario
  proprietario->aumentaDenaro(ipotecato? static_cast<int>((100-ipotecato)*denaro/100) : denaro);

}

// l'interfaccia grafica si preoccupa di forninre una scelta
// di percentuali accettabili a seconda della situazione del 
// giocatore che possiede l'albergo
void CEdIpoteca::aumentaIpoteca(int percentuale) {

  ipotecato += percentuale;
  proprietario->aumentaDenaro(static_cast<int>((static_cast<double>(getCostoAlbergo())/100)*percentuale));

}

// l'interfaccia grafica si preoccupa di forninre una scelta
// di percentuali accettabili a seconda della situazione del 
// giocatore che ha ipotecato l'albergo
void CEdIpoteca::decurtaIpoteca(int percentuale) {

  ipotecato -= percentuale;
  proprietario->decurtaDenaro(static_cast<int>((static_cast<double>(getCostoAlbergo())/100)*percentuale));

}

void CEdIpoteca::liberaCasella(Giocatore * g) {

  CEdificabile::liberaCasella(g);
  ipotecato=0;

}

// calcola il valore della casella come se non fosse ipotecata
// nel caso lo sia sottrae il valore dell'albergo appartenente 
// alla banca
int CEdIpoteca::valoreCasella(Giocatore * g) const {

  int valore=CEdificabile::valoreCasella(g);

  if(ipotecato)
    valore -= static_cast<int>(getCostoAlbergo()/100)*ipotecato;

  return valore;

}
