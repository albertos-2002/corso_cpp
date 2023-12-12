struct Particle {  

  int electric_field;
  float momentum_x;
  float momentum_y;
  float momentum_z;

};

struct Event {

  int event_id;
  float impact_x;
  float impact_y;
  float impact_z;
  int number_particles;
  Particle** ptr_partstruct;

};

const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

const float massMin = 0.490;
const float massMax = 0.505;
