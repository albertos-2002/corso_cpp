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

  MassMean( double min_mass, double max_mass);           

  ~MassMean();

  bool add( const Event& evento_a );  //cambiata a bool


  void compute();

  int nEvents();

  double mMean() const;

  double mRMS() const;

};

#endif
