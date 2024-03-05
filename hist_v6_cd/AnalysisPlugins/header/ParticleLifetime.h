#ifndef ParticleLifetime_h
#define ParticleLifetime_h 

#include <vector>
#include <iostream>
#include <string>
#include "../../AnalysisObjects/header/LifetimeFit.h"
#include "../../AnalysisFramework/header/AnalysisSteering.h"
#include "../../AnalysisFramework/header/AnalysisInfo.h"
#include <TFile.h>
#include <TH1F.h>
#include "ActiveObserver.h"
#include "../../AnalysisFramework/header/class_event.h"
using namespace std;


class ParticleLifetime : public AnalysisSteering, public ActiveObserver<Event> {

  private:
  
  struct Particle_pm { 
  
  string str_name;
  LifetimeFit* ptr_lifetime;
  TH1F* ptr_histo;
  
  };
  
  vector<Particle_pm*> ptr_particle_lt;  
  
  public:

  ParticleLifetime(const AnalysisInfo* info_arg);

  ~ParticleLifetime() override;
  
  // deleted copy constructor and assignment to prevent unadvertent copy
  ParticleLifetime           ( const ParticleLifetime& x ) = delete;
  ParticleLifetime& operator=( const ParticleLifetime& x ) = delete;

  void beginJob() override;
  
  void endJob() override;
  
  void update( const Event& classe_evento );
  
  void pCreate( string& nome, float minimo, float massimo, float minimo_tempo, float massimo_tempo, float minimo_scan, float massimo_scan, float step);

};

#endif
