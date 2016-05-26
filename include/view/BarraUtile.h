/***************************************\
|               BARRE UTILI             |
|---------------  header  --------------|
\***************************************/


#ifndef BARRA_UTILE_H
#define BARRA_UTILE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QProgressBar>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QTimer>

//////////////////////////////////////////////////////////////
/*********************** BARRA IPOTECA **********************/

class BarraIpoteca : public QWidget {

  Q_OBJECT

 public slots:

  // slot che invia il segnale per l'aggiornamento logico
  // dell'ipoteca sull'albergo
  void modificaIpoteca();

  // slots che aggiornano visivamente la ProgressBar
  void aggiornaIncremento();
  void aggiornaDecremento();

 signals:

  // segnale che avvisa l'effettivo variamento dell'ipoteca
  void aggiornaIpoteca(int newValue);

 private:

  // valore che indica la percentuale di ipoteca sull'albergo
  // quando e' stato invocato il pop-up
  int ipotecaAttuale;

  // valore che indica la percentuale di ipoteca sotto la quale
  // il giocatore non ha abbastanza denaro per pagarne il riscatto
  int ipotecaMinima;

  // valore dell'immobile:utilizzato solo per fornire la stima
  // di guadagno/perdita all'utente
  int costoAlbergo;

  QLabel *info;
  QPushButton *invia;
  QPushButton *incrementa;
  QPushButton *decrementa;
  QProgressBar *percentuale;

  // metodo che valuta l'attuabilita' sul cambiamento dell'ipoteca
  // e discerne i pulsanti cliccabili da quelli non cliccabili
  void checkValue(int newValue);

 public:

  BarraIpoteca(int, int, int, QWidget *parent=0);

  // dato che sullo heap vengono allocati solo oggetti derivanti da
  // QWidget e figli dell'oggetto da distruggere, il distruttore 
  // virtuale di QWidget si occupa da se di deallocare il deallocabile
  ~BarraIpoteca();

};

/********************* FINE BARRA IPOTECA ********************/
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/********************** BARRA PRIVATIZZATA *******************/

class BarraPrivata : public QWidget {

  Q_OBJECT

 public slots:

  // slot che invia il segnale per l'aggiornamento logico
  // della percentuale di privatizzazione della societa'
  void modificaAzioni();

  // slots che aggiornano visivamente la percentuale
  void incrementaAzioni();
  void decrementaAzioni();

 signals:

  // segnale che avvisa l'effettivo variamento delle Azioni
  void aggiornaAzioni(int newValue);

 private:

  // valore temporaneo che viene modificato
  int quotaTemporanea;

  // valore iniziale con cui il giocatore ha invocato il pop-up
  int quotaAttuale;

  // valore totale delle quote di Azioni di tutti i giocatori verso
  // una certa societa'
  int quotaTotale;

  // valore massimo disponibile al giocatore dettato dalle sue finanze
  int quotaMassima;

  QLabel *display;
  QLabel *info;
  QPushButton *incrementa;
  QPushButton *decrementa;
  QPushButton *invia;

  // metodo che valuta l'attuabilita' sul cambiamento della partecipazione
  // finanziaria e discerne i bottoni cliccabili da quelli non cliccabili
  void checkValue(int);

 public:

  BarraPrivata(int, int, int, int,  const QString&, const QString&,  QWidget* parent=0);

  // dato che sullo heap vengono allocati solo oggetti derivanti da
  // QWidget e figli dell'oggetto da distruggere, il distruttore 
  // virtuale di QWidget si occupa da se di deallocare il deallocabile
  ~BarraPrivata() {}

};

/***************** FINE BARRA PRIVATIZZATA *******************/
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/********************** BARRA POLIZIA ************************/

class BarraPolizia : public QWidget {

  Q_OBJECT

 public slots:

  // slot che fa lanciare la moneta
  void tiraMoneta();
  // slot che fornisce il risultato all'esterno
  void inviaSegnale();

 signals:

  // signal che informa del risultato del tiro della moneta
  void tirato(int);

 private:

  QPushButton *tira;
  QPushButton *fatto;
  QLabel *lLabel;
  QLabel *rLabel;
  QTimer *timer;
  int risultato;
  int ripetizione;

 public:

  BarraPolizia(QWidget *parent=0);
  ~BarraPolizia();

};

/******************** FINE BARRA POLIZIA *********************/
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/********************** BARRA TRIBUNALE **********************/

class BarraTribunale : public QWidget {

  Q_OBJECT

 public slots:

  // slot che fa lanciare il dado
  void tiraDado();
  // slot che fornisce il risultato all'esterno
  void inviaSegnale();

 signals:

  // signal che informa del risultato del tiro del dado
  void tirato(int);

 private:
  
  QPushButton *tira;
  QPushButton *fatto;
  QTimer *timer;
  int risultato;
  int ripetizione;

 public:

  BarraTribunale(QWidget *parent=0);
  ~BarraTribunale();

};

/******************* FINE BARRA TRIBUNALE ********************/
///////////////////////////////////////////////////////////////

#endif
