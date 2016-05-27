/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#ifndef CASELLA_EDIFICABILE_H
#define CASELLA_EDIFICABILE_H

#include "CBase.h"
#include "Bolla.h"

class CEdificabile : public CBase {

 private:

  const int costoTerreno;
  // importo da versare alla Banca per acquistarne il terrno 
  
  const int costoAlbergo;
  // importo da versare alla Banca per costruire un albergo nel 
  // terreno acquistato 

  const int pedaggioTerreno;
  // importo da versare al proprietario nel caso il terreno non  
  // sia piu' proprietà della Banca e sul quale non sia ancora 
  // stato edificato un albergo 

  const int pedaggioAlbergo;
  // importo da versare al proprietario quando sul terreno sia 
  // presente un albergo
  // pedaggioAlbergo esclude pedaggioTerreno e vice-versa

  bool edificata;
  // booleano che identifica se sul terreno sia edificato un albergo

  /*
    PUNTATORE_AL_PROPRIETARIO : ereditato dalla classe base
  */

 public:

  CEdificabile(string, int, int, int, int, int, int);

  int getCostoTerreno() const;
  int getCostoAlbergo() const;
  int getPedaggioTerreno() const;
  int getPedaggioAlbergo() const;
  bool isEdificata() const;

  virtual Andata sceltaOpzione(Giocatore *);
  // metodo che invia all'interfaccia grafica le azioni disponibili
  // che il giocatore puo' eseguire su una tale cella

  virtual void eseguiAzione(const Ritorno&);
  // metodo che esegue effettivamente l'azione scelta dall'utente
  // modificando opportunamente l'interfaccia logica

  void compraTerreno(Giocatore *);
  // metodo che setta il proprietario del terreno

  void edificaAlbergo();
  // metodo che setta la casella come edificata

  void pagaPedaggio(Giocatore *);
  // metodo che calcola il pedaggio da versare al proprietario della casella

  virtual void liberaCasella(Giocatore *);
  // metodo che libera la casella dal proprietario deceduto

  virtual int valoreCasella(Giocatore * g) const;
  // metodo che calcola il corrispettivo in valuta corrente dei beni
  // immobili presenti ed appartenenti al proprietario

};


#endif
