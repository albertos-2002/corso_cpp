#include "header/struct.h"
#include <iostream>
using namespace std;

void dump( const Event& eventr_dump ) {

  cout << eventr_dump.event_id << endl;
  cout << eventr_dump.impact_x << " " << eventr_dump.impact_y << " " << eventr_dump.impact_z << endl;
  cout << eventr_dump.number_particles << endl;

  for( int i=0; i<eventr_dump.number_particles; ++i ) {

    cout << eventr_dump.ptr_partstruct[i] -> electric_field << " " ;
    cout << eventr_dump.ptr_partstruct[i] -> momentum_x << " " << eventr_dump.ptr_partstruct[i] -> momentum_y << " " <<  eventr_dump.ptr_partstruct[i] -> momentum_z << endl;
   }

  return;
}
