/****************************************\
 *
 *            POP UP
 *
\****************************************/

#include<iostream>
#include "PopUp.h"
using namespace std;

QString num2string(int num);
QString string2QString(string);

PopUp::PopUp(const Andata& info, QPixmap *pic, QWidget *parent) : QWidget(parent),  immagine(pic), type(info.tipo), giocatore(info.giocatore), casella(info.casella) {

  setFont(QFont("Helvetica", 10, QFont::DemiBold));
  setFixedSize(625, 400);

  // inizializzazione del PopUp per una casella in cui
  // la modalita` di gioco forza l'impossibilita` di 
  // fare qualsiasi cosa
  if(type == Andata::Null) {

    initNull(string2QString(casella->getNomeCasella()));

  }

  // inizializzazione del PopUp per una casella in cui
  // il giocatore e` forzato a pagare il pedaggio o
  // un ammenda od una tassa
  else if(type == Andata::Paga) {

    initPaga(string2QString(casella->getNomeCasella()), info.costo, casella->getProprietario());

  }

  // inizializzazione del PopUp per una casella in cui
  // il giocatore puo` diventare il proprietario e 
  // acquistare terreno, albergo o ipotecare
  else if(type == Andata::Edif) {

    // se e` possibile utilizzare l'ipoteca sull'albergo
    if(info.edificabili[3]) {

      initIpot(string2QString(casella->getNomeCasella()), info.attuale, info.limite, info.costo);

    }
    // altrimenti se la casella non ha un proprietario o
    // l'albergo non e` ancora stato costruito o se
    // la modalita` di gioco non permette l'ipoteca
    else {

      initEdif(string2QString(casella->getNomeCasella()), info.edificabili[1], info.edificabili[2], info.costo, info.limite);

    }

  }

  // inizializzazione del PopUp per una casella in cui
  // il giocatore puo` comprare delle quote di una societa`
  else if(type == Andata::Priv) {

    initPriv(info.costo, info.attuale, info.totale, info.limite);

  }

  // inizializzazione del PopUp per la casella della Polizia
  else if(type == Andata::Polz) {

    initPolz(info.costo);

  }

  // inizializzazione del PopUp per la casella del Tribunale
  else if(type == Andata::Trib) {

    initTrib();

  }

  // inizializzazione del PopUp per informare il 
  // giocatore di dover star fermo per TOT turni
  else if(type == Andata::Ferm) {

    initFerm(info.costo);

  }

  // inizializzazione del PopUp per la morte di un giocatore
  else if(type == Andata::Mort) {

    initMort();

  }

  // inizializzazione del PopUp per la vittoria di qualcuno
  // PopUp(Andata::Vitt, giocatore, 0, 0, giocatore->contaAveri(), 1|0)
  else if(type == Andata::Vitt) {

    initVitt(info.costo, info.attuale);

  }

}

void PopUp::paintEvent(QPaintEvent * /* event */) {

  QPainter painter(this);
  painter.fillRect(QRect(0, 0, 625, 400), Qt::lightGray);

  if(type == Andata::Mort) {
    painter.setOpacity(0.33);
    painter.drawPixmap(QRect(15, 15, 595, 370), QPixmap("immagini/sfondi/morte.jpg"));
    painter.drawPixmap(QRect(15+257,15+87,90,90), *immagine);
  }

  else if(type == Andata::Vitt) {
    painter.setOpacity(0.33);
    painter.drawPixmap(QRect(170, 50, 284, 277), QPixmap("immagini/sfondi/vittoria.gif"));
    for(int i=0; i<9; i++)
      painter.drawPixmap(QRect(16+i*1+i*65, 325, 65, 65), *immagine);
  }

  // entro sse il popUp NON e` per informare della morte di un giocatore
  // o della vittoria di qualcuno
  else {
    painter.setOpacity(0.33);
    painter.drawPixmap(QRect(15, 15, 595, 370), *immagine);
    painter.setOpacity(1);
    painter.setFont(QFont("LohitMarathi", 14, QFont::Normal, false));
    painter.drawText(QRect(0, 25, 625, 50), Qt::AlignCenter, "E' IL TURNO DI " + string2QString(giocatore->getNomeGiocatore()));
  }


}

