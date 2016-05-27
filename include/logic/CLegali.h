/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/


#ifndef LEGALI_H
#define LEGALI_H

#include"CNEdificabile.h"
#include"giocatore.h"

//-------------HEADER Casella della prigione-------------------

class Prigione: public CNEdificabile
{
 private:

  vector<int> turniPrigione;

 public:

  //costruttore
  Prigione(string, int, int);

  //sceltaOpzione viene invocata DA TURNO prima dello spostamento
  //se ci troviamo sulla prigione
  //e ritorna una Bolla prigione se e soltanto se il giocatore
  //su cui e' stata invocata e' carcerato e ha ancora turni da 
  //trascorrere in prigione
  virtual Andata sceltaOpzione(Giocatore *);

  // metodo per settare il numero di turni da scontare in Prigione
  void incarcera(int, int);

};

//--------------HEADER Casella del tribunale-------------------

class Tribunale: public CNEdificabile
{
 private:

  Prigione * prigione;

 public:

  //costrutture
  Tribunale(string, Prigione *, int, int);

  //metodo che raccoglie tutte le informazioni necassarie alla costruzione
  //del popup;
  virtual Andata sceltaOpzione(Giocatore *);

  //sposta logicamente il giocatore carcerato nella prigione
  //e segnala quanti turni questo dovra starvi
  virtual void eseguiAzione(const Ritorno&);

  // NB valoreCasella e liberaCasella sono eriditate da CNEdficabile,
  // dove erano state overridate con corpo vuoto perche inutili: 
  // questo va benissimo anche per il tribunale

};

//--------------HEADER Casella della polizia--------------------

class Polizia: public CNEdificabile
{
 private:

  vector<bool> fermo;
  vector <bool> appenaArrivato;
  const int ammenda;

 public:

  //costruttore
  Polizia(string, int, int, int);

  //viene invocato da TURNO prima di spostare il giocatore, se
  //ritorna una bolla polizia vuol dire che il giocatore in questione
  //e' in stato di fermo e in quel caso non sposta nulla
  virtual Andata sceltaOpzione(Giocatore *);

  //viene invocato se atterro dopo lo spostamento sulla polizia,
  //turno grafico fa vedere il lancio della moneta e poi si 
  //salva il risultato in un parametro dedicato
  //questa funzione in pratica non viene mai invocata
  //ma è necessario che venga ridefinita
  virtual void eseguiAzione(const Ritorno&);
};

#endif
