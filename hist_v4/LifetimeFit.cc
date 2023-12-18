#include "header/LifetimeFit.h"
#include "header/class_event.h"
#include "header/ParticleReco.h"
#include <cmath>
using namespace std;

  LifetimeFit::LifetimeFit( double min_mass, double max_mass):    

  min_invariant_mass(min_mass),
  max_invariant_mass(max_mass)
  {
    selected_events = 0;
  }
  
  LifetimeFit::~LifetimeFit(){  }                  

  bool LifetimeFit::add( const Event& evento_a ){  

    //creazione istanza a particle reco, svolgimento della ex funzione mass e estrazione della massa invariante
   static ParticleReco* ptr_particlereco = ParticleReco::instance();
   ptr_particlereco -> update( evento_a );
    
    double massa_tmp;
    massa_tmp = ptr_particlereco -> get_invariantmass();
    
    if ( massa_tmp <= max_invariant_mass && massa_tmp >= min_invariant_mass ) {
      selected_events++ ;
      
      return true;
    }
    else{
      return false;
    }

  }


  int LifetimeFit::nEvents(){
    return selected_events;
  }
  
  void LifetimeFit::compute() {
    return;
  }
