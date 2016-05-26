#include"ModalitaGioco.h"
#include<iostream>
#include<fstream>
#include<QFile>
#include<QTextStream>

using namespace std;

QString string2QString(string);

//-------------Metodi di ModalitaGioco-----------------------

ModalitaGioco::ModalitaGioco(Partita * par): partita(par), sb(new QSpinBox(this))   
{
  setFixedSize(850, 500);
  
  QPushButton * gioca= new QPushButton(tr("Gioca!"), this);
  QPushButton * esci= new QPushButton(tr("Esci"), this);
  
  QLabel * Titolo0= new QLabel(tr("Numero Giocatori"), this);
  QLabel * Titolo1= new QLabel(tr("Nome Giocatori"), this);
  QLabel * Titolo2= new QLabel(tr("Modalita di Gioco"), this);

  QLabel * Info[4];

  QHBoxLayout * lay2=new QHBoxLayout();
  lay2->addWidget(gioca);
  lay2->addWidget(esci);
  setWindowTitle("Scegli Modalita'");

  Titolo0->setAlignment(Qt::AlignHCenter);
  Titolo1->setAlignment(Qt::AlignHCenter);
  Titolo2->setAlignment(Qt::AlignHCenter);
  Titolo0->setFont(QFont("AnyStyle", 12, QFont::Bold));
  Titolo1->setFont(QFont("AnyStyle", 12, QFont::Bold));
  Titolo2->setFont(QFont("AnyStyle", 12, QFont::Bold));

  //Lineedits per i nomi dei giocatori
  inputNomi[0]=new QLineEdit("Kodama", this);
  inputNomi[1]=new QLineEdit("PavonPorco", this);
  inputNomi[2]=new QLineEdit("LumaCandela", this);
  inputNomi[3]=new QLineEdit("PesceCapra", this);

  Warning=new QLabel("Attenzione: i nomi dei giocatori devono essere lunghi meno di\n 11 caratteri", this);
  Warning->setAlignment(Qt::AlignHCenter);
  Warning->setFont(QFont("Times", 11));

  Modalita[0]=new QCheckBox("Modalita Ipoteca", this);
  Modalita[0]->setFont(QFont("AnyStyle", 10, QFont::Bold));
  Info[0]=new QLabel("In questa modalita e' permesso \n ipotecare i propri beni", this);
  //Info[0]->setAlignment(Qt::AlignHCenter);
  Info[0]->setFont(QFont("Times", 11));

  Modalita[1]=new QCheckBox("Modalita Privatizzata", this);
  Modalita[1]->setFont(QFont("AnyStyle", 10, QFont::Bold));
  Info[1]=new QLabel("In questa modalita e' permesso acquistare azioni delle societa\n Acqua Potabile, Energia Elettrica e Stazione Ferroviaria\n rispettivamente presso le sedi del Municipio,\n della Regione e della Provincia", this);
  //Info[1]->setAlignment(Qt::AlignHCenter);  
  Info[1]->setFont(QFont("Times", 11));

  Modalita[2]=new QCheckBox("Modalita Legale", this);
  Modalita[2]->setFont(QFont("AnyStyle", 10, QFont::Bold));
  Info[2]=new QLabel("In questa modalita finire sulla\n casella Tribunale equivale a trascorrere in prigione un numero di\n turni pari al lancio di un dado e finire sulla casella Polizia costringe\n con probabilita del 50% a saltare un turno", this);
  //Info[2]->setAlignment(Qt::AlignHCenter);
  Info[2]->setFont(QFont("Times", 11));

  Modalita[3]=new QCheckBox("Modalita Dado Truccato", this);
  Modalita[3]->setFont(QFont("AnyStyle", 10, QFont::Bold));
  Info[3]=(new QLabel("Questa modalita fa in modo che\n il dado dia sempre 1 come risultato", this));
  //Info[3]->setAlignment(Qt::AlignHCenter);
  Info[3]->setFont(QFont("Times", 11));

  QGridLayout * lay=new QGridLayout();
 
  lay->addWidget(Titolo0,0,0,1,1);
  sb->setRange(2,4);

  lay->addWidget(sb,1,0,1,1);
  lay->addLayout(lay2, 5,1,2,1);
 
 lay->addWidget(Titolo1,2,0,1,1);
  for (int i=0; i<4; ++i)
    {
      lay->addWidget(inputNomi[i],i+3, 0, 1, 1);
    }
  lay->addWidget(Warning,7,0,1,1);
  lay->addWidget(Titolo2,8,0,1,2);
  lay->addWidget(Modalita[0],9,0,1,1);
  lay->addWidget(Info[0],10,0,1,1);
  lay->addWidget(Modalita[1],11,0,1,1);  
  lay->addWidget(Info[1],12,0,2,1);
  lay->addWidget(Modalita[3],9,1,1,1);  
  lay->addWidget(Info[3],10,1,1,1);
  lay->addWidget(Modalita[2],11,1,1,1);  
  lay->addWidget(Info[2],12,1,2,1);
  
  inputNomi[2]->setDisabled(true);
  inputNomi[3]->setDisabled(true);
  setLayout(lay);
  
  connect(sb, SIGNAL(valueChanged(int)), this, SLOT(sistemaGiocatori(int)));
  connect(gioca, SIGNAL(clicked()), this, SLOT(salvaInfo()));
  connect(esci, SIGNAL(clicked()), this, SLOT(close()));
 }

