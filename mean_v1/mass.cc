#include "header/struct.h"
#include "header/funzioni.h"
using namespace std;

typedef const Particle* type_part_ptr;

double mass( const Event& evento ) {

  //definizione delle variabili
  int counter_positive_particles = 0;
  int counter_negative_particles = 0;

  double sum_momentum_x = 0;
  double sum_momentum_y = 0;
  double sum_momentum_z = 0;

  double sum_energy_K0 = 0;
  double sum_energy_L0 = 0;

  double invariantmass_K0 = 0;
  double invariantmass_L0 = 0;

  type_part_ptr tp_part_ptr;  

  //loop over Particles
  for(int i=0; i<evento.number_particles; ++i) {
      
      tp_part_ptr = evento.ptr_partstruct[i];                                             

      if ( tp_part_ptr -> electric_field > 0 ){
        counter_positive_particles += 1;
      }
      else{
        counter_negative_particles += 1;
      }

      sum_momentum_x += tp_part_ptr -> momentum_x;
      sum_momentum_y += tp_part_ptr -> momentum_y;
      sum_momentum_z += tp_part_ptr -> momentum_z;

      //calcolo energia ipotesi K0

      sum_energy_K0 += energia( tp_part_ptr -> momentum_x, tp_part_ptr -> momentum_y, tp_part_ptr -> momentum_z, massPion );

      //calcolo energia ipotesi L0

      if (tp_part_ptr -> electric_field > 0 ) {
        sum_energy_L0 += energia( tp_part_ptr -> momentum_x, tp_part_ptr -> momentum_y, tp_part_ptr -> momentum_z, massProton );
      }
      else {
        sum_energy_L0 += energia( tp_part_ptr -> momentum_x, tp_part_ptr -> momentum_y, tp_part_ptr -> momentum_z, massPion );
      }
  }

  if ( counter_positive_particles != 1 || counter_negative_particles != 1 ) return -1;

  invariantmass_K0 = massa_invariante( sum_momentum_x, sum_momentum_y, sum_momentum_z, sum_energy_K0 );
  invariantmass_L0 = massa_invariante( sum_momentum_x, sum_momentum_y, sum_momentum_z, sum_energy_L0 );

  double controllo_K0 = abs(invariantmass_K0 - massK0);
  double controllo_L0 = abs(invariantmass_L0 - massLambda0);

  if ( controllo_K0 < controllo_L0 ) {
    return invariantmass_K0;
  }
  else{
    return invariantmass_L0;
  }
  
}
