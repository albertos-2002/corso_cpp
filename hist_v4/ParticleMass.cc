#include <vector>
#include <iostream>
#include <string>
#include <TFile.h>
#include <TH1F.h>
#include "header/class_massmean.h"
#include "header/AnalysisSteering.h"
#include "header/ParticleMass.h"
#include "header/AnalysisInfo.h"
#include "header/AnalysisFactory.h"
#include "ActiveObserver.h"
#include "header/ParticleReco.h"
using namespace std;

class ParticleMass;

//from braggplotv3 ------------------------------------------------------------------------------

// concrete factory to create an ElementReco analyzer
class ParticleMassFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleMassFactory(): AnalysisFactory::AbsFactory( "plotMass" ) {}
  // create an ElementReco when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new ParticleMass( info );
  }
};
// create a global ElementRecoFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ElementRecoFactory will be available with name "plot".
static ParticleMassFactory pm;

//-----------------------------------------------------------------------------------------------

ParticleMass::ParticleMass(const AnalysisInfo* info_arg):AnalysisSteering(info_arg), ActiveObserver<Event>(){
}

ParticleMass::~ParticleMass(){

  for (auto c : ptr_particle_pm){

    delete c -> ptr_massmean;
    delete c -> ptr_histo;
    delete c;
    }

  ptr_particle_pm.clear();

}
  

void ParticleMass::beginJob(){

  ptr_particle_pm.reserve(2);

  //ipotesi lambda
  const string nome_1 = "Lambda";
  ptr_particle_pm.push_back(new Particle_pm);
  pCreate( nome_1, 1.115, 1.116);
  
  //ipotesi k0
  const string nome_2 = "K0";
  ptr_particle_pm.push_back(new Particle_pm);
  pCreate( nome_2, 0.495, 0.500);

  return;
}

void ParticleMass::endJob(){  

  //estrazione del nome dalla riga di comando
  string nome_file_root = AnalysisSteering::aInfo->value("plotMass");

  TFile* histo_file = new TFile( nome_file_root.c_str() , "RECREATE");

//  if (histo_file -> IsOpen()) { cout << "File aperto correttamente" << endl; }

  for (unsigned int i=0; i < ptr_particle_pm.size() ; ++i){
  
  ptr_particle_pm.at(i) -> ptr_massmean -> compute();
  
    if(i==0){
    
      cout << "Ipotesi L0" << endl;
      cout << "Numero eventi:  " << ptr_particle_pm.at(i) -> ptr_massmean -> nEvents() << endl;
      cout << "Media        :  " << ptr_particle_pm.at(i) -> ptr_massmean -> mMean() << endl;
      cout << "RMS          :  " << ptr_particle_pm.at(i) -> ptr_massmean -> mRMS() << endl;
      cout << ptr_particle_pm.at(i) -> ptr_massmean -> discarded_events << endl;
    
      ptr_particle_pm.at(i) -> ptr_histo -> Write();      
    }
    else{
  
      cout << "Ipotesi K0" << endl;
      cout << "Numero eventi:  " << ptr_particle_pm.at(i) -> ptr_massmean -> nEvents() << endl;
      cout << "Media        :  " << ptr_particle_pm.at(i) -> ptr_massmean -> mMean() << endl;
      cout << "RMS          :  " << ptr_particle_pm.at(i) -> ptr_massmean -> mRMS() << endl;
      cout << ptr_particle_pm.at(i) -> ptr_massmean -> discarded_events << endl;
  
      ptr_particle_pm.at(i) -> ptr_histo -> Write(); 
    }  
  }

  histo_file -> Close();

  return;
}

void ParticleMass::update( const Event& classe_evento ){

      //creazione istanza a particle reco, svolgimento della ex funzione mass e estrazione della massa invariante
      static ParticleReco* ptr_particlereco = ParticleReco::instance();
      ptr_particlereco -> update( classe_evento );

  for (unsigned int i = 0; i < ptr_particle_pm.size(); ++i){
  
    if ( ptr_particle_pm.at(i) -> ptr_massmean -> add( classe_evento ) ) {
      
      ptr_particle_pm.at(i) -> ptr_histo -> Fill( ptr_particlereco -> get_invariantmass() );
    }  
  }
  
  return;
}

void ParticleMass::pCreate( const string& nome, float minimo, float massimo){

//  TFile* histo_file = new TFile("histo.root", "RECREATE");

  int index =  ptr_particle_pm.size()-1;
  int bin_numb = 20; 
  
  ptr_particle_pm.at(index) -> str_name = nome;
  
  ptr_particle_pm.at(index) -> ptr_massmean = new MassMean(minimo, massimo);
  
  const string new_nome = "mass" + nome;
  
  ptr_particle_pm.at(index) -> ptr_histo = new TH1F(new_nome.c_str(), nome.c_str(), bin_numb, minimo, massimo);


  return;
}
