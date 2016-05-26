 /************************
 *    TAVOLO DA GIOCO     *
 *       HEADER           *
 *                        *
 *                        *
 *************************/

#ifndef TAVOLODAGIOCO_H
#define TAVOLODAGIOCO_H

#include"TurnoGrafico.h"
#include"InfoGiocatori.h"
#include<QGridLayout>

class TavoloDaGioco: public QWidget
{
private:

  TurnoGrafico * t;

  vector<CasellaGrafica*> caselle;

  InfoGiocatori * Info;

public:

  TavoloDaGioco(TurnoGrafico * ,vector<CasellaGrafica*> &,  InfoGiocatori *);


  /*distruttore, distrugge il turnografico e infogiocatori
    turnografico a sua volta distrugge:
         -GiocatoriGrafici
	 -CaselleGrafiche
	 -turnologico
	 turnologico a sua volta distrugge:
	        -GiocatoriLogici
		-CaselleLogiche
  */

};

#endif
