#include"TurnoLogico.h"


TurnoLogico::TurnoLogico(const vector<Giocatore *> & gl, const vector<CBase *> & cl): indiceGiocatore(0),  lmax(15), GiocatoriLogici(gl), CaselleLogiche(cl), result(1)
{}

Andata TurnoLogico::muovi()
{
  int numCaselle=CaselleLogiche.size();

  int caselleVecchie= GiocatoriLogici[indiceGiocatore]->getCasellePercorse();

  CaselleLogiche[caselleVecchie%numCaselle]->rimuoviGiocatore(indiceGiocatore);

  GiocatoriLogici[indiceGiocatore]->avanza(result);

  CaselleLogiche[(GiocatoriLogici[indiceGiocatore]->getCasellePercorse())%numCaselle]->aggiungiGiocatore(indiceGiocatore);

  GiocatoriLogici[indiceGiocatore]->cameraCommercio(caselleVecchie);
  
  vector<Giocatore *>::iterator it=GiocatoriLogici.begin();
  if(GiocatoriLogici[indiceGiocatore]->getCasellePercorse()/numCaselle>=lmax)
    {
      Giocatore* g=trovaVincitore();
      return Andata(Andata::Vitt, g, 0 ,0 , g->getDenaro());
    }
  return CaselleLogiche[(GiocatoriLogici[indiceGiocatore]->getCasellePercorse())%numCaselle]->sceltaOpzione(GiocatoriLogici[indiceGiocatore]);
}

void TurnoLogico::passaTurno()
{
  int numGiocatori=GiocatoriLogici.size();

  indiceGiocatore=(indiceGiocatore+1)%numGiocatori;

 while(GiocatoriLogici[indiceGiocatore]->eMorto())
    indiceGiocatore=(indiceGiocatore+1)%numGiocatori;
}

//Quando uno dei giocatori supera il massimo numero di giri viene invocata
//trova vincitore in modo che identifichi il giocatore piu ricco e ne restituisca il puntatore
Giocatore* TurnoLogico::trovaVincitore() const{
  int max=0;
  Giocatore * winner=0;
  vector<Giocatore*>::const_iterator it= GiocatoriLogici.begin();
  for (; it<GiocatoriLogici.end() && !(*it)->eMorto(); ++it)
    {
      if((*it)->contaAveri()>max)
	{	  
	  max=(*it)->contaAveri();
	  winner=*it;
	}
    }
  return winner;
}

//
Andata TurnoLogico::statoGiocatore()
{
if(GiocatoriLogici[indiceGiocatore]->eMorto())
{
  CaselleLogiche[(GiocatoriLogici[indiceGiocatore]->getCasellePercorse())%CaselleLogiche.size()]->rimuoviGiocatore(indiceGiocatore);
  int num=0;
  Giocatore * g=0;
  vector<Giocatore*>::iterator it=GiocatoriLogici.begin();
  for (; it<GiocatoriLogici.end(); ++it){
      if (!(*it)->eMorto())
	{
	num++;
	g=*it;
	}
    }
  if (num==1){
     return Andata(Andata::Vitt, g, 0, 0, g->getDenaro(), 1);
    }
  return Andata(Andata::Mort, GiocatoriLogici[indiceGiocatore], 0, 0, 0, 0);
}
return Andata(Andata::Null, 0,0,0);
}

Giocatore * TurnoLogico::getGiocatore()
{
return GiocatoriLogici[indiceGiocatore];
}


//distruttore
TurnoLogico::~TurnoLogico(){
  vector<Giocatore*>::iterator it1=GiocatoriLogici.begin();
  for (; it1<GiocatoriLogici.end(); ++it1)
    delete *it1;

 vector<CBase*>::iterator it2=CaselleLogiche.begin();
 for (; it2<CaselleLogiche.end(); ++it2)
    delete *it2;
}

//metodo non usato da turno logico normale ma che serve
//a turno logico legale per gestire lo spostamento o meno in caso di
//prigionia
Andata TurnoLogico::testPreliminare()
{
      //controllo se sono imprigionato, se ritorna una bolla con tipo==Andata::Null
      //allora non sono imprigionato e posso muovermi
      //altrimenti ritorna una bolla con tipo=Andata::Prig e in questo caso non muovo
      //nulla e ritorno al turno grafico la stessa bolla!
      Andata b=CaselleLogiche[(GiocatoriLogici[indiceGiocatore]->getCasellePercorse())%CaselleLogiche.size()]->sceltaOpzione(GiocatoriLogici[indiceGiocatore]);
      if(b.tipo==Andata::Ferm)
	return b;

  return (Andata::Null);
}

void TurnoLogico::salvaLancio(int rs){
  result=rs;
}
