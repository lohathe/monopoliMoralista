#include"CLegali.h"

//----------------C++ Casella della prigione------------------

Prigione::Prigione(string nome, int index, int numGiocatori): CNEdificabile(nome, index, numGiocatori) {

  for (int i=0; i<numGiocatori; ++i)
    turniPrigione.push_back(0);

}

// viene invocata da turno prima di spostare un giocatore:
// ritorna Andata::Fermo sse il giocatore e` in prigione e deve
//         scontare altri turni dietro le sbarre. Verra`
//         invocato apposito PopUp di informazione
// ritorna Andata::Nulla sse il giocatore ha gia` scontato la 
//         pena o se era finito su prigione durante il tragitto
//         e non tramite il tribunale
Andata Prigione::sceltaOpzione(Giocatore * g) {

  int x = turniPrigione[g->getNumGiocatore()];

  // informazione PREVENTIVA per Turno
  // se deve scontare altri turni in panciolle
  if (x>0) {
    // essendo informazione non modificabile dall'utente
    // decremento i turni di fermo direttamente qui
    turniPrigione[g->getNumGiocatore()] -= 1;
    return Andata(Andata::Ferm, g, this, 0, x);
  }
  // informazione PREVENTIVA per Turno
  // se ha finito di scontare i turni in panciolle
  // o se proprio non li deve scontare
  else {
    return Andata(Andata::Null, g, this);
  }

}

//esegui azione non fa niente quindi possiamo tenere quello ereditato da CNEdificabile

// metodo invocato da Tribunale per impostare quanti turni
// un certo giocatore dovra` scontare in Prigione
void Prigione::incarcera(int numGiocatore, int numTurni) {
if (static_cast<unsigned int>(numGiocatore)<turniPrigione.size())
  turniPrigione[numGiocatore] = numTurni;

}

//-------------C++ Casella del Tribunale---------------------

Tribunale::Tribunale(string nome, Prigione * p, int index, int numGiocatori): CNEdificabile(nome, index, numGiocatori), prigione(p){}

Andata Tribunale::sceltaOpzione(Giocatore *g) {

  return Andata(Andata::Trib, g, this);

}

void Tribunale::eseguiAzione(const Ritorno& r) {

  // se eseguo eseguiAzione vuol dire che il giocatore ha
  // tirato il dado, e dato che il dado non puo` mai fare
  // 0 so gia` che dovra` scontare almeno 1 turno in prigione
  prigione->incarcera(r.giocatore->getNumGiocatore(), r.value);

  // lo aggiorno il numero di caselle percorse dall'inizio
  // dal giocatore g
  r.giocatore->avanza(prigione->getIndiceCasella() - this->getIndiceCasella());

  // sposto la presenza dal tribunale alla prigione
  rimuoviGiocatore(r.giocatore->getNumGiocatore());
  prigione->aggiungiGiocatore(r.giocatore->getNumGiocatore());

}

//---------------C++ Casella della polizia-------------------

Polizia::Polizia(string nome, int costo, int index, int numGiocatori): CNEdificabile(nome, index, numGiocatori), ammenda(costo) {
  for (int i=0; i<numGiocatori; ++i) {
    fermo.push_back(false);
    appenaArrivato.push_back(true);
  }
}


//viene invocata da turno prima che il giocatore venga spostato!
//viene spostato soltanto se ritorna una bolla che non sia
//di tipo Polizia
Andata Polizia::sceltaOpzione(Giocatore * g){

  int index = g->getNumGiocatore();

  // se il giocatore e` appena arrivato sulla Polizia
  // invoca il PopUp per fargli tirare la moneta
  if (appenaArrivato[index]) {
    return Andata(Andata::Polz, g, this, 0, ammenda);
  }
  // e` informazione PREVENTIVA per Turno
  // se il giocatore e` sulla polizia e il turno attuale
  // e` il turno che deve saltare
  else if (fermo[index]) {
    // aggiorno per il prossimo turno del giocatore
    // che avra` cosi` scontato il turno in panciolle
    fermo[index] = false;
    return Andata(Andata::Ferm, g, this, 0, 1);
  }
  // se il giocatore inizia il nuovo turno gia` sulla Polizia
  // e non deve saltare il turno o l'ha gia` saltato allora
  // avverto TurnoLogico di fargli tirare il dado
  else {
    // e` informazione PREVENTIVA per Turno
    // aggiorno per i turni a venire:
    // il giocatore sta lasciando la Polizia, sia che sia stato in fermo
    // sia che non sia stato in fermo per un turno
    appenaArrivato[index] = true;
    return Andata(Andata::Null);
  }
}

// viene invocata dopo il lancio della moneta e inserisce il 
// risultato del lancio nell'array fermo[]
void Polizia::eseguiAzione(const Ritorno& r) {

  appenaArrivato[r.giocatore->getNumGiocatore()] = false;

  if (r.value==1){
      fermo[r.giocatore->getNumGiocatore()] = true;
      r.giocatore->decurtaDenaro(ammenda);
    }
}
