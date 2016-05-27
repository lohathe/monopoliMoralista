/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#ifndef CASELLA_BASE_H
#define CASELLA_BASE_H

#include <QString>
#include <QWidget>
#include "giocatore.h"
#include "Bolla.h"

using namespace std;

class CBase {

protected:

  // nome della casella
  const string nomeCasella;
 
  int indiceCasella;
  
  
  // puntatore al proprietario della casella
  // se proprietario==NULL => il proprietario e` la Banca
  Giocatore *proprietario;
  
 
public:

    // array che indica le pedine/giocatori attualmente
  // soggiornanti nella casella
  vector<bool> presenti;


  CBase(string, int, int);

  // metodo virtuale puro per binding dinamico:
  // sceglie le vario opzioni attuabili sulla casella
  virtual Andata sceltaOpzione(Giocatore*) = 0;

  // metodo virtuale puro per binding dinamico:
  // necessario per caselle in cui il giocatore puo`
  // diventare proprietario di qualcosa legata alla casella stessa
  virtual void liberaCasella(Giocatore *) = 0;

  // metodo virtuale puro per binding dinamico:
  // ritorna il valore degli immobili presenti ed appartenendi
  // al proprietario
  virtual int valoreCasella(Giocatore *) const =0;

  // esegue l'azione scelta dal giocatore memorizzata in 
  // operazioni[i]
  virtual void eseguiAzione(const Ritorno&) = 0;

  // metodo che aggiunge il giocatore indicizzato da N
  // nell'array dei presenti nella casella
  void aggiungiGiocatore(int);

  // metodo che aggiunge il giocatore indicizzato da N
  // nell'array dei presenti nella casella
  void rimuoviGiocatore(int);

  // metodo utilizzato alla partenza per rendere presenti
  // i giocatori nella casella del via
  void setTuttiPresenti();

  int getIndiceCasella() const;
  
  string getNomeCasella() const {return nomeCasella;}
  
  Giocatore *getProprietario() const {return proprietario;}  

  virtual ~CBase();

};


#endif
