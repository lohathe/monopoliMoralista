/*
* Copyright (c) 2009-2016 Marco Ziccardi, Luca Bonato
* Licensed under the MIT license.
*/

#include"TurnoGrafico.h"
#include<math.h>

static const double PI = 3.14159265;

QString string2QString(string);

//-----------------TurnoGrafico----------------------

TurnoGrafico::TurnoGrafico(const vector<CasellaGrafica*>& cas, const vector<GiocatoreGraf*> & gioc,TurnoLogico * tur, bool truccato, bool legale,  QWidget * parent): QWidget(parent), CaselleGrafiche(cas), GiocatoriGrafici(gioc), t(tur), move(new QPushButton("muovi!",this)), passa(new QPushButton("Fine Turno",this)), d(new Dado(this,truccato)), p(0), vecchiaCasella(0), nuovaCasella(0) {

  move->setDisabled(true);
  passa->setDisabled(true);
  setFixedSize(625, 400);
  d->setGeometry(300, 100, 200,75);
  move->setGeometry(320,180,160,50);
  passa->setGeometry(320,235,160,50);
  connect(d,SIGNAL(lanciato(int)),this, SLOT(attivaMovimento(int)));
  connect(move, SIGNAL(clicked()),this, SLOT(muovi()));
  connect(passa, SIGNAL(clicked()), this, SLOT (passaTurno()));
  if(legale)
    {
      connect(passa, SIGNAL(clicked()), this, SLOT(testPreliminare()));
    }

  // per l'animazione
  contatore = 0;
  x=190;
  y=190;
  angolo = 0.0;
  angoloTraiettoria = 0.0;

  timer = new QTimer(this);
  timer->setInterval(100);
  timer->start();
  connect(timer, SIGNAL(timeout()), this, SLOT(movimentoImmagine()));
  connect(move, SIGNAL(clicked()), timer, SLOT(stop()));

}

double distanza(int x1, int y1) {

  int temp1 = 190 - x1;
  int temp2 = 190 - y1;
  return sqrt(temp1*temp1 + temp2*temp2);

}

void TurnoGrafico::movimentoImmagine() {

  // il centro e` il punto P(190, 190)

  if(contatore%32 == 0) {

    contatore = 0;
    if(distanza(x, y) > 120.0)
      angoloTraiettoria = atan2(190-y, x-190) + 3.341592 - (rand()%400)/1000;
    else 
      angoloTraiettoria = (rand()%6283184)/1000000;
    rotazione = rand()%2;

  }

  contatore++;

  x += 2*cos(angoloTraiettoria);
  // la Y viene decrementata perche` il sistema di riferimento e` ruotato sottosopra
  // dato che l'origine del piano cartesiano e` indirizzata al punto P(190, 190) secondo
  // le coordinate geometriche delle QT : numero di pixel dall'angolo in alto a sinistra
  y -= 2*sin(angoloTraiettoria);
  angolo += ((rotazione == 1) ? 1.0: 0.0-1.0);

  update();

}

void TurnoGrafico::paintEvent(QPaintEvent */*e*/) {

  QPainter painter(this);
  painter.fillRect(QRect(0, 0, 625, 400), Qt::lightGray);
  painter.setFont(QFont("LohitMarathi", 14, QFont::Normal, false));
  painter.drawText(QRect(0,25,625,400), Qt::AlignHCenter, "E' IL TURNO DI "+string2QString(t->getGiocatore()->getNomeGiocatore()));
  painter.setOpacity(0.33);
  painter.drawPixmap(QRect(100,100,200,200),*(GiocatoriGrafici[t->getGiocatore()->getNumGiocatore()])->avatar_grande);
  painter.setOpacity(1);

  painter.translate(x, y);
  painter.rotate(angolo);
  painter.drawPixmap(QRect(-50, -50, 100, 100), *(GiocatoriGrafici[t->getGiocatore()->getNumGiocatore()])->avatar_grande);
} 

void TurnoGrafico::attivaMovimento(int risultato) {

  t->salvaLancio(risultato);
  move->setDisabled(false);
}

void TurnoGrafico::muovi() {

  move->setDisabled(true);
  vecchiaCasella=((t->getGiocatore())->getCasellePercorse())%CaselleGrafiche.size();
  Andata b=t->muovi();
  //aggiorna nel caso in cui fossimo passati dal via!
  emit aggiornaInfoGiocatori(t->getGiocatore()->getNumGiocatore()); 
  nuovaCasella=((t->getGiocatore())->getCasellePercorse())%CaselleGrafiche.size();
  CaselleGrafiche[vecchiaCasella]->update();
  CaselleGrafiche[nuovaCasella]->update();

  if (b.tipo==Andata::Vitt)
    {
      p = new PopUp(b, (GiocatoriGrafici[t->getGiocatore()->getNumGiocatore()])->avatar_grande, this);
      p->show();
      connect (p, SIGNAL(chiudi()), this, SLOT(close()));
      connect (p, SIGNAL(chiudi()), this, SIGNAL(chiudi()));
    }
  else 
    { 
      p = new PopUp(b, (CaselleGrafiche[(t->getGiocatore()->getCasellePercorse())%CaselleGrafiche.size()])->sfondoGrande, this);
      p->setAttribute(Qt::WA_DeleteOnClose);
      connect(p, SIGNAL(chiudi()), this, SLOT(updateInfoGiocatori()));
      connect(p, SIGNAL(chiudi()), this, SLOT(statoGiocatore()));
      connect(p, SIGNAL(chiudi()), this , SLOT(aggiorna()));
      connect(p, SIGNAL(chiudi()), timer, SLOT(start()));
      p->setGeometry(0,0,625,400);

      p->show();
      passa->setDisabled(false);
  }
 }

