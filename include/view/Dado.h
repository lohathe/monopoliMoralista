/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#ifndef DADO_H
#define DADO_H
#include<QWidget>
#include<QPushButton>

//-----------------HEADER Dado-----------------------

class Dado: public QWidget
{
  Q_OBJECT


 private:
  QPixmap * pic;
  QPushButton * lancia;
  bool truccato;
  int risultato;

 public:
  Dado(QWidget *, bool);
  ~Dado();
  void paintEvent(QPaintEvent * e);
  void abilitaLancio();
  void disabilitaLancio();

 public slots:
  void mostra();
  void mostraTruccato();

 signals:
  void lanciato(int);

};
#endif
