/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>

#include "BarraUtile.h"
#include "Bolla.h"
#include "giocatore.h"
#include "CBase.h"

class PopUp : public QWidget {

  Q_OBJECT

 public slots:

  void setNulla();
  void setPagamento();
  void setCompraTerreno();
  void setCompraAlbergo();
  void setVariazioneIpoteca(int);
  void setVariazioneAzioni(int);
  void setImprigionato(int);

 signals:

  void chiudi();

 private:

  QPixmap * immagine;
  Andata::Tipo type;
  Giocatore *giocatore;
  CBase *casella;

  // inizializzazione per una casella in cui non si fa nulla
  void initNull(const QString &);

  // inizializzazione per una casella in cui si deve pagare
  void initPaga(const QString &, int, Giocatore*);

  // inizializzazione per una casella edificabile in cui si compra
  void initEdif(const QString &, bool, bool, int, int);

  // inizializzazione per una casella ipotecabile in cui si ipoteca
  void initIpot(const QString &, int, int, int);

  // inizizlizzazione per una casella privatizzata in cui si aziona
  void initPriv(int, int, int, int);

  // inizializzazione della polizia
  void initPolz(int);

  // inizializzazione del tribunale
  void initTrib();

  // inizializzazione per informare di essere imprigionato
  void initFerm(int);

  // inizializzazione per la vincita di un giocatore
  void initVitt(int, bool);

  // inizializzazione per la morte di un giocatore
  void initMort();

 public:

  PopUp(const Andata&, QPixmap *, QWidget *parent=0);

  // dato che sullo heap vengono allocati solo oggetti derivanti da
  // QWidget e figli dell'oggetto da distruggere, il distruttore 
  // virtuale di QWidget si occupa da se di deallocare il deallocabile
  ~PopUp() {}

  void paintEvent(QPaintEvent*);
};


#endif
