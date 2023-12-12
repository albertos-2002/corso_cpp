#include "header/struct.h"
#include <fstream>
using namespace std;

Event* read(ifstream& file_reading) {

  Event* eventptr_read = new Event;                                                                 

  if ( !file_reading.eof() ) {

    file_reading >> eventptr_read -> event_id;
    file_reading >> eventptr_read -> impact_x;
    file_reading >> eventptr_read -> impact_y;
    file_reading >> eventptr_read -> impact_z;
    file_reading >> eventptr_read -> number_particles;

    eventptr_read -> ptr_partstruct = new Particle*[eventptr_read -> number_particles];             

    for (int i=0; i<eventptr_read -> number_particles; ++i) {

      eventptr_read -> ptr_partstruct[i] = new Particle;                                            

      file_reading >> eventptr_read -> ptr_partstruct[i] -> electric_field;                         
      file_reading >> eventptr_read -> ptr_partstruct[i] -> momentum_x;
      file_reading >> eventptr_read -> ptr_partstruct[i] -> momentum_y;
      file_reading >> eventptr_read -> ptr_partstruct[i] -> momentum_z;
    }
  }
  else{
    return nullptr;                                                                              
  }
  
  return eventptr_read;                                                                          
}
