#include <vector>
#include <iostream>
#include <string>
#include <TFile.h>
#include <TH1F.h>
#include "header/LifetimeFit.h"
#include "header/AnalysisSteering.h"
#include "header/ParticleLifetime.h"
#include "header/AnalysisInfo.h"
#include "header/AnalysisFactory.h"
#include "ActiveObserver.h"
#include "header/ParticleReco.h"
#include "header/ProperTime.h"
#include "header/class_event.h"
using namespace std;

class ParticleLifetime;


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

ParticleLifetime::ParticleLifetime(const AnalysisInfo* info_arg):AnalysisSteering(info_arg), ActiveObserver<Event>(){
}

ParticleLifetime::~ParticleLifetime(){
}
  

void ParticleLifetime::beginJob(){

  ptr_particle_lt.reserve(2);

  //ipotesi lambda
  const string nome_1 = "Lambda";
  ptr_particle_lt.push_back(new Particle_pm);
  
  pCreate( nome_1, 1.115, 1.116, 10.0, 1000.0);
  //ipotesi k
  const string nome_2 = "K0";
  ptr_particle_lt.push_back(new Particle_pm);
  
  pCreate( nome_2, 0.495, 0.500, 10.0, 500.0);

  return;
}

void ParticleLifetime::endJob(){  

  //estrazione del nome dalla riga di comando
  string nome_file_root = AnalysisSteering::aInfo->value("plotTime");

  TFile* histo_file = new TFile( nome_file_root.c_str() , "RECREATE");

//  if (histo_file -> IsOpen()) { cout << "File aperto correttamente" << endl; }

  for (unsigned int i=0; i < ptr_particle_lt.size() ; ++i){
  
  ptr_particle_lt.at(i) -> ptr_lifetime -> compute();
  
    if(i==0){
    
      cout << "Ipotesi L0" << endl;
      cout << "Numero eventi:  " << ptr_particle_lt.at(i) -> ptr_lifetime -> nEvents() << endl;
    
      ptr_particle_lt.at(i) -> ptr_histo -> Write();
      
    }
    else{
  
      cout << "Ipotesi K0" << endl;
      cout << "Numero eventi:  " << ptr_particle_lt.at(i) -> ptr_lifetime -> nEvents() << endl;
  
      ptr_particle_lt.at(i) -> ptr_histo -> Write(); 
    }  
  }

  histo_file -> Close();

  return;
}

void ParticleLifetime::update( const Event& classe_evento ){

  for (unsigned int i = 0; i < ptr_particle_lt.size(); ++i){
  
    if ( ptr_particle_lt.at(i) -> ptr_lifetime -> add( classe_evento ) ) {
   
      //creazione istanza a particle reco, svolgimento della ex funzione mass e estrazione del tempo proprio
      ProperTime* ptr_propertime = new ProperTime();
      ptr_propertime -> update(classe_evento);
   
      ptr_particle_lt.at(i) -> ptr_histo -> Fill( ptr_propertime -> decayTime() );
    
      delete ptr_propertime;
    }
  
  }
  
  return;
}

void ParticleLifetime::pCreate( const string& nome, float minimo, float massimo, float minimo_tempo, float massimo_tempo){

//  TFile* histo_file = new TFile("histo.root", "RECREATE");

  int index =  ptr_particle_lt.size()-1;
  int bin_numb = 20;
  
  ptr_particle_lt.at(index) -> str_name = nome;
  
  ptr_particle_lt.at(index) -> ptr_lifetime = new LifetimeFit(minimo, massimo);
  
  const string new_nome = "time" + nome;
  
  ptr_particle_lt.at(index) -> ptr_histo = new TH1F(new_nome.c_str(), nome.c_str(), bin_numb, minimo_tempo, massimo_tempo);


  return;
}
