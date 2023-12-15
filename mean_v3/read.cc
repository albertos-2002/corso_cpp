#include "header/class_event.h"
#include <fstream>
using namespace std;

  float event_id_r = 0;
  float impact_x_r = 0;
  float impact_y_r = 0;
  float impact_z_r = 0;
  int electric_field_r = 0;
  float momentum_x_r = 0;
  float momentum_y_r = 0;
  float momentum_z_r = 0;
  int number_particles_r = 0;

//--------------------------------------------------------------------------------------------------

Event* read(ifstream& file_reading) {

  Event* ptr_classevent;

  if ( !file_reading.eof() ) {

    file_reading >> event_id_r;
    file_reading >> impact_x_r;
    file_reading >> impact_y_r;
    file_reading >> impact_z_r;
    file_reading >> number_particles_r;

    ptr_classevent = new Event( event_id_r, impact_x_r, impact_y_r, impact_z_r);  
	
    for (int i=0; i< number_particles_r; ++i) {

      file_reading >> electric_field_r;
      file_reading >> momentum_x_r;
      file_reading >> momentum_y_r;
      file_reading >> momentum_z_r;

      ptr_classevent -> add( electric_field_r, momentum_x_r, momentum_y_r, momentum_z_r);
    }
  }

  else{
  return nullptr;   
  }
  
  return ptr_classevent;
};
