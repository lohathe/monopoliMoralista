#include "InfoGiocatori.h"

QString string2QString(string);

MonoGiocatore::MonoGiocatore(Giocatore * gl, GiocatoreGraf * gg, QWidget * parent) : QWidget(parent), GiocatoreLogico(gl) {

  //setFixedSize(100, 100);
  setFont(QFont("Helvetica", 9, QFont::Black));

  group = new QGroupBox(string2QString(GiocatoreLogico->getNomeGiocatore()), this);
  group->setFixedSize(105, 130);

  ghiande = new QLabel("Ghiande :", this);
  ghiande->setFont(QFont("Helvetica", 7));
  soldi = new QLabel(this);
  soldi->setNum(GiocatoreLogico->getDenaro());

  QHBoxLayout *l = new QHBoxLayout;
  l->addWidget(ghiande, 0, Qt::AlignTop|Qt::AlignLeft);
  l->addWidget(soldi, 5, Qt::AlignTop);

  immagine = new QPushButton(this);
  immagine->setIcon(*(gg->avatar_grande));
  immagine->setFlat(true);
  immagine->setIconSize(QSize(65, 65));

  QVBoxLayout *la = new QVBoxLayout(group);
  la->addLayout(l);
  la->addWidget(immagine);

}

MonoGiocatore::~MonoGiocatore() {

  delete immagine;
  delete soldi;
  delete ghiande;
  delete group;

}

void MonoGiocatore::aggiorna() {

  if(GiocatoreLogico->eMorto()){

    ghiande->setText("BANCAROTTA");
    ghiande->setFont(QFont("Helvetica", 7, QFont::Black));
    soldi->setText("");
    immagine->setIcon(QPixmap(":/immagini/RIP.gif"));

  }
  else {

    soldi->setNum(GiocatoreLogico->getDenaro());

  }

}


InfoGiocatori::InfoGiocatori(const vector<Giocatore*> &gl, const vector<GiocatoreGraf*> &gg, QWidget * p): QWidget(p) {

  setFixedSize(110, 600);

  vector<Giocatore *>::const_iterator it= gl.begin();
  for (int i=0; it<gl.end(); it++, i++) {

    Schede.push_back(new MonoGiocatore(const_cast<Giocatore *>(*it), gg[i], this));
    Schede[i]->setGeometry(0, 20 + 140*i, 105, 130);
    Schede[i]->setDisabled(true);

  }

  Schede[0]->setDisabled(false);

}

InfoGiocatori::~InfoGiocatori() {

  vector<MonoGiocatore*>::iterator it=Schede.begin();
  for(; it<Schede.end(); ++it)
    delete (*it);

}

void InfoGiocatori::aggiorna() {

  vector<MonoGiocatore*>::iterator it=Schede.begin();
  for(; it<Schede.end(); ++it)
    (*it)->aggiorna();

}

void InfoGiocatori::abilitaGiocatore(int num) {

  aggiorna();

  vector<MonoGiocatore*>::iterator it=Schede.begin();
  for(int i=0; it<Schede.end(); ++it, ++i)
    if(i==num)
      (*it)->setDisabled(false);
    else
      (*it)->setDisabled(true);

}
