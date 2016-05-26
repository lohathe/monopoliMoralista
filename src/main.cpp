#include<QApplication>
#include"ModalitaGioco.h"

int main (int argc, char **argv)
{
  QApplication app(argc, argv);
  Partita partita= Partita();
  return app.exec();
}
