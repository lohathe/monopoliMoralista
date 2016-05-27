/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/


#ifndef INFO_GIOCATORI_H
#define INFO_GIOCATORI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QFont>

#include"giocatore.h"
#include"GiocatoreGraf.h"

/////////////////////////////////////////////////////////////
/********************* MONO GIOCATORE **********************/

class MonoGiocatore : public QWidget {

  Q_OBJECT;

 public slots:

  void aggiorna();

 private:

  const Giocatore* GiocatoreLogico;

  QGroupBox *group;
  QLabel *ghiande;
  QLabel *soldi;
  QPushButton *immagine;

 public:

  MonoGiocatore(Giocatore *, GiocatoreGraf *, QWidget * =0);
  ~MonoGiocatore();

};

/******************** FINE MONO_GIOCATORE ******************/
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/********************* INFO GIOCATORI **********************/

class InfoGiocatori : public QWidget {

  Q_OBJECT;

 public slots:

  void aggiorna();
  void abilitaGiocatore(int);

 private:

  vector<MonoGiocatore*> Schede;

public:
  
  InfoGiocatori(const vector<Giocatore*>&, const vector<GiocatoreGraf*>&, QWidget * =0);
  ~InfoGiocatori();

};

/******************** FINE INFO GIOCATORI ******************/
/////////////////////////////////////////////////////////////

#endif