// elaborazione dei dati: 
// creazione dell'interfaccia grafica per l'arrivo su di una
// casella in cui e` necessario PAGARE qualcuno
void PopUp::initPaga(const QString &NomeCasella, int DindiniDaPagare, Giocatore *g) {

  QString text = "\"Il pedaggio e` il pedaggio, e il formaggio e` il formaggio\ne se tu non paghi il pedaggio, io non mangio formaggio\" by Little John\n\nHEI! Ti trovi in " + NomeCasella;

  // se su e` su una casella Edificabile
  if(g) {
    text.append("\n\nche per tua sfortuna e` una proprieta` privata...\ninsomma: devi pagare "  + num2string(DindiniDaPagare) + " succulente Ghiande!\nNon disperare...tutte queste prelibatezze verranno devolute\ned andranno ad ingrassare le finanze di " + string2QString(g->getNomeGiocatore()));
  }
  // se si e` su una casella Non Edificabile
  else {
    text.append("\n\ne sfortunatamente per te che hai voglia di posare le tue zampette un po' ovunque\ndovrai pagare un'ammenda di " + num2string(DindiniDaPagare) + " Ghiande\n...insomma, e` per il bene di tutti: la Banca e la Societa` si augurano che capiate\n...e che magari passiate ancora!");
  }

  QLabel *info = new QLabel(text, this);
  info->setGeometry(15, 60, 595, 200);
  info->setAlignment(Qt::AlignCenter);

  QPushButton *paga = new QPushButton(tr("PAGA"), this);
  paga->setFont(QFont("Verdana", 15, QFont::Bold));
  paga->setGeometry(192, 260, 241, 45);

  connect(paga, SIGNAL(clicked()), this, SLOT(setPagamento()));
  // setPagamento chiama slot::close()

  return;

}

// corrispondente slot per settare il pagamento
void PopUp::setPagamento() {

  casella->eseguiAzione(Ritorno(giocatore, 3, 0));

  emit chiudi();

  close();

}

// elaborazione dei dati:
// creazione dell'interfaccia grafica per l'arrivo su di una
// casella in cui non e` possibile svolgere alcuna azione
void PopUp::initNull(const QString &NomeCasella) {

  QString text="HEI! Ti trovi in " + NomeCasella + "\n\nE` palesemente una zona veramente molto interessante...\ned e` proprio per questo che ti guardi attorno attonito\nsenza sapere che fare: il fatto che qui non si possa fare nulla \nnon viene minimamente preso in considerazione eh!";

  QLabel *info = new QLabel(text, this);
  info->setGeometry(15, 60, 595, 200);
  info->setAlignment(Qt::AlignCenter);

  QPushButton *fatto = new QPushButton(tr("FATTO"), this);
  fatto->setFont(QFont("Verdana", 15, QFont::DemiBold));
  fatto->setGeometry(192, 260, 241, 35);

  connect(fatto, SIGNAL(clicked()), this, SLOT(setNulla()));
  // setNulla chiama slot::close()

  return;

}

// corrispondente slot per fare nulla
void PopUp::setNulla() {

  // potrei invocare eseguiAzione() ma non sortirebbe
  // nessun effetto

  // emetto chiudi per ricordare di aggiornare la grafica
  emit chiudi();

  close();

}

