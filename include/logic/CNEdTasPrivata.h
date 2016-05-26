/*****************************************\
|        CASELLA NON EDIFICABILE          |
|     OPZIONE TASSABILE PRIVATIZZATA      |
|---------------  header  ----------------|
\*****************************************/

#ifndef CASELLA_NON_EDIFICABILE_TASSABILE_PRIVATIZZATA_H
#define CASELLA_NON_EDIFICABILE_TASSABILE_PRIVATIZZATA_H

#include "CNEdTassa.h"


class CNEdTasPrivata : public CNEdTassa {

 private:

  const int costoQuota;
  // costo di un'azione per il 10% della societa'

  int quotaPrivata;
  // percentuale privatizzata della societa'

  vector<Giocatore *>membriAzionisti;
  // vector dei giocatori aventi quote della societa'

 vector<int> quoteAzionisti;
  // vector delle corrispettive quote possedute dai giocatori
  
  void pagaPedaggio(Giocatore*);
  

 public:

 CNEdTasPrivata(string, int, int, int, int);

  void decrementaAzionista(Giocatore*, int);
  void incrementaAzionista(Giocatore*, int);
  int getCostoQuota() const;
  int getQuotaPrivata() const;
  int getQuotaAzionista(int) const;

  virtual Andata sceltaOpzione(Giocatore*);

  virtual void eseguiAzione(const Ritorno&);

  void liberaCasella(Giocatore*);

  int valoreCasella(Giocatore*);

};

#endif
