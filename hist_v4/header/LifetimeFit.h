#ifndef LifetimeFit_h
#define LifetimeFit_h

#include "class_event.h"

using namespace std;

class LifetimeFit {

private:

  double min_invariant_mass;
  double max_invariant_mass;
  int selected_events;

//--------------------------------------------------------------------------------------------------

public:

  LifetimeFit( double min_mass, double max_mass);           

  ~LifetimeFit();

  bool add( const Event& evento_a );  

  int nEvents();
  
  void compute();

};

#endif
