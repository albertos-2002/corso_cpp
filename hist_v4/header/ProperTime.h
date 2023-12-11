#ifndef propertime_h
#define propertime_h

#include "Singleton.h"
#include "LazyObserver.h"
#include "class_event.h"
#include "ParticleReco.h"

class ProperTime /*: public Singleton<Event> , public LazyObserver<Event>*/ {

  private:
  
  enum decay_type{
    lambda,
    k0
  };
  
  double total_energy;
  double invariant_mass;
  
  double time;
  
  ParticleReco* ptr_particlereco_internal;
  
  public:
  
  ProperTime(const Event& evento_m);
  ~ProperTime();
  
  void update();
  
  decay_type tipologia_decadimento;
  
  double decayTime();
  
};

#endif