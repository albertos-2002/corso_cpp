#include "header/class_massmean.h"
#include "../AnalysisFramework/header/class_event.h"
#include "header/ParticleReco.h"
#include <cmath>
using namespace std;

  MassMean::MassMean( double min_mass, double max_mass):    

  min_invariant_mass(min_mass),
  max_invariant_mass(max_mass)
  {
    selected_events = 0;
    sum_masses = 0;
    sqr_sum_masses = 0;
    mean = 0;
    rms = 0;
    massa_tmp = 0;
    discarded_events = 0;
  }

  MassMean::~MassMean(){  }                  

  bool MassMean::add( const Event& evento_a ){  

    //creazione istanza a particle reco, svolgimento della ex funzione mass ed estrazione della massa invariante
    static ParticleReco* ptr_particlereco = ParticleReco::instance();
    ptr_particlereco -> update( evento_a );
    
    massa_tmp = ptr_particlereco -> get_invariantmass();
    
    if ( massa_tmp <= max_invariant_mass && massa_tmp >= min_invariant_mass ) {

      sum_masses += massa_tmp ;
      sqr_sum_masses += (massa_tmp*massa_tmp) ;
      selected_events++ ;
      
      return true;
    }
    else{
      discarded_events++;
      return false;
    }

  }

  void MassMean::compute() {

    mean = sum_masses / selected_events;
    rms = sqrt( (sqr_sum_masses / selected_events) - (mean*mean) ) ;

    return;
  }

  int MassMean::nEvents(){
    return selected_events;
  }

  double MassMean::mMean() const {
    return mean;
  }

  double MassMean::mRMS() const {
    if(rms > 0) return rms;
    else return 0;
  }
