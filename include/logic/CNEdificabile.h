/*****************************************\
| CASELLA NON EDIFICABILE : VERSIONE BASE |
|                  header                 |
\*****************************************/

#ifndef CASELLA_NON_EDIFICABILE_H
#define CASELLA_NON_EDIFICABILE_H

#include "CBase.h"

class CNEdificabile : public CBase {

 public:

  CNEdificabile(string, int, int);

  // concretizzazione dei metodi virtuali puri per
  // poter creare caselle non edificabili (per opzione base)
  virtual Andata sceltaOpzione(Giocatore *);
  virtual void liberaCasella(Giocatore *);
  virtual int valoreCasella(Giocatore *) const;
  virtual void eseguiAzione(const Ritorno&);

};

#endif
