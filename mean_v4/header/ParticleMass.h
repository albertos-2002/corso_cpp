#ifndef ParticleMass_h
#define ParticleMass_h 

#include <vector>
#include <iostream>
#include "class_massmean.h"
#include "AnalysisSteering.h"
using namespace std;

class ParticleMass : public AnalysisSteering {

  private:
  
  vector<MassMean*> ptr_massmean;
  
  public:

  ParticleMass();

  ~ParticleMass() override;
  
  // deleted copy constructor and assignment to prevent unadvertent copy
  ParticleMass           ( const ParticleMass& x ) = delete;
  ParticleMass& operator=( const ParticleMass& x ) = delete;

  void beginJob() override;
  
  void endJob() override;
  
  void process( const Event& classe_evento ) override;

};

#endif
