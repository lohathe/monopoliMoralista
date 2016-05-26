#ifndef TURNOLOGICO_H
#define TURNOLOGICO_H

#include"CBase.h"
#include"giocatore.h"
#include"Bolla.h"

class TurnoLogico
{
private:
  int indiceGiocatore;
  const int lmax;
  vector<Giocatore*> GiocatoriLogici;
  vector<CBase*> CaselleLogiche;
  int result; //risultato dado tirato
  Giocatore* trovaVincitore() const;

 public:
  TurnoLogico(const vector<Giocatore*> &, const vector<CBase*> &);
  ~TurnoLogico();

  Andata muovi();
  Andata statoGiocatore();
  Andata testPreliminare();
  void passaTurno();
  void salvaLancio(int);
  Giocatore * getGiocatore();

};
#endif