void ModalitaGioco::sistemaGiocatori(int num)
{
  
  for(int i=0; i<num; ++i)
    inputNomi[i]->setDisabled(false);
  for(int i=num; i<4; ++i)
  inputNomi[i]->setDisabled(true);
} 
      
void ModalitaGioco::salvaInfo()
{
bool b=true;
  for (int i=0; i< 4; ++i)
    {
      if (inputNomi[i]->text().size()>11)
	b=false;
    }
  if (!b)
    {
    Warning->setFont(QFont("Times", 11, QFont::Bold));
    }
    else
{
	partita->salvaInfo();
 	close();
}

}

void ModalitaGioco::paintEvent(QPaintEvent */* e*/)
{
  QPainter painter(this);
  painter.drawPixmap(QRect(410,0,425,150), QPixmap(":/immagini/NomeGioco.gif"));
}

//--------------------Metodi di Partita-------------------

Partita::Partita(): opzioni(new ModalitaGioco(this)), numGiocatori(4), modalita(new bool[4]), Tavolo(0)
{
  opzioni->show();
}
void Partita::salvaInfo()
{
      numGiocatori=opzioni->sb->value();
      
      for(int i=0; i<numGiocatori; ++i)
	nomi.push_back(opzioni->inputNomi[i]->text().toStdString());
      
      for(int i=0; i<4; ++i)
	modalita[i]=opzioni->Modalita[i]->isChecked();
      
      CreaGioco();
}

void Partita::CreaGioco()
{
  QFile file(":/nomi");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    cout<<"ERRORE: impossibile aprire file dei nomi, creazione del gioco annullata";
  }
