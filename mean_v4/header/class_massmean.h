#ifndef class_massmean
#define class_massmean

#include "class_event.h"

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

  //costruttore
  MassMean( double min_mass, double max_mass);           

  //distruttore
  ~MassMean();

  void add( const Event& evento_a );


  void compute();

  int nEvents();

  double mMean() const;

  double mRMS() const;

};

#endif