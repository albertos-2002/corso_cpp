#ifndef propertime_h
#define propertime_h

#include "../../util/include/Singleton.h"
#include "../../util/include/LazyObserver.h"
#include "../../AnalysisFramework/header/class_event.h"
#include "ParticleReco.h"

class ProperTime : public Singleton<ProperTime> , public LazyObserver<Event> {

  private:
  
  enum decay_type{
    lambda,
    k0
  };
  
  double total_energy;
  double invariant_mass;
  double time;
  
  public:
  
  ProperTime();
  ~ProperTime();
  
  void update(const Event& evento_m);
  
  decay_type tipologia_decadimento;
  
//funzioni che ritornano dati -----------------------------------------------
  
  double decayTime();
  
};

#endif
