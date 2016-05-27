/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/


#include "giocatore.h"

#define GHIANDE 700
int bonusGiro=200;

Giocatore::Giocatore(string nome, int indice): nomeGiocatore(nome), denaro(GHIANDE), casellePercorse(0), numGiocatore(indice), morto(false){}

string Giocatore::getNomeGiocatore() const {

  return nomeGiocatore;

}

int Giocatore::getDenaro() const {

  return denaro;

}

int Giocatore::getNumGiocatore() const {

  return numGiocatore;

}

void Giocatore::aumentaDenaro(int soldi) {

  denaro += soldi;

}

int Giocatore::decurtaDenaro(int soldi) {
  int provv=0;
  if(denaro < soldi)
    {
      provv=denaro;
      denaro-=soldi;
      liberaProprieta();
      morto=true;

      return provv;
    }
  else
    denaro-=soldi;
  return soldi;
}

// newProprieta non e' presente in possedimenti[x]
// il test viene demandato alle funzioni invocatrici 
// di Giocatore::aumentaPossedimenti
void Giocatore::aumentaPossedimenti(CBase *newProprieta) {

  possedimenti.push_back(newProprieta);

}

// eliminando i possedimenti (relativo esclusivamente alle
// quote partecipative di societa') si preoccupa di riaggruppare 
// all'inizio dell'array i puntatori sucessivi
// viene invocata sse il giocatore possiede veramente una quota
void Giocatore::decurtaPossedimenti(CBase *oldProprieta) {

  vector<CBase*>::iterator it=possedimenti.begin();
  bool found=false;
  for (; it<possedimenti.end() && !found; it++){
      if (*it == oldProprieta)
	possedimenti.erase(it);
    }

}

vector<int> Giocatore::getIndiciPossedimenti() const {

  vector<int> temp;

  vector<CBase*>::const_iterator it=possedimenti.begin();
  for(; it<possedimenti.end(); ++it) {
    temp.push_back((*it)->getIndiceCasella());
  }

  return temp;

}

void Giocatore::avanza(int tot_caselle) {

  casellePercorse += tot_caselle;

}

int Giocatore::getCasellePercorse() const {

  return casellePercorse;

}

// calcola la ricchezza di un giocatore: denaro liquido e 
// beni immobili
int Giocatore::contaAveri() {

  int count=0;
  vector<CBase*>::iterator it=possedimenti.begin();
  for(;it<possedimenti.end(); ++it) {
    count += (*it)->valoreCasella(this);
  }
  return count + denaro;

}

void Giocatore::liberaProprieta()
{
  vector<CBase*>::iterator it=possedimenti.begin();
  morto=true;
  for(; it<possedimenti.end(); ++it)
    {
      (*it)->liberaCasella(this);
    }
}

void Giocatore::cameraCommercio(int caselleVecchie)
{
  int caselleNuove=getCasellePercorse();
  if((caselleNuove/20)>(caselleVecchie/20))
    aumentaDenaro(bonusGiro);
}

bool Giocatore::eMorto() const
{
  return morto;
}