// elaborazione dei dati:
// creazione dell'interfaccia grafica per l'arrivo su di una
// casella in cui e` possibile COMPRARE terreno o albergo
void PopUp::initEdif(const QString &NomeCasella, bool primaOpzione, bool secondaOpzione, int costo, int possiedoDenaro) {

  QString text = "HEI! Ti trovi in " + NomeCasella;

  QPushButton *pulsante;

  // primaOpzione = terreno in vendita
  // => non e` possibile comprare l'albergo
  if(primaOpzione) {

    pulsante = new QPushButton(tr("COMPRA TERRENO"), this);
    pulsante->setFont(QFont("Verdana", 15, QFont::Bold));
    pulsante->setGeometry(192, 260, 241, 45);
    connect(pulsante, SIGNAL(clicked()), this, SLOT(setCompraTerreno()));

    text.append("\n\ne se proprio vuoi fare un investimento a breve-lungo termine,\npotresti comprare questo bellissimo terreno: ma ovviamente ti\nverrebbe a costare " + num2string(costo) + " Ghiande");
    // se non ha abbastanza denaro gli nego la possibilita' 
    // di comprare il terreno e lo avverto di cio'
    if(!possiedoDenaro) {
      text.append("\n...che un povero straccione come te non sa nemmeno come\nsiano fatte...");
      pulsante->setDisabled(true);
    }

  }

  // secondaOpzione = albergo in vendita
  // => disabilito la possibilita' di ricomprare nuovamente il terreno
  else if(secondaOpzione) {

    pulsante = new QPushButton(tr("COMPRA ALBERGO"), this);
    pulsante->setFont(QFont("Verdana", 15, QFont::Bold));
    pulsante->setGeometry(192, 260, 241, 45);
    connect(pulsante, SIGNAL(clicked()), this, SLOT(setCompraAlbergo()));

    text.append("\n\ne se te ne fossi scordato, questo terreno e` proprio tuo!\nVolendo potresti comprare quella bella costruzione in cui ci si puo` rintanare per evitare\nil freddo dell'inverno, la calura dell'estate, la violenza della grandine e...\nNaturalmente per accondiscendere a questo tuo recondito\ndesiderio morboso dovresti privarti di " + num2string(costo) + " infime Ghiande");
    // se non ha abbastanza denaro gli nego la possibilta'
    // di comprare l'albergo e lo avevrto di cio'
    if(!possiedoDenaro) {
      text.append("\nanche se si puo' capire che per qualcuno tutte queste ghiande potrebbero fare la differenza\n...come per te, che non hai nemmeno l'ombra di un simile pantagruelica scorta\n...riprova piu` tardi, potresti essere piu' fortunato...beh...non contarci troppo!");
      pulsante->setDisabled(true);
    }

  }

  // se il giocatore e' il proprietario ed ha gia' comprato l'albergo
  // disabilito entrambi i pulsanti
  else {

    text.append("\n\nDovresti essere proprio tronfio d'orgoglio per aver fatto una\nsimile speculazione edilizia, cotanta avidita` e brutalita`\nsu un tanto bel territorio...\nMamma Natura ne chiedera` il prezzo un giorno!!!\n(e anche tu ne dovrai rispondere)");

  }


  QLabel *label = new QLabel(text, this);
  label->setAlignment(Qt::AlignCenter);
  label->setGeometry(15, 60, 595, 200);

  QPushButton *fatto = new QPushButton(tr("FATTO"), this);
  fatto->setFont(QFont("Verdana", 15, QFont::DemiBold));
  fatto->setGeometry(192, 310, 241, 35);
  connect(fatto, SIGNAL(clicked()), this, SLOT(setNulla()));

  return;

}

// corrispondente slot per comprare il terreno
void PopUp::setCompraTerreno() {
  casella->eseguiAzione(Ritorno(giocatore, 0, 0));
  emit chiudi();
  close();

}

// corrispondente slot per comprare l'albergo
void PopUp::setCompraAlbergo() {

  casella->eseguiAzione(Ritorno(giocatore, 1, 0));
  emit chiudi();
  close();

}

// elaborazione dei dati:
// creazione dell'interfaccia grafica per l'arrivo su di una
// casella in cui e` possibile variare l'IPOTECA dell'albergo
void PopUp::initIpot(const QString &NomeCasella, int ipotecaAttuale, int ipotecaMinima, int costoAlbergo) {

  QString text = "HEI! Ti trovi in " +  NomeCasella + "\n\nGuardandoti attorno probabilmente noterai che il posto non ti e` completamente\nestraneo, anzi: il terreno e l'albergo sono proprio tuoi!!! Anzi...dovresti essere\nproprio tronfio d'orgoglio per aver  fatto una simile speculazione edilizia,\ncotanta avidita` e brutalita` su un tanto bel territorio.\nMamma Natura ne chiedera` il prezzo un giorno: e pure tu ne dovrai rispondere!!!\nAnche se, ora come ora, la Magnificentissima e Rigogliosissima Banca delle Ghiande,\nben piu` pressante di Mamma Natura, Vi informa che e` disponibilissima a modificare\nil tasso di ipoteca sul Vostro albergo, sempre che Voi lo vogliate...";

  BarraIpoteca *ipoteca = new BarraIpoteca(ipotecaAttuale, ipotecaMinima, costoAlbergo, this);
  ipoteca->setGeometry(15, 60, 595, 330); 
  ipoteca->hide();

  connect(ipoteca, SIGNAL(aggiornaIpoteca(int)), this, SLOT(setVariazioneIpoteca(int)));
  // setIpoteca CHIAMA slot:close()

  QPushButton *fatto = new QPushButton(tr("FATTO"), this);
  fatto->setFont(QFont("Verdana", 15, QFont::DemiBold));
  fatto->setGeometry(192, 310, 241, 35);
  connect(fatto, SIGNAL(clicked()), this, SLOT(setNulla()));

  QLabel *label = new QLabel(text, this);
  label->setAlignment(Qt::AlignCenter);
  label->setGeometry(15, 60, 595, 200);

  QPushButton *mostraIpoteca = new QPushButton(tr("OPZIONI IPOTECA"), this);
  mostraIpoteca->setFont(QFont("Verdana", 15, QFont::DemiBold));
  mostraIpoteca->setGeometry(192, 260, 241, 45);
  connect(mostraIpoteca, SIGNAL(clicked()), mostraIpoteca, SLOT(hide()));
  connect(mostraIpoteca, SIGNAL(clicked()), label, SLOT(hide()));
  connect(mostraIpoteca, SIGNAL(clicked()), ipoteca, SLOT(show()));

  return;

}

