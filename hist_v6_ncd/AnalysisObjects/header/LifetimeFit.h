#ifndef LifetimeFit_h
#define LifetimeFit_h

#include "../../AnalysisFramework/header/class_event.h"
#include <vector>
#include <string>
using namespace std;

class LifetimeFit {

private:

  double min_invariant_mass;
  double max_invariant_mass;
  
  double min_time_range;
  double max_time_range;
  double min_scan_range;
  double max_scan_range;
  double scan_step;
  
  vector<double> decay_time_value;
  
  double mean_time;
  double error_time;

//--------------------------------------------------------------------------------------------------

public:

  LifetimeFit( double min_mass, double max_mass, double max_time, double min_time, double max_scan, double min_scan, double step_scan);           

  ~LifetimeFit();

  bool add( const Event& evento_a );
  
  void compute( string nome_grafico_parabola );
  
//funzioni per il return dei dati -------------------------------

  int nEvents();

  double get_lifeTime();

  double get_lifeTimeError();
  
};

#endif