void TurnoGrafico::updateInfoGiocatori() {

  emit aggiornaInfoGiocatori(t->getGiocatore()->getNumGiocatore());

}

void TurnoGrafico::statoGiocatore()
{
Andata b=t->statoGiocatore();

//il giocatore è morto e ne è rimasto solo uno in vita, dobbiamo:
//	- comunicare la morte del giocatore in questione
//	- comunicare la vittoria del giocatore rimasto
  if(b.tipo==Andata::Vitt)
    {
      p = new PopUp(Andata(Andata::Mort, t->getGiocatore(), 0), (GiocatoriGrafici[t->getGiocatore()->getNumGiocatore()])->avatar_grande, this);
      p->setAttribute(Qt::WA_DeleteOnClose);
      p->show();
      PopUp * p1= new PopUp(b, (GiocatoriGrafici[b.giocatore->getNumGiocatore()])->avatar_grande, this);
      p1->setAttribute(Qt::WA_DeleteOnClose);
      t->passaTurno();
      
      connect(p, SIGNAL(chiudi()), p1, SLOT(show()));
      connect(p, SIGNAL(chiudi()), this, SLOT(updateInfoGiocatori()));
      connect(p1, SIGNAL(chiudi()), this, SLOT(close()));
      connect(p1, SIGNAL(chiudi()), this, SIGNAL(chiudi()));
      
      //aggiorno le CaselleGrafiche possedute dal giocatore morto che sono state
      //gia liberate logicamente da decurtaDenaro
      Giocatore* giocatore=t->getGiocatore();
      vector<int> indici=giocatore->getIndiciPossedimenti();
      vector<int>::iterator it= indici.begin();
      for(; it<indici.end(); ++it)
      
		{
		  CaselleGrafiche[*it]->update();
		}
      }
      
      //il giocatore è semplicemente morto e quindi comunichiamo il decesso 
      else if(b.tipo==Andata::Mort)
      {
      p= new PopUp(b, (GiocatoriGrafici[t->getGiocatore()->getNumGiocatore()])->avatar_grande, this);
      p->setAttribute(Qt::WA_DeleteOnClose);
      p->show();
      //aggiorno le CaselleGrafiche possedute dal giocatore morto che sono state
      //gia liberate logicamente da decurtaDenaro
      Giocatore* giocatore=t->getGiocatore();
      vector<int> indici=giocatore->getIndiciPossedimenti();
      vector<int>::iterator it= indici.begin();
      for(; it<indici.end(); ++it)
      
		{
		  CaselleGrafiche[*it]->update();
		}
      }
}	

void TurnoGrafico::passaTurno()
{
  t->passaTurno();
  d->abilitaLancio();
  passa->setDisabled(true);
  emit aggiornaInfoGiocatori(t->getGiocatore()->getNumGiocatore());
  update();
}

//questo aggiornamento è utile soltanto nel caso in cui il giocatore sia
//stato messo in prigione, altrimenti non serve a nulla quindi viene connesso
//soltanto se è selezionata la modalita legale
void TurnoGrafico::aggiorna()
{
  vecchiaCasella=nuovaCasella;
  nuovaCasella= ((t->getGiocatore())->getCasellePercorse())%CaselleGrafiche.size();
  CaselleGrafiche[nuovaCasella]->update();
  CaselleGrafiche[vecchiaCasella]->update();
}

//solo in modalita legale connetto questo slot
//prima di abilitare il pulsanti controllo che il giocatore non sia imprigionato
//nel qual caso comunico quanti turni mancano di carcere e permetto di passare
//il turno, altrimenti passo ad abilitare muovi
void TurnoGrafico::testPreliminare()
{
  move->setDisabled(true);
  Andata c=t->testPreliminare();  
  if(c.tipo==Andata::Ferm)
    {
      d->disabilitaLancio();
      p=new PopUp(c, (CaselleGrafiche[(t->getGiocatore()->getCasellePercorse())%CaselleGrafiche.size()])->sfondoGrande, this);
      p->setAttribute(Qt::WA_DeleteOnClose);
      p->show();
      passa->setDisabled(false);
     }
}

TurnoGrafico::~TurnoGrafico()
{
  vector<GiocatoreGraf *>::iterator it2=GiocatoriGrafici.begin();
  for (; it2<GiocatoriGrafici.end(); ++it2)
    {
      delete *it2;
    }

  /*invocazione del distruttore del turnologico che distrugge:
       -Giocatorilogici
       -Casellelogiche
  */
  delete t;
}

