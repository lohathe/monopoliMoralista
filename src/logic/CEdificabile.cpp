/****************************************\
|   CASELLA EDIFICABILE : OPZIONE BASE   |
|                                        |
\****************************************/

#include "CEdificabile.h"

CEdificabile::CEdificabile(string nome, int cTerr, int cAlb, int pTerr, int pAlb, int ind, int numGiocatori): CBase(nome, ind, numGiocatori), costoTerreno(cTerr), costoAlbergo(cAlb), pedaggioTerreno(pTerr), pedaggioAlbergo(pAlb), edificata(false) {}

int CEdificabile::getCostoTerreno() const {
  return costoTerreno;
}

int CEdificabile::getCostoAlbergo() const {
  return costoAlbergo;
}

int CEdificabile::getPedaggioTerreno() const {
  return pedaggioTerreno;
}

int CEdificabile::getPedaggioAlbergo() const {
  return pedaggioAlbergo;
}

bool CEdificabile::isEdificata() const {
  return edificata;
}

Andata CEdificabile::sceltaOpzione(Giocatore *g) {

  int possiedoDenaro = 1;

  if(!proprietario){
    // terreno acquistabile da chiunque ==>  Andata::opz=1
    if(g->getDenaro() < costoTerreno)
      possiedoDenaro = 0;
    return Andata(Andata::Edif, g, this, 1, costoTerreno, 0, possiedoDenaro, 0);

  }
  else if(proprietario==g && !edificata){
    // terreno edificabile dal proprietario ==> Andata::opz=2
    if(g->getDenaro() < costoAlbergo)
      possiedoDenaro = 0;
    return Andata(Andata::Edif, g, this, 2, costoAlbergo, 0, possiedoDenaro, 0);

  }
  else if(proprietario==g && edificata){
    // terreno del proprietario gia` edificato 
    return Andata(Andata::Edif, g, this, 0, 0, 0, 0, 0);
  }
  else
    // pagamento del dazio ==> Andata::opz= non definito ==> 0
    return Andata(Andata::Paga, g, this, 0, isEdificata() ? getPedaggioAlbergo() : getPedaggioTerreno(), 0, 0, 0);

}

// operazioni[x]==true sse il giocatore ha confermato l'azione disponibile
// possiedoDenaro==false => operazioni[x]==false : interfaccia grafica
// si preoccupa di disabilitare tutte lo opzioni disponibili
void CEdificabile::eseguiAzione(const Ritorno& r) {

  if(r.operazioni[3]) {
    pagaPedaggio(r.giocatore);
  }

  if(r.operazioni[0]) {
    compraTerreno(r.giocatore);
  }

  if(r.operazioni[1]) {
    edificaAlbergo();
  }

}

// invocabile se e solo se il giocatore ha abbastanza soldi
// per comprare il terreno senza andare in game-over
void CEdificabile::compraTerreno(Giocatore *g) {

  proprietario=g;
  g->decurtaDenaro(costoTerreno);
  // il giocatore paga la somma per l'acquisto del terreno
  g->aumentaPossedimenti(this);
  // salvato il puntatore alla cella per un eventuale game-over
  // del giocatore con necessario rilascio dei suoi Averi

}

// invocabile se e solo se il giocatore ha abbastanza soldi
// per comprare e costruire l'albergo senza andare in game-over
void CEdificabile::edificaAlbergo() {

  edificata=true;
  proprietario->decurtaDenaro(costoAlbergo);
  // il giocatore possiede gia' il puntatore alla casella in quanto
  // deve per forza aver acquistato il terreno

}

void CEdificabile::pagaPedaggio(Giocatore *g) {

  int denaro=g->decurtaDenaro(edificata? pedaggioAlbergo : pedaggioTerreno);
  // ricevo il denaro dal giocatore sulla casella: se il giocatore
  // non ha abbastanza denaro viene settato il game-over dalla funzione
  // Giocatore::decurtaDenaro e si prelevano i soldi che ha disponibili
  proprietario->aumentaDenaro(denaro);

}

// elimina i possedimenti del proprietario della casella che ritorna 
// una casella vergine
void CEdificabile::liberaCasella(Giocatore * g) {
  presenti[g->getNumGiocatore()]=0;
  proprietario=0;
  edificata=0;

}

// il proprietario della casella e' l'unico invocatore di tale metodo
// non necessita quindi di test per valutare se ha un proprietario
int CEdificabile::valoreCasella(Giocatore */* g*/) const {

  int valore=costoTerreno;
  if(edificata)
    valore += costoAlbergo;

  return valore;

}
