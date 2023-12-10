#include "header/ParticleReco.h"
#include "header/class_event.h"
#include "header/class_constants.h"
#include "header/class_utilities.h"

#include <cmath>
#include <vector>
using namespace std;

ParticleReco::ParticleReco(){
}

ParticleReco::~ParticleReco(){
}

void ParticleReco::update( const Event& evento_m ){

//definizione delle variabili (è necessaria la reinizializzazione quindi le manteniamo in scope)

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

  if ( counter_positive_particles != 1 && counter_negative_particles != 1 ) return;

  invariantmass_K0 = Utilities::massa_invariante( sum_momentum_x, sum_momentum_y, sum_momentum_z, sum_energy_K0 );
  invariantmass_L0 = Utilities::massa_invariante( sum_momentum_x, sum_momentum_y, sum_momentum_z, sum_energy_L0 );

  double controllo_K0 = invariantmass_K0 - Constants::massK0;
  double controllo_L0 = invariantmass_L0 - Constants::massLambda0;

  if ( controllo_K0 < controllo_L0 ) {
    invariant_mass = invariantmass_K0;
    total_energy = sum_energy_K0;
    tipologia_decadimento = k0;
  }
  else{
    invariant_mass = invariantmass_L0;
    total_energy = sum_energy_L0;
    tipologia_decadimento = lambda;
  }

  distance = sqrt( pow( (evento_m.xdecay()) ,2) + pow( (evento_m.ydecay()) ,2) + pow( (evento_m.zdecay()) ,2) );

}

double ParticleReco::get_invariantmass(){
  return invariant_mass;
}
double ParticleReco::get_totalenergy(){
  return total_energy;
}
double ParticleReco::get_distance(){
  return distance;
}
