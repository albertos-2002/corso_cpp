#include <vector>
#include <iostream>
#include <string>
#include <TFile.h>
#include <TH1F.h>
#include <fstream>
#include "header/LifetimeFit.h"
#include "header/AnalysisSteering.h"
#include "header/ParticleLifetime.h"
#include "header/AnalysisInfo.h"
#include "header/AnalysisFactory.h"
#include "ActiveObserver.h"
#include "header/ParticleReco.h"
#include "header/ProperTime.h"
#include "header/class_event.h"
#include "TFileProxy.h"
using namespace std;

class ParticleLifetime;
class ProperTime;


//------------------------------------------------------------------------------------------------------------------------
//from braggplotv3

// concrete factory to create an ElementReco analyzer
class ParticleLifetimeFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleLifetimeFactory(): AnalysisFactory::AbsFactory( "plotTime" ) {}
  // create an ElementReco when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new ParticleLifetime( info );
  }
};
// create a global ElementRecoFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ElementRecoFactory will be available with name "plot".
static ParticleLifetimeFactory pl;
//-----------------------------------------------------------------------------------------------------------------------------

ParticleLifetime::ParticleLifetime(const AnalysisInfo* info_arg):AnalysisSteering(info_arg){
}

ParticleLifetime::~ParticleLifetime(){
}
  

void ParticleLifetime::beginJob(){

  ptr_particle_lt.reserve(2);
  string nome_particella;
  double param_minMass;
  double param_maxMass;
  double param_minTime;
  double param_maxTime;
  double param_minScan;
  double param_maxScan;
  double param_step;
  ifstream file_time( AnalysisSteering::aInfo->value("TimeFileName") );
  
  //lettura dei parametri di inizializzazione e creazione -----------------------------------
  
  while ( file_time >> nome_particella ){
  
    file_time >> param_minMass ;
    file_time >> param_maxMass ;
    file_time >> param_minTime ;
    file_time >> param_maxTime ;
    file_time >> param_minScan ;
    file_time >> param_maxScan ;
    file_time >> param_step ;
  
    ptr_particle_lt.push_back(new Particle_pm);
    pCreate( nome_particella, param_minMass, param_maxMass, param_minTime, param_maxTime, param_minScan, param_maxScan, param_step);
  }
  
  return;
}

void ParticleLifetime::endJob(){  

  //estrazione del nome dalla riga di comando
  string nome_file_root = AnalysisSteering::aInfo->value("RootFileName");

  TFileProxy* histo_file = new TFileProxy( nome_file_root.c_str() , "RECREATE");

//  if (histo_file -> IsOpen()) { cout << "File aperto correttamente" << endl; }

  for (unsigned int i=0; i < ptr_particle_lt.size() ; ++i){
  
  ptr_particle_lt.at(i) -> ptr_lifetime -> compute( (ptr_particle_lt.at(i) -> str_name) );
    
  cout << "Ipotesi " << ptr_particle_lt.at(i) -> str_name << endl;
  cout << "Numero eventi:  " << ptr_particle_lt.at(i) -> ptr_lifetime -> nEvents() << endl;
  cout << "Tempo        :  " << ptr_particle_lt.at(i) -> ptr_lifetime -> get_lifeTime() << endl;
  cout << "Errore       : " << ptr_particle_lt.at(i) -> ptr_lifetime -> get_lifeTimeError() << endl;
    
  ptr_particle_lt.at(i) -> ptr_histo -> Write();
  }

  histo_file -> Close();
  
  return;
}

void ParticleLifetime::update( const Event& classe_evento ){

  //creazione istanza a proper time, svolgimento della funzione ... e estrazione del tempo di decadimento
  static ProperTime* ptr_propertime = ProperTime::instance(); 
  ptr_propertime -> update( classe_evento );

  for (unsigned int i = 0; i < ptr_particle_lt.size(); ++i){
  
    if ( ptr_particle_lt.at(i) -> ptr_lifetime -> add( classe_evento ) ) {
   
      ptr_particle_lt.at(i) -> ptr_histo -> Fill( ptr_propertime -> decayTime() );
    }
  
  }
  
  return;
}

void ParticleLifetime::pCreate( string& nome, float minimo, float massimo, float minimo_tempo, float massimo_tempo, float minimo_scan, float massimo_scan, float step){

  int index =  ptr_particle_lt.size()-1;
  int bin_numb = 20;
  
  ptr_particle_lt.at(index) -> str_name = nome;
  
  ptr_particle_lt.at(index) -> ptr_lifetime = new LifetimeFit(minimo, massimo, massimo_tempo, minimo_tempo, massimo_scan, minimo_scan, step);
  
  const string new_nome = "time" + nome;
  
  ptr_particle_lt.at(index) -> ptr_histo = new TH1F(new_nome.c_str(), nome.c_str(), bin_numb, minimo_tempo, massimo_tempo);

  return;
}
