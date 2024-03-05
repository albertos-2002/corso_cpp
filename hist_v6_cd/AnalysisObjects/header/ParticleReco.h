#ifndef particlereco_h
#define particlereco_h

#include "Singleton.h"
#include "LazyObserver.h"
#include "../../AnalysisFramework/header/class_event.h"

class ParticleReco : public Singleton<ParticleReco> , public LazyObserver<Event> {
friend class Singleton<ParticleReco>;

  private:
  
  enum decay_type{
    lambda,
    k0,
    default_reset
  };
  
  double total_energy;
  double invariant_mass;
  double distance;
  
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
