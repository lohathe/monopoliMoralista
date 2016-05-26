/********************************************\
|  CASELLA EDIFICABILE : OPZIONE IPOTECABILE |
|-----------------  header  -----------------|
\********************************************/

#ifndef CASELLA_EDIFICABILE_IPOTECABILE_H
#define CASELLA_EDIFICABILE_IPOTECABILE_H

#include "CEdificabile.h"
#include "giocatore.h"


class CEdIpoteca : public CEdificabile {

 private:

  int ipotecato;
  // percentuale di ipoteca sulla casa:
  // le quote di ipoteca sono multipli di 10 cumulabili


 public:

  CEdIpoteca(string, int, int, int, int, int, int);

  int getIpoteca() const;

  virtual Andata sceltaOpzione(Giocatore *);
  // ridefinizione metodo di CEdificabile::sceltaOpzione

  virtual void eseguiAzione(const Ritorno&);
  // nuovo metodo di eseguiAzione

  void pagaPedaggio(Giocatore *);
  // ridefinizione metodo di CEdificabili:pagaPedaggio

  void aumentaIpoteca(int);
  // aumenta la percentuale di ipoteca sull'albergo

  void decurtaIpoteca(int);
  // decrementa la percentuale di ipoteca sull'albergo

  virtual void liberaCasella(Giocatore *);
  // rende la casella nuovamente sul mercato dopo
  // il decesso del proprietario

  virtual int valoreCasella(Giocatore *) const;
  // metodo che calcola il corrispettivo in valuta corrente dei beni
  // immobili presenti ed appartenenti al proprietario
};


#endif
