/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#ifndef TURNOGRAFICO_H
#define TURNOGRAFICO_H

#include<QWidget>
#include<QLabel>
#include<QGridLayout>
#include<QPushButton>
#include<QTimer>
#include"CasellaGrafica.h"
#include"GiocatoreGraf.h"
#include"Dado.h"
#include"TurnoLogico.h"
#include"PopUp.h"

//dichiarazione incompleta di dado
class Dado;
//dichiarazione incompleta di PopUp
class PopUp;

class TurnoGrafico: public QWidget
{
  Q_OBJECT;

 private:
  vector<CasellaGrafica*> CaselleGrafiche;
  vector<GiocatoreGraf*> GiocatoriGrafici;
  TurnoLogico * t;
  //il puntatore a turno logico, al fine di invocare le funzioni logiche
  //e di salvare in turno logico il risultato result del lancio del dado
  
  QPushButton * move;            //pulsante che attiva il movimento
  QPushButton * passa;        //pulsante che fa passare il turno
  Dado * d;
  PopUp * p;                    //puntatore al popup della casella
  int vecchiaCasella;
  int nuovaCasella;
  
  // animazione
  QTimer *timer;
  double angolo;
  double angoloTraiettoria;
  int rotazione;
  int contatore;
  int x;
  int y;
  
 signals:
  void chiudi();
  void aggiornaInfoGiocatori(int);
  
 public:
  TurnoGrafico(const vector<CasellaGrafica*> &, const vector<GiocatoreGraf*> &,TurnoLogico *, bool, bool, QWidget * =0);
  ~TurnoGrafico();
  void paintEvent(QPaintEvent *);
 
 public slots:
  void updateInfoGiocatori();  
  void passaTurno();
  void muovi();
  void attivaMovimento(int);
  void aggiorna();
  void testPreliminare();
  void statoGiocatore();
  void movimentoImmagine();
  
};
#endif
