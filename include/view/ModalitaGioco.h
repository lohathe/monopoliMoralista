/********************************************************
 *                                                      *
 *               MODALITA GIOCO                         *
 *                   HEADER                             *
 *                                                      *
 ********************************************************/

#include<QWidget>
#include<QPushButton>
#include<QSpinBox>

#include<QCheckBox>
#include<QLineEdit>
#include<QLabel>
#include<QPainter>
#include"giocatore.h"
#include"TurnoLogico.h"
#include"Caselle.h"
#include"Grafica.h"
class Partita;


//----------Widget che presenta le varie modalita di gioco-----------
//Questo widget raccoglie le info dell'utente e le salva negli array di costruzione
//della partita
class ModalitaGioco: public QWidget
{
Q_OBJECT
 private:
 friend class Partita;
  Partita * partita;
  QLineEdit * inputNomi[4];
  QCheckBox * Modalita[4];
  QLabel * Warning;
  QSpinBox * sb;

 public:

  ModalitaGioco(Partita *);
  public slots:
  void sistemaGiocatori(int);
  void salvaInfo();
  void paintEvent(QPaintEvent *);
};




//Classe che crea il selettore di modalita e poi corrispondentemente
//il gioco, incapsula le informazioni necessarie al gioco (e alla sua deallocazione)
//partita contiene quindi:
/*
 -SchermataInziale:
        -ModalitaGioco;
 -TavoloDaGioco:
        -TurnoGrafico:
	       -vector GiocatoriGrafici
	       -vector CaselleGrafiche
	       -TurnoLogico:
	              -vector GiocatoriLogici
		      -vector CaselleLogiche
*/

class Partita
{
 private:
  //vettore dei nomi dei giocatori
  ModalitaGioco * opzioni;
  vector<string> nomi;
  int numGiocatori;
  bool* modalita;
  TavoloDaGioco* Tavolo;
 public:
  //costruttore
  Partita();
  
  void salvaInfo();
  //costruttore del gioco quando sono state selezionate le modalita
  void CreaGioco();
  //distruttore
  ~Partita();
};