// corrispettivo slot per modificare il tasso di ipoteca sull'albergo
void PopUp::setVariazioneIpoteca(int percentuale) {

  casella->eseguiAzione(Ritorno(giocatore, 2, percentuale));
  emit chiudi();
  close();

}

// elaborazione dei dati:
// creazione dell'interfaccia grafica per l'arrivo su di una
// casella in cui e` possibile COMPRARE azioni di una societa`
void PopUp::initPriv(int costo, int attuale, int totale, int limite) {

  BarraPrivata *azioni = new BarraPrivata(costo, attuale, totale, limite, string2QString(giocatore->getNomeGiocatore()), string2QString(casella->getNomeCasella()), this);
  azioni->setGeometry(15, 60, 595, 330); 

  connect(azioni, SIGNAL(aggiornaAzioni(int)), this, SLOT(setVariazioneAzioni(int)));

  QPushButton *fatto = new QPushButton(tr("FATTO"), this);
  fatto->setFont(QFont("Verdana", 15, QFont::DemiBold));
  fatto->setGeometry(192, 350, 241, 35);
  connect(fatto, SIGNAL(clicked()), this, SLOT(setNulla()));

  return;

}

void PopUp::setVariazioneAzioni(int percentuale) {

  casella->eseguiAzione(Ritorno(giocatore, 4, percentuale));
  emit chiudi();
  close();

}

void PopUp::initPolz(int ammenda) {

  QString text = "ACHTUNG : POLIZEI!!!\nProbabilmente hai fatto qualcosa di non bello: le mani che ti stanno toccando\nnon son di maniaci, ma son le sagge mani dei poliziotti che ti stanno perquisendo!\nNon tremare, non aver paura, perche` tu sai di aver paura...l'importante e` non darlo a vedere!\npotresti essere fortunato: magari non sentono quello strano odorino uscire dalle tue tasche!\nCerto e` che se ti va male passerai una caruccia nottata al fresco,\ne dovrai pagare un piiiccolo pegno: " + num2string(ammenda) + " Ghiande come ammenda per il misfatto";

  QLabel *label = new QLabel(text, this);
  label->setAlignment(Qt::AlignCenter);
  label->setGeometry(15, 60, 595, 200);

  BarraPolizia *moneta = new BarraPolizia(this);
  moneta->setGeometry(100, 220, 395, 135);
  connect(moneta, SIGNAL(tirato(int)), this, SLOT(setImprigionato(int)));

  return;

}

void PopUp::initTrib() {

  QString text = "Diciamo che sarebbe potuta andarti meglio, giusto per non far il drammatico:\nma proprio dentro al TRIBUNALE dovevi andarti ad imbrecanare per fumare!?!\nTu sai che la legge e`...mh...dovrebbe essere uguale per tutti, e proprio per questo fatto\nindiscutibile (o quasi) ti sei meritato dei giorni al fresco!\nE naturalmente senza dover pagare il climatizzatore!\nTi resta solo da tentare la sorte e sperare di trovare un giudice fumatore!";

  QLabel *label = new QLabel(text, this);
  label->setAlignment(Qt::AlignCenter);
  label->setGeometry(15, 60, 595, 200);

  BarraTribunale *dado = new BarraTribunale(this);
  dado->setGeometry(63, 220, 499, 135);
  connect(dado, SIGNAL(tirato(int)), this, SLOT(setImprigionato(int)));

  return;

}

