#ifndef particlereco_h
#define particlereco_h

#include "Singleton.h"
#include "LazyObserver.h"
#include "class_event.h"

class ParticleReco : public Singleton<Event> , public LazyObserver<Event> {

  private:
  
  enum decay_type{
    lambda,
    k0
  };
  
  double total_energy;
  double invariant_mass;
  double distance;
  
  public:
  
  ParticleReco();
  ~ParticleReco();
  
  void update( const Event& evento_m );
  
  decay_type tipologia_decadimento;
  
  double get_invariantmass();
  double get_totalenergy();
  double get_distance();

};

#endif
