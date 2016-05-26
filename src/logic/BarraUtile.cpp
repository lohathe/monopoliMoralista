/*****************************************\
|               BARRE UTILI               |
|                                         |
\*****************************************/

#include "BarraUtile.h"


QString num2string(int num);

//////////////////////////////////////////////////
//////////////////////////////////////////////////
/**************** BARRA IPOTECA *****************/
/******************* INIZIO *********************/

BarraIpoteca::BarraIpoteca(int ipAttuale, int ipMinima, int cAlbergo, QWidget *parent) : QWidget(parent), ipotecaAttuale(ipAttuale), ipotecaMinima(ipMinima), costoAlbergo(cAlbergo){

  QGroupBox *group = new QGroupBox("opzioni di ipoteca", this);
  group->setFixedSize(585, 220);

  info = new QLabel("la vostra attuale ipoteca e' al " + num2string(ipotecaAttuale) + "%", group);
  info->setFixedSize(581, 170);
  info->setAlignment(Qt::AlignHCenter);

  invia = new QPushButton(tr("MODIFICA IPOTECA"), this);
  invia->setFont(QFont("Verdana", 15, QFont::Black));
  invia->setDisabled(true);
  invia->setGeometry(177, 200, 241, 45);
  connect(invia, SIGNAL(clicked()), this, SLOT(modificaIpoteca()));

  // creo il pulsante per aumentare l'ipoteca e relativa etichetta
  incrementa = new QPushButton("+", this);
  incrementa->setFixedSize(20, 23);
  incrementa->setFont(QFont("Verdana", 15, QFont::Black));

  // se l'ipoteca e' gia' al 100% blocco il pulsante per l'incremento
  if(ipotecaAttuale == 100)
    incrementa->setDisabled(true);

  // creo il pulsante per diminuire l'ipoteca e relativa etichetta
  decrementa = new QPushButton("-", group);
  decrementa->setFixedSize(20, 23);
  decrementa->setFont(QFont("Verdana", 15, QFont::Black));

  // se l'ipoteca e' gia' al 0% blocco il pulsante per il decremento
  if(ipotecaAttuale == 0)
    decrementa->setDisabled(true);

  // creo la barra che indica la percentuale di ipoteca sull'albergo
  percentuale = new QProgressBar(group);
  percentuale->setRange(0, 100);
  percentuale->setTextVisible(false);
  percentuale->setValue(ipotecaAttuale);

  connect(incrementa, SIGNAL(clicked()), this, SLOT(aggiornaIncremento()));
  connect(decrementa, SIGNAL(clicked()), this, SLOT(aggiornaDecremento()));

  QHBoxLayout *variazioneLayout = new QHBoxLayout;
  variazioneLayout->addWidget(decrementa);
  variazioneLayout->addWidget(percentuale);
  variazioneLayout->addWidget(incrementa);

  QVBoxLayout *layout = new QVBoxLayout(group);
  layout->addLayout(variazioneLayout);
  layout->addWidget(info);

  group->setLayout(layout);
  
}

// segnale per l'esterno per indicare di modificare l'ipoteca
// se il valore di NewIpoteca < 0 => la percentuale diminuisce
// se il valore di NewIpoteca > 0 => la percentuale aumenta
void BarraIpoteca::modificaIpoteca() {

  emit aggiornaIpoteca(percentuale->value() - ipotecaAttuale);

}

// aggiorna l'incremento appena effettuato dall'utente
void BarraIpoteca::aggiornaIncremento() {

  int newValue = percentuale->value() + 10;

  // setto il nuovo valore gia' calcolato nella progress bar
  percentuale->setValue(newValue);

  // se la percentuale raggiunta e' del 100% non permetto
  // piu' alcun incremento dell'ipoteca:non voglio percentuali piu'
  // alte del 100%
  if(newValue == 100)
    incrementa->setDisabled(true);

  // se la percentuale raggiunta e' del 10% riabilito il decremento
  // precedentemente disabilitato poiche' l'ipoteca era al 0%
  if(newValue == 10)
    decrementa->setDisabled(false);

  // controllo che il valore appena settato permetta l'effettivo
  // aggiornamento dell'ipoteca sull'albergo
  checkValue(newValue);

}

