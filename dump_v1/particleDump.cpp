#include <iostream>
#include <fstream>

int read( std::ifstream& reading_file_read, float& impact_x_read, float& impact_y_read, float& impact_z_read, int electric_field_read[], float momentum_x_read[], float momentum_y_read[], float momentum_z_read[]);
void dump( int& measure_id, float& impact_x, float& impact_y, float& impact_z, int& number_particles, int electric_field[], float momentum_x[], float momentum_y[], float momentum_z[]);

int main( int terminal_index, char* terminal_string[] ) {

  int measure_id = 0 ;
  int number_particles = 0 ;
  float impact_x = 0 ;
  float impact_y = 0 ;
  float impact_z = 0 ;
  int electric_field[10];
  float momentum_x[10];
  float momentum_y[10];
  float momentum_z[10];

  std::ifstream reading_file(terminal_string[1]);

  while(reading_file >> measure_id) {

    number_particles = read( reading_file, impact_x, impact_y, impact_z, electric_field, momentum_x, momentum_y, momentum_z);
    dump( measure_id, impact_x, impact_y, impact_z, number_particles, electric_field, momentum_x, momentum_y, momentum_z);
    }

  return 0;
}
