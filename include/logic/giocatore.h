/******************************************
|               GIOCATORE                              |
|                 header                                 |
\****************************************/

#ifndef GIOCATORE_H
#define GIOCATORE_H
#include"CBase.h"
#include<vector>
#include<string>
using std::string;
using std::vector;

class CBase;


class Giocatore {

 private:

  const string nomeGiocatore;
  int denaro;
  int casellePercorse;
  const int numGiocatore;
  bool morto;
  vector<CBase *> possedimenti;

 public:

  Giocatore(string, int);
  int getDenaro() const;
  string getNomeGiocatore() const;
  int getNumGiocatore() const;
  int getCasellePercorse() const;
  bool eMorto() const;
  vector<int> getIndiciPossedimenti() const;
  void aumentaDenaro(int);
  int decurtaDenaro(int);
  void aumentaPossedimenti(CBase*);
  void decurtaPossedimenti(CBase*);
  void avanza(int);
  int contaAveri();
  void liberaProprieta();
  void cameraCommercio(int);

};

#endif
