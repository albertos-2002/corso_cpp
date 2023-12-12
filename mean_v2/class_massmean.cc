#include <cmath>
#include "header/class_event.h"
#include "header/class_constants.h"
#include "header/class_utilities.h"
#include "header/class_massmean.h"
#include "header/funzioni.h"

class MassMean;

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
  }

  MassMean::~MassMean(){ 
  }                                                                                   

  void MassMean::add( const Event& evento_a ){

    massa_tmp = mass( evento_a );

    if ( massa_tmp <= max_invariant_mass && massa_tmp >= min_invariant_mass ) {

      sum_masses += massa_tmp ;
      sqr_sum_masses += (massa_tmp*massa_tmp) ;
      selected_events = selected_events +1 ;
    }
    
   return;
  }

  void MassMean::compute() {

    mean = sum_masses / selected_events;
    rms = sqrt( (sqr_sum_masses / selected_events) - (mean*mean) ) ;

    return;
  }
  
//funzioni per il return dei dati  

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
