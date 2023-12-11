#include <fstream>

int read( std::ifstream& reading_file_read, float& impact_x_read, float& impact_y_read, float& impact_z_read, int electric_field_read[], float momentum_x_read[], float momentum_y_read[], float momentum_z_read[]) {

  int number_particles_read;

  reading_file_read >> impact_x_read;
  reading_file_read >> impact_y_read;
  reading_file_read >> impact_z_read;
  reading_file_read >> number_particles_read;

  for(int i=0; i< number_particles_read; i++) {

    reading_file_read >> electric_field_read[i];
    reading_file_read >> momentum_x_read[i];
    reading_file_read >> momentum_y_read[i];
    reading_file_read >> momentum_z_read[i];
   }
   
  return number_particles_read ;
}

