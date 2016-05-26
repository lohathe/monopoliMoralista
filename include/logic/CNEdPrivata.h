/***************************************\
|      ::CASELLA NON EDIFICABILE::      |
|          OPZIONE PRIVATIZZATA         |
|--------------  header  ---------------|
\***************************************/

#ifndef CASELLA_NON_EDIFICABILE_PRIVATIZZATA_H
#define CASELLA_NON_EDIFICABILE_PRIVATIZZATA_H

#include "CNEdificabile.h"
#include "CNEdTasPrivata.h"

class CNEdPrivata : public CNEdificabile {

 private:

  CNEdTasPrivata *societa;
  // puntatore alla cella a cui fa riferimento la possibilita'
  // di acquistare quote 
  
  void acquistaQuota(Giocatore*, int);
  // metodo che setta/aumenta la partecipazione del giocatore 
  // ad una data societa' pubblica

  void vendiQuota(Giocatore*, int);
  // metodo che resetta/decrementa la partecipazione del
  // giocatore ad una data societa' pubblica

 public:

  CNEdPrivata(string, CNEdTasPrivata*, int, int);

  virtual Andata sceltaOpzione(Giocatore*);
  // sceglie le opzioni disponibili all'esecuzione

  virtual void eseguiAzione(const Ritorno&);
  // esegue l'azione scelta dal giocatore



};


#endif