// aggiorna il decremento appena effettuato dall'utente
void BarraIpoteca::aggiornaDecremento() {

  int newValue = percentuale->value() - 10;

  // setto il nuovo valore gia' calcolato nella progress bar
  percentuale->setValue(newValue);

  // se la percentuale raggiunta e' del 0% non permetto
  // piu' alcun decremento dell'ipoteca:non voglio percentuali negative
  if(newValue == 0)
    decrementa->setDisabled(true);

  // se la percentuale raggiunta e' del 90% riabilito l'incremento
  // precedentemente disabilitato poiche' l'ipoteca era al 100%
  if(newValue == 90)
    incrementa->setDisabled(false);

  // controllo che il valore appena settato permetta l'effettivo
  // aggiornamento dell'ipoteca sull'albergo
  checkValue(newValue);

}

void BarraIpoteca::checkValue(int newValue) {

  QString text;

  // se dopo i vari cambiamenti apportati dall'utente la percentuale
  // di ipoteca rimane invariata dall'inizio segnalo il non-cambiamento
  if(newValue == ipotecaAttuale) {

    text = "la vostra attuale ipoteca e' al " + num2string(newValue) + "%";
    info->setText(text);
    invia->setDisabled(true);

  }

  // se l'ipoteca e' stata diminuita e il valore del decremento non 
  // e' ricoperto dalle finanze del giocatore segnalo che non e'
  // possibile decrementare di tanto l'ipoteca
  else if(newValue < ipotecaMinima) {

    text = "vi piacerebbe eh...ma purtroppo non possedete abbastanza Ghiande\nper estinguere cotanta parte della vostra ipoteca, e alla\nBanca Delle Querce non gliela fate!!!";
    info->setText(text);
    invia->setDisabled(true);

  }

  // altrimenti: l'ipoteca non e' restata invariata(aumentata o diminuita)
  // ed in caso sia stata diminuita il proprietario ha abbastanza denaro
  else {

    text = "state portando...mh...come dire: avete la vaga idea di portare l'ipoteca del vostro\nalbergo al " + num2string(newValue) + "%";
    if(ipotecaAttuale < newValue)
      text.append("\n\nQuesto vostro colpo di genio vi farebbe guadagnare " + num2string(((newValue-ipotecaAttuale)*costoAlbergo)/100) + " luccicose Ghiande ma...\nvi priverebbe di parte dei ricordi racchiusi tra quelle mura\nanh...e pure di parte degli introiti provenienti dal vostro albergo, non disperate:\nla Banca Delle Querce sapra' molto bene come investire il vostro immobile");
    else
      text.append("\n\nI vostri ricordi vi sono mancati? Per riaverli dovrete separarvi da " + num2string(((ipotecaAttuale-newValue)*costoAlbergo)/100) + " Ghiande\nma e` anche vero che in fin dei conti le prelibatissime Ghiande ve le aveva anticipate\nla Magnanima Banca Delle Querce CheNonChiedeMaiInteressi\nE poi tutti sanno che i ricordi non hanno prezzo:le ghiande non comprano la felicita`!!!");
    info->setText(text);
    invia->setDisabled(false);

  }

}

