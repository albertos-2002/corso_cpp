#ifndef propertime_h
#define propertime_h

#include "Singleton.h"
#include "LazyObserver.h"
#include "../../AnalysisFramework/header/class_event.h"
#include "ParticleReco.h"

class ProperTime : public Singleton<ProperTime> , public LazyObserver<Event> {
friend class Singleton<ProperTime>;

  private:
  
  enum decay_type{
    lambda,
    k0
  };
  
  double total_energy;
  double invariant_mass;
  double time;
  
  ProperTime();
  ProperTime           ( const ProperTime& x ) = delete;
  ProperTime& operator=( const ProperTime& x ) = delete;
  ~ProperTime();
  
  public:
  
  void update(const Event& evento_m);
  
  decay_type tipologia_decadimento;
  
//funzioni che ritornano dati -----------------------------------------------
  
  double decayTime();
  
};

#endif
