#include "header/class_constants.h"
#include "header/class_utilities.h"
#include "header/class_event.h"

#include <cmath>
#include <vector>
using namespace std;

double mass( const Event& evento_m ) {

  int counter_positive_particles = 0;
  int counter_negative_particles = 0;

  double sum_momentum_x = 0;
  double sum_momentum_y = 0;
  double sum_momentum_z = 0;

  double sum_energy_K0 = 0;
  double sum_energy_L0 = 0;

  double invariantmass_K0 = 0;
  double invariantmass_L0 = 0;

//--------------------------------------------------------------------------------------------------

  //loop over Particles

  for(int i=0; i< evento_m.nParticles(); ++i) {

    if ( evento_m.particles(i) -> electric_field > 0 ){
      counter_positive_particles += 1;
    }
    else{
      counter_negative_particles += 1;
    }

    sum_momentum_x += evento_m.particles(i) -> momentum_x;
    sum_momentum_y += evento_m.particles(i) -> momentum_y;
    sum_momentum_z += evento_m.particles(i) -> momentum_z;

    //calcolo energia ipotesi K0

    sum_energy_K0 += Utilities::energia( evento_m.particles(i) -> momentum_x, evento_m.particles(i) -> momentum_y, evento_m.particles(i) -> momentum_z, Constants::massPion );

    //calcolo energia ipotesi L0

    if ( evento_m.particles(i) -> electric_field > 0 ) {
      sum_energy_L0 += Utilities::energia( evento_m.particles(i) -> momentum_x, evento_m.particles(i) -> momentum_y, evento_m.particles(i) -> momentum_z, Constants::massProton );
    }
    else {
      sum_energy_L0 += Utilities::energia( evento_m.particles(i) -> momentum_x, evento_m.particles(i) -> momentum_y, evento_m.particles(i) -> momentum_z, Constants::massPion );
    }

  }

  if ( counter_positive_particles != 1 || counter_negative_particles != 1 ) return -1;

  invariantmass_K0 = Utilities::massa_invariante( sum_momentum_x, sum_momentum_y, sum_momentum_z, sum_energy_K0 );
  invariantmass_L0 = Utilities::massa_invariante( sum_momentum_x, sum_momentum_y, sum_momentum_z, sum_energy_L0 );

  double controllo_K0 = abs(invariantmass_K0 - Constants::massK0);
  double controllo_L0 = abs(invariantmass_L0 - Constants::massLambda0);

  if ( controllo_K0 < controllo_L0 ) {
    return invariantmass_K0;
  }
  else{
    return invariantmass_L0;
  }

}
