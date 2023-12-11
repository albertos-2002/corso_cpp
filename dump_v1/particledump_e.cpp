#include <iostream>
#include <fstream>

//piccolo controllo del numero di eventi totali del file
unsigned int total_number_of_events = 0;

int read( std::ifstream& reading_file_read, float& impact_x_read, float& impact_y_read, float& impact_z_read, int electric_field_read[], float momentum_x_read[], float momentum_y_read[], float momentum_z_read[])  {

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

//---------------------------------------
  total_number_of_events = total_number_of_events + 1;

return number_particles_read ;

}

//------------------------------------------------------------------------------

void dump( int& measure_id, float& impact_x, float& impact_y, float& impact_z, int& number_particles, int electric_field[], float momentum_x[], float momentum_y[], float momentum_z[]) {

std::cout << measure_id << std::endl;
std::cout << impact_x << " " << impact_y << " " << impact_z << std::endl;
std::cout << number_particles << std::endl;

for(int i=0; i<number_particles; i++) {

  std::cout << electric_field[i] << " " << momentum_x[i] << " " << momentum_y[i] << " " << momentum_z[i] << std::endl;

  }
}

//------------------------------------------------------------------------------

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

//-------------------------------------------------
  std::cout << "Il numero totale di eventi presenti nel file è:" << std::endl;
  std::cout << total_number_of_events << std::endl;

return 0;

}
