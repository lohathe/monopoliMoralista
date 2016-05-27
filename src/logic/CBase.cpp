/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include "CBase.h"

CBase::CBase(string n, int ind, int numGiocatori): nomeCasella(n), indiceCasella(ind), proprietario(0) {

  for(int i=0; i<numGiocatori; ++i) {
    presenti.push_back(false);
  }
}

void CBase::aggiungiGiocatore(int indexGiocatore) {

  presenti[indexGiocatore]=true;

}

void CBase::rimuoviGiocatore(int indexGiocatore) {

  presenti[indexGiocatore]=false;

}

void CBase::setTuttiPresenti() {
  vector<bool>::iterator it=presenti.begin();
  for (; it<presenti.end(); ++it) {
      *it=true;
  }

}

int CBase::getIndiceCasella() const
{
  return indiceCasella;
}

CBase::~CBase(){}