BarraIpoteca::~BarraIpoteca() {

  delete info;
  delete invia;
  delete incrementa;
  delete decrementa;
  delete percentuale;

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/************* BARRA PER LA PARTECIPAZIONE ***************/
/*********  FINANZIARIA ALLE AZIONI DELLA SOCIETA' *******/
/************************* INIZIO ************************/


BarraPrivata::BarraPrivata(int costoQuota, int qAttuale, int qTotale, int qMax, const QString &nome, const QString &NomeCasella, QWidget *parent) : QWidget(parent), quotaTemporanea(qAttuale), quotaAttuale(qAttuale), quotaTotale(qTotale), quotaMassima(qMax) {

  setFixedSize(585, 285);

  QString NomeSocieta = "";
  if(NomeCasella == "Municipio") NomeSocieta.append("dell'Acquedotto");
  if(NomeCasella == "Palazzo della Regione") NomeSocieta.append("della societa` Elettrica");
  if(NomeCasella == "Palazzo della Provincia") NomeSocieta.append("della Ferrovia");

  QLabel *Text = new QLabel("OHOH! Compra Vendi Compra Vendi Partecipa: con moderazione e mai piu' del 50%!!!\n\nSiete giunti in " + NomeCasella +"\nPer " + num2string(costoQuota) +" Ghiande potrete comprare un 10% (cumulativo) delle azioni " + NomeSocieta + "\noppure se non credete piu` nel Mercato ritirare le vostre azioni per la stessa cifra", this);
  Text->setAlignment(Qt::AlignHCenter);
  // SetFont ereditato dal padre = PopUp

  display = new QLabel(this);
  display->setNum(quotaAttuale);
  display->setFont(QFont("Verdana", 20, QFont::Black));
  QLabel *rDisplay = new QLabel("%", this);
  rDisplay->setFont(QFont("Verdana", 14, 70));
  QLabel *lDisplay = new QLabel(nome + ": ", this);
  lDisplay->setFont(QFont("Verdana", 14, 70));
  QLabel *lastDisplay;
  if(quotaTotale - quotaAttuale == 0)
    lastDisplay = new QLabel("[gli altri giocatori non detengono alcuna quota della societa`]", this);
  else
    lastDisplay = new QLabel("[gli altri giocatori detengono gia` il " + num2string(quotaTotale - quotaAttuale) + "% delle azioni]", this);
  lastDisplay->setFont(QFont("Verdana", 10, QFont::Black));

  // creo il pulsante per aumentare la Quota delle Azioni
  incrementa = new QPushButton("+", this);
  incrementa->setFixedSize(25, 25);
  incrementa->setFont(QFont("Verdana", 15, QFont::Black));
  if(quotaAttuale == 50)
    incrementa->setDisabled(true);

  // creo il pulsante per diminuire la Quota delle Azioni
  decrementa = new QPushButton("-", this);
  decrementa->setFixedSize(25, 25);
  decrementa->setFont(QFont("Verdana", 15, QFont::Black));
  if(quotaAttuale == 0)  
    decrementa->setDisabled(true);

  connect(incrementa, SIGNAL(clicked()), this, SLOT(incrementaAzioni()));
  connect(decrementa, SIGNAL(clicked()), this, SLOT(decrementaAzioni()));

  QHBoxLayout *hlayout = new QHBoxLayout;
  hlayout->addWidget(lDisplay, 18, Qt::AlignRight);
  hlayout->addWidget(display, 3, Qt::AlignLeft);
  hlayout->addWidget(rDisplay);
  hlayout->addWidget(decrementa);
  hlayout->addWidget(incrementa, 12, Qt::AlignLeft);

  info = new QLabel("La societa` Vi ricora inoltre la vostra partecipazione finanziaria al \nsuo sviluppo e mantenimento e` al " + num2string(quotaAttuale) + "%", this);
  info->setFixedSize(580, 100);
  info->setAlignment(Qt::AlignHCenter);

  invia = new QPushButton("MODIFICA QUOTA", this);
  invia->setFont(QFont("Verdana", 15, QFont::Bold));
  invia->setGeometry(177, 240, 241, 45);
  invia->setDisabled(true);
  connect(invia, SIGNAL(clicked()), this, SLOT(modificaAzioni()));
  // ci pensa PopUp a chiudere questa finestra tramite il signal
  // dello slot modificaAzioni

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(Text);
  layout->addLayout(hlayout);
  layout->addWidget(lastDisplay, 0, Qt::AlignCenter);
  layout->addWidget(info);

  setLayout(layout);

}

// segnale per l'esterno che indica la variazione delle Azioni
// se il valore di NewAzioni < 0 => la percentuale diminuisce
// se il valore di NewAzioni > 0 => la percentuale aumenta
// il valore non puo' essere == 0
void BarraPrivata::modificaAzioni() {

  emit aggiornaAzioni(quotaTemporanea - quotaAttuale);

}

// metodo che abilita/disabilita la possibilita' di inviare i nuovi dati
void BarraPrivata::checkValue(int newValue) {

  QString text;

  // se non ha abbastanza soldi per comprare le azioni
  // non gli permetto di acquistale
  if(newValue > quotaMassima) {
    invia->setDisabled(true);
    text = "La societa` e` veramente lusingata dal fatto che Voi riponiate tanta fiducia in lei...\nma purtroppo di bonta` non ci campa nessuno! ...era un modo gentile per dirvi che giocate\na far il riccastro quando non avete nemmeno abbastanza Ghiande per limarvi i denti!!!!";
  }

  // se effettivamente modificando i valori e' tornato
  // al valore iniziale 
  else if(newValue == quotaAttuale) {
    invia->setDisabled(true);
    text = "Guardate che se vi decidete non e` un male eh...\nsiete tornati alla vostra partecipazione iniziale: insomma...non e' cambiato nulla.\nVi si informa che non siete obbligati: potete sempre proseguire nel vostro cammino";
  }

  // se la quantita' di azioni della societa' sfora il 50%
  // non lascio che vengano acquistate le quote 
  // entro nell'IF sse qualcun altro ha acquistato qualche altra quota
  else if(newValue + (quotaTotale - quotaAttuale) > 50) {
    invia->setDisabled(true);
    text = "Eh...insomma...la societa` non permette agli azionisti esterni di\ndetenere piu' del 50% delle sue Azioni...non prendetevela sul personale:\nma Voi non siete il solo privato ad aver avanzato lunsighe e Ghiande!";
  }

  // altrimenti se ha il denaro sufficiente e il totale delle
  // quote e' inferiore al 50% permetto l'aggiornamento
  else {
    invia->setDisabled(false);
    text = "Prestate occhi, nasi e orecchi a quel che fate:\nstate modificando la vostra partecipazione come azionista! Fate bene i vostri calcoli!";
  }

  info->setText(text);

}

// incremento visivamente la partecipazione alle azioni della societa'
// senza tuttavia lasciar sforare il limite del 50% massimo pro giocatore
void BarraPrivata::incrementaAzioni() {

  quotaTemporanea += 10;

  if(quotaTemporanea == 50)
    incrementa->setDisabled(true);

  if(quotaTemporanea == 10)
    decrementa->setDisabled(false);

  display->setNum(quotaTemporanea);

  checkValue(quotaTemporanea);

}

// decremento visivamente la partecipazione alle azioni della societa'
// senza tuttavia lasciar sforare il limite del 0% minimo pro giocatore
void BarraPrivata::decrementaAzioni() {

  quotaTemporanea -= 10;

  if(quotaTemporanea == 40)
    incrementa->setDisabled(false);

  if(quotaTemporanea == 0 )
    decrementa->setDisabled(true);

  display->setNum(quotaTemporanea);

  checkValue(quotaTemporanea);

}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
/**************** BARRA POLIZIA *****************/
/******************* INIZIO *********************/

BarraPolizia::BarraPolizia(QWidget *parent) : QWidget(parent), risultato(11 + rand()%2), ripetizione(0) {

  setFont(QFont("Helvetica", 9, QFont::Black));
  setFixedSize(395, 135);

  lLabel = new QLabel("se la sorte vuoi tentar\ncroce ti fa sospirar", this);
  lLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
  rLabel = new QLabel("la moneta devi pigiar\ntesta ti fa imprecar!", this);
  rLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

  fatto = new QPushButton("???", this);
  fatto->setFont(QFont("Verdana", 15, QFont::DemiBold));
  fatto->setDisabled(true);
  connect(fatto, SIGNAL(clicked()), this, SLOT(inviaSegnale()));

  tira = new QPushButton(QPixmap(":/immagini/moneta/testa.gif"), "", this);
  tira->setIconSize(QSize(65, 65));
  tira->setFlat(true);

  timer = new QTimer(this);
  timer->setInterval(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(tiraMoneta()));
  connect(tira, SIGNAL(clicked()), timer, SLOT(start()));

  QHBoxLayout *hlayout = new QHBoxLayout;
  hlayout->addWidget(lLabel);
  hlayout->addWidget(tira);
  hlayout->addWidget(rLabel);

  QVBoxLayout *vlayout = new QVBoxLayout;
  vlayout->addLayout(hlayout);
  vlayout->addWidget(fatto);

  setLayout(vlayout);

}

BarraPolizia::~BarraPolizia() {

  delete tira;
  delete fatto;
  delete lLabel;
  delete rLabel;
  delete timer;

}

void BarraPolizia::inviaSegnale() {

  // risultato - 11 = rand()%2 [per inizializzazione]
  emit tirato(risultato - 11);

}

void BarraPolizia::tiraMoneta() {

  ripetizione++;
  timer->setInterval(timer->interval() + 100);

  if(ripetizione%2) {

    tira->setIcon(QPixmap(":/immagini/moneta/croce.gif"));
    fatto->setText("FUGGI CON FARE INDIFFERENTE");

  }

  else {

    tira->setIcon(QPixmap(":/immagini/moneta/testa.gif"));
    fatto->setText("AMMETTI LE TUE COLPE");

  }

  if(ripetizione == risultato) {

    timer->stop();
    tira->setDisabled(true);
    fatto->setDisabled(false);

  }

}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
/*************** BARRA TRIBUNALE ****************/
/******************* INIZIO *********************/

BarraTribunale::BarraTribunale(QWidget *parent) : QWidget(parent), risultato(0), ripetizione(12) {

  setFont(QFont("Helvetica", 9, QFont::Black));
  setFixedSize(499, 135);

  QLabel *lLabel = new QLabel("Tal sara` la prigionia che sconterai\nspera quindi siano pochi", this);
  lLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
  QLabel *rLabel = new QLabel("quanti i pallin che contar riuscirai\nper l'amor del formaggio!", this);
  rLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

  fatto = new QPushButton("CONSEGNATI ALLA GIUSTIZIA", this);
  fatto->setFont(QFont("Verdana", 15, QFont::DemiBold));
  fatto->setDisabled(true);
  fatto->setGeometry(50, 85, 395, 45);
  connect(fatto, SIGNAL(clicked()), this, SLOT(inviaSegnale()));

  tira = new QPushButton(QPixmap(":/immagini/dado/faccia1.gif"), "", this);
  tira->setIconSize(QSize(65, 65));
  tira->setFlat(true);

  timer = new QTimer(this);
  timer->setInterval(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(tiraDado()));
  connect(tira, SIGNAL(clicked()), timer, SLOT(start()));

  QHBoxLayout *hlayout = new QHBoxLayout;
  hlayout->addWidget(lLabel);
  hlayout->addWidget(tira);
  hlayout->addWidget(rLabel);

  QVBoxLayout *vlayout = new QVBoxLayout(this);
  vlayout->addLayout(hlayout);
  vlayout->addWidget(fatto);

}

BarraTribunale::~BarraTribunale() {

  delete fatto;
  delete tira;
  delete timer;

}

void BarraTribunale::inviaSegnale() {

  emit tirato(risultato);

}

void BarraTribunale::tiraDado() {

  ripetizione--;
  timer->setInterval(timer->interval() + 100);

  int temp = risultato;
  while(risultato==temp)  risultato = (rand()%6)+1;
  QString percorso = ":/immagini/dado/facciaX.gif";
  percorso[22] = '0' + risultato; 

  tira->setIcon(QPixmap(percorso));

  if(!ripetizione) {

    timer->stop();
    tira->setDisabled(true);
    fatto->setDisabled(false);

  }

}
