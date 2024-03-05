#ifndef particlereco_h
#define particlereco_h

#include "Singleton.h"
#include "LazyObserver.h"
#include "class_event.h"

class ParticleReco : public Singleton<ParticleReco> , public LazyObserver<Event> {

friend class Singleton<ParticleReco>;

  private:
  
  decay type_enum{
    lambda,
    k0,
    default_reset
  };
  
  double total_energy;
  double invariant_mass;
  double distance;
  
  //public:
  
  //costruttore privato in modo da non poter creare una istanza che non sia singleton
  ParticleReco();
  
  ParticleReco           ( const ParticleReco& x ) = delete;
  ParticleReco& operator=( const ParticleReco& x ) = delete;
  
  ~ParticleReco() override;
  
  public:
  
  void update( const Event& evento_m ) override;
  
  decay_type tipologia_decadimento;
  
  double get_invariantmass();
  double get_totalenergy();
  double get_distance();

};

#endif
