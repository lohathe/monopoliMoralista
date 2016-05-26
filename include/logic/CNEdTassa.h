/***************************************\
|  :CASELLA NON EDIFICABILE TASSABILE:  |
|--------------  header  ---------------|
\***************************************/

#ifndef CASELLA_NON_EDIFICABILE_TASSABILE_H
#define CASELLA_NON_EDIFICABILE_TASSABILE_H

#include "CNEdificabile.h"


class CNEdTassa : public CNEdificabile {

 protected:

  const int quotaPedaggio;
  // tassa relativa alla permanenza sulla societa`
  
  void pagaPedaggio(Giocatore*);
  // metodo che riscuote il dovuto pagamento dal giocatore
  
 public:

  CNEdTassa(string, int, int, int);

  virtual Andata sceltaOpzione(Giocatore*);
  // invia all'interfaccia grafica le possibili azioni
  // della casella eseguibili dal utente

  virtual void eseguiAzione(const Ritorno&);
  // esegue l'azione confermata dall'utente nella
  // interfaccia grafica




};

#endif
