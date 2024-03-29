#ifndef ParticleMass_h
#define ParticleMass_h 

#include <vector>
#include <iostream>
#include <string>
#include "class_massmean.h"
#include "AnalysisSteering.h"
#include "AnalysisInfo.h"
#include <TFile.h>
#include <TH1F.h>
#include "ActiveObserver.h"
#include "class_event.h"
using namespace std;

class ParticleMass : public AnalysisSteering, public ActiveObserver<Event> {

  private:
  
  struct Particle_pm {  
  
  string str_name;
  MassMean* ptr_massmean;
  TH1F* ptr_histo;
  
  };
  
  vector<Particle_pm*> ptr_particle_pm;  
  
  public:

  ParticleMass(const AnalysisInfo* info_arg);

  ~ParticleMass() override;
  
  // deleted copy constructor and assignment to prevent unadvertent copy
  ParticleMass           ( const ParticleMass& x ) = delete;
  ParticleMass& operator=( const ParticleMass& x ) = delete;

  void beginJob() override;
  
  void endJob() override;
  
  //la funzione fa riferimento a quella dell'observer
  void update( const Event& classe_evento ) override;
  
  void pCreate( const string& nome, float minimo, float massimo);

};

#endif
