/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include<QApplication>
#include"ModalitaGioco.h"

int main (int argc, char **argv)
{
  QApplication app(argc, argv);
  Partita partita= Partita();
  return app.exec();
}