void PopUp::setImprigionato(int numTurni) {

  casella->eseguiAzione(Ritorno(giocatore, 0, numTurni));
  
  emit chiudi();
  close();

}

void PopUp::initFerm(int x) {

  QString text = "Allora guarda: contando dai segni che hai fatto sul muro, manco fossero\nanni che sei chiuso qui dentro, dovrebbero mancare " + num2string(24*x) + " ore\nal tuo rilascio...Tieni duro!!!\nanh...se non si fosse capito si tratta di aspettare ancora ";

  if(x == 1) text.append("1 turno");
  else text.append(num2string(x) + " turni");

  QLabel *label = new QLabel(text, this);
  label->setAlignment(Qt::AlignCenter);
  label->setGeometry(15, 60, 595, 230);

  QPushButton *fatto = new QPushButton(tr("FATTO"), this);
  fatto->setFont(QFont("Verdana", 15, QFont::DemiBold));
  fatto->setGeometry(192, 260, 241, 35);
  connect(fatto, SIGNAL(clicked()), this, SLOT(setNulla()));

  return;

}

void PopUp::initMort() {

  QString text = "E` sempre un colpo al cuore...\n\n\n" + string2QString(giocatore->getNomeGiocatore()) + " ... SEI MORTO! SEI FALLITO! SEI SUL LASTRICO!!!\n\nIn questa Valle di Lacrime non c'e` giustizia, e la disperazione\nnon e` una valida sostituta!\nLa Florida Banca delle Quercie ha gia` ben pensato di sottrarti qualsiasi bene\nmobile ed immolbile. Non e` per mancanza di pudore che ora\nla tua tomba e` spoglia, come il tuo corpo, di qualsiasi cosa:\nnon hai amministrato come si deve i tuoi beni\nBiasimati pure ... ne avrai tutto il tempo!";

  QLabel *label = new QLabel(text, this);
  label->setAlignment(Qt::AlignHCenter);
  label->setGeometry(15, 60, 595, 300);

  QPushButton *fatto = new QPushButton(tr("RIPOSA IN PACE"), this);
  fatto->setFont(QFont("Verdana", 15, QFont::DemiBold));
  fatto->setGeometry(192, 310, 241, 35);
  connect(fatto, SIGNAL(clicked()), this, SLOT(setNulla()));

  return;

}

void PopUp::initVitt(int soldi, bool tipoVittoria) {

  QString text = "Ben considerando le cose...\n\nCONGRATULAZIONI: AVETE VINTO!!!\n\n" + string2QString(giocatore->getNomeGiocatore()) + ", la Vostra abilita` nell'amministrare i beni immobili e` encomiabile!";
  // tipoVittoria true sse Giocatore e` l'ultimo giocatore ancora in vita
  if(tipoVittoria)
    text.append("\nCon le vostre forze e con l'astuzia avete sbaragliato tutti quei mendicanti\nche avete trovato per strada...ora sono tutti morti, distrutti, falliti!!!\nE anche se avevano una famiglia sulle spalle, cosa importa?\nE dato che qui nei dintorni non ' rimasto piu` nessuno,\nora siete Voi la persona piu` ricca: con ben " + num2string(soldi) + " Ghiande!!!" );
  else
    text.append("\nCon le vostre forze e con l'astuzia dimostrata\navete abbindolato tutti gli altri stolti che concorrevano contro di voi!\n\nOra voi siete la persona piu` ricca!!!\nPotete crogiolarvi tra le vostre " + num2string(soldi) + " Ghiande!!!");

  QLabel *label = new QLabel(text, this);
  label->setAlignment(Qt::AlignHCenter);
  label->setGeometry(15, 60, 595, 300);

  QPushButton *esci = new QPushButton(tr("ESCI"), this);  
  esci->setFont(QFont("Verdana", 15, QFont::DemiBold));
  esci->setGeometry(192, 325, 241, 35);
  connect(esci, SIGNAL(clicked()), this, SLOT(setNulla()));

  return;

}
