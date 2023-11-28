#ifndef class_massmean
#define class_massmean

#include <cmath>
using namespace std;

class MassMean {

private:

  double min_invariant_mass;
  double max_invariant_mass;
  int selected_events;
  double sum_masses;
  double sqr_sum_masses;
  double mean;
  double rms;
  double massa_tmp;

//--------------------------------------------------------------------------------------------------

public:

  MassMean( double min_mass, double max_mass):            //costruttore

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

  ~MassMean(){  }                      //distruttore

  void add( const Event& evento_a ){

    massa_tmp = mass( evento_a );

    if ( massa_tmp <= max_invariant_mass && massa_tmp >= min_invariant_mass ) {

      sum_masses += massa_tmp ;
      sqr_sum_masses += (massa_tmp*massa_tmp) ;
      selected_events++ ;

    }

    return;

  }

  void compute() {

    mean = sum_masses / selected_events;
    rms = sqrt( (sqr_sum_masses / selected_events) - (mean*mean) ) ;

    return;

  }

  int nEvents(){
    return selected_events;
  }

  double mMean() const {
    return mean;
  }

  double mRMS() const {
    if(rms > 0) return rms;
    else return 0;
  }

};

#endif