#ifndef class_massmean
#define class_massmean

class MassMean {

private:

  double min_invariant_mass;
  double max_invariant_mass;
  int selected_events = 0;
  double sum_masses;
  double sqr_sum_masses;
  double mean;
  double rms;
  double massa_tmp;

public:

  MassMean( double min_mass, double max_mass);

  ~MassMean();

  void add( const Event& evento_a );
  void compute();
  
  int nEvents();
  double mMean() const;
  double mRMS() const;

};

#endif