else
{
  //Per prima cosa creo un array dei giocatori logici e grafici
  vector<Giocatore *> GiocatoriLogici;
  vector<GiocatoreGraf *> GiocatoriGrafici;

  string percorso_avatar1=":/immagini/pedine_piccole/pedinaX.gif";
  string percorso_avatar2=":/immagini/pedine_grandi/pedinaX.gif";
  for (int i=0; i<numGiocatori; i++)
  {
    GiocatoriLogici.push_back(new Giocatore(nomi[i], i));
    percorso_avatar1[32]='0'+i+1;

    percorso_avatar2[31]='0'+i+1;
    GiocatoriGrafici.push_back(new GiocatoreGraf(string2QString(percorso_avatar1), string2QString(percorso_avatar2)));
  }

  vector<CBase *> CaselleLogiche;
  vector<CasellaGrafica *> CaselleGrafiche;
 

  CNEdTasPrivata * provvTasse=0;
  Prigione * prigione=0;	
  
  QTextStream IN(&file);

  for (int i=0; i<20; ++i)
    {
      string percorso=":/immagini/sfondi/sfondoX";
      percorso[24]='0'+i;
      if (i>=10){
	percorso[24]='0'+1;
	percorso.push_back('0'+(i-10));
      }

      int costoTerreno;
      int costoAlbergo;
      int pedaggioTerreno;
      int pedaggioAlbergo;

      QString qname = IN.readLine();
      IN>>costoTerreno>>costoAlbergo>>pedaggioTerreno>>pedaggioAlbergo;
      QString padding = IN.readLine();
      string nome = qname.toStdString();

      if (i==0)
	{
    CaselleLogiche.push_back(new CNEdificabile(nome, i, numGiocatori));
	  CaselleLogiche[0]->setTuttiPresenti();
	}
      if (i==1 || i==2 || i==4 || i==7 || i==9 || i==12 || i==13 || i==16 || i==17 || i==19)
	{
	  CEdificabile * c;
	  if (modalita[0])
	    {
	      c=new CEdIpoteca(nome, costoTerreno, costoAlbergo, pedaggioTerreno, pedaggioAlbergo, i, numGiocatori);
	    }
	  else
	    {
	      c=new CEdificabile(nome, costoTerreno, costoAlbergo, pedaggioTerreno, pedaggioAlbergo, i, numGiocatori);
	    }
	  CaselleLogiche.push_back(c);
	  CaselleGrafiche.push_back(new CasellaGraficaEd(string2QString(percorso),":/immagini/albergo.png", ":/immagini/timbro.gif", c, GiocatoriGrafici, Tavolo));
	}
      else{
	if (i==3 || i==8 || i==14)
	  {
	    if(modalita[1])
	      {
		provvTasse=new CNEdTasPrivata(nome,costoTerreno,costoAlbergo, i, numGiocatori);
		CaselleLogiche.push_back(provvTasse);
	      }
	    else
	      {
		CaselleLogiche.push_back(new CNEdTassa(nome, costoTerreno, i, numGiocatori));
	      }
	  }	  
	if (i==6 || i==11 || i==18)
	  {
	    if (modalita[1])
	      CaselleLogiche.push_back(new CNEdPrivata(nome, provvTasse, i, numGiocatori));
	    else
	      CaselleLogiche.push_back(new CNEdificabile(nome, i, numGiocatori));
	  }
	if (i==5)
	  {
	    if(modalita[2]){
	      prigione=new Prigione(nome, 5, numGiocatori);
	      CaselleLogiche.push_back(prigione);
	    }
	    else
	      CaselleLogiche.push_back(new CNEdificabile(nome, i, numGiocatori));
	  }
	if(i==10 || i==15)
	  {
	    if (modalita[2]){
	      if (i==10)
		CaselleLogiche.push_back(new Tribunale(nome, prigione, i, numGiocatori));
	      if (i==15)
		CaselleLogiche.push_back(new Polizia(nome, costoTerreno,i, numGiocatori));
	    }
	    else
	      CaselleLogiche.push_back(new CNEdificabile(nome, i, numGiocatori));
	  }
	CaselleGrafiche.push_back(new CasellaGrafica(string2QString(percorso), CaselleLogiche[i], GiocatoriGrafici, Tavolo));
      }
    } 
    
  TurnoLogico * TurnoLog=new TurnoLogico(GiocatoriLogici, CaselleLogiche);
  TurnoGrafico * TurnoGraf=new TurnoGrafico(CaselleGrafiche, GiocatoriGrafici, TurnoLog, modalita[3], modalita[2]);
  InfoGiocatori* info= new InfoGiocatori(GiocatoriLogici, GiocatoriGrafici, Tavolo);
  Tavolo=new TavoloDaGioco(TurnoGraf,CaselleGrafiche, info);

  Tavolo->show();
  file.close();
  }
}

Partita::~Partita()
{
  delete [] modalita;
  delete opzioni;
  delete Tavolo;
}
