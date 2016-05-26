/********************************\
|         BOLLA
|           header
\********************************/

#ifndef BOLLA_H
#define BOLLA_H

// dichiarazioni incomplete di classi utilizzate
class Giocatore;
class CBase;

// classe finalizzata alla trasmissione dei dati tra la
// parte logica verso l'interfaccia grafica: il pop-up
// elaborera` i dati contenuti in questa classe per 
// offrire agli utenti le varie informazioni
class Andata {

 public:

  // struttura enumerazione per capire come dovranno venir
  // utilizzati i dati dal PopUp
  // Null  : caselle che non hanno uno scopo nella modalita` di gioco scelta
  // Paga  : caselle in cui il giocatore in turno puo` solo pagare
  //         -CEdificabile, -CEdIpoteca, -CNEdTassa, CNEdTasPrivata
  // Edif  : caselle in cui il giocatore puo` diventare il proprietario
  //         -CEdificabile, -CEdIpoteca
  // Priv  : caselle in cui il giocatore puo` diventare socio
  //         -CNEdPrivata
  // Ferm  : informativa PREVENTIVA per Turno, per sapere se poter
  //         lasciar tirare i dadi al giocatore o se vede saltare il turno
  // Polz  : Polizia
  // Trib  : Tribunale
  // Mort  : morte di un giocatore
  // Vitt  : fine della partita e vincita di qualcuno
  enum Tipo{Null, Paga, Edif, Priv, Ferm, Polz, Trib, Mort, Vitt};

  // tipo di casella in cui si e` finiti
  Tipo tipo;

  // puntatore al giocatore
  // posso recuperare: NomeGiocatore
  Giocatore *giocatore;

  // puntatore alla casella
  // posso recuperare: Proprietario, NomeCasella
  CBase *casella;

  // array delle possibili azioni disponibili nelle caselle edificabili:
  // [1] = compra terreno
  // [2] = compra albergo
  // [3] = ipoteca
  // [0] = per valori non definiti: onde evitare condivisione di risorse che
  //       potrebbe causare problemi
  // tali informazioni verrano poi utilizzate dal PopUp
  bool edificabili[4];

  // determina il costo di:
  // Pedaggio e Tassa  :: Tipo==Paga
  // Terreno e Albergo :: Tipo==Edif
  // QuotaSocieta`     :: Tipo==Priv
  // Turni da perdere  :: Tipo==Polz||Tipo==Trib||Tipo==Ferm
  // Soldi Finali      :: Tipo==Vitt
  int costo;

  // determina il valore attuale di:
  // PercentualeDiIpoteca         :: Tipo==Edif
  // PercentualeDiAzioniPossedute :: Tipo==Priv
  // TipoDiVittoria               :: Tipo==Vitt => 1 se il giocatore e` l'unico
  //                                               0 se ci sono altri giocatori
  int attuale;

  // determina il valore limite di:
  // PossiedoDenaro             :: Tipo==Edif (true o false)
  // IpotecaMinimaRaggiungibile :: Tipo==Edif
  // QuotaMassimaRaggiungibile  :: Tipo==Priv
  int limite;

  // determina la percentuale totale delle Quote degli Azionisti
  int totale;


  // costruttore di Andata
  Andata(Tipo t, Giocatore *g=0, CBase *c=0, int opz=0, int cs=0, int att=0, int lim=0, int tot=0);

  // distruttore
  ~Andata();

};

class Ritorno {

 public:

  Giocatore *giocatore;

  // array delle varie opzioni disponibili in tutte le caselle
  // operazioni[0] -> compra terreno
  // operazioni[1] -> compra albergo
  // operazioni[2] -> modifica ipoteca
  // operazioni[3] -> paga tassa
  // operazioni[4] -> modifica quota partecipazione azionaria
  bool operazioni[5];

  // valore effettivo delle nuove disposizioni
  // operazioni[0] -> non definito
  // operazioni[1] -> non definito
  // operazioni[2] -> value > 0 aumenta ipoteca | value < 0 decurta ipoteca
  // operazioni[3] -> non definito
  // operazioni[4] -> value > 0 compra quota | value < 0 decurta quota
  int value;

  Ritorno(Giocatore *g=0, int n=0, int v=0);

  ~Ritorno();

};

#endif
