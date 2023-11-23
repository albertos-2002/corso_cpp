
#include <iostream>
#include <fstream>

int read( const char* file_name, float& impact_x_read, float& impact_y_read, float& impact_z_read, int electric_field_read[], float momentum_x_read[], float momentum_y_read[], float momentum_z_read[], int& measure_id_read, int& cicle_point)  {

std::ifstream reading_file(file_name);
int number_particles_read = 0;

if (!reading_file.is_open()) {
  std::cout << "Errore apertura del file" << std::endl;
  return 1;
}

int row_counter = 1;
char carattere;

while(row_counter < cicle_point) {

  while(reading_file.get(carattere)) {
      if(carattere == '\n'){
          break;
      }
  }
  row_counter++;
}

reading_file >> measure_id_read;
reading_file >> impact_x_read;
reading_file >> impact_y_read;
reading_file >> impact_z_read;
reading_file >> number_particles_read;

cicle_point = 3 + cicle_point + number_particles_read;

for(int i=0; i<= number_particles_read; i++) {

  reading_file >> electric_field_read[i];
  reading_file >> momentum_x_read[i];
  reading_file >> momentum_y_read[i];
  reading_file >> momentum_z_read[i];

  }

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

//dichiarazione delle variabili

int measure_id = 0 ;
int number_particles = 0 ;

float impact_x = 0 ;
float impact_y = 0 ;
float impact_z = 0 ;

int electric_field[10];

float momentum_x[10];
float momentum_y[10];
float momentum_z[10];

int reading_row = 1;
int measure_id_ceck = -1;

std::ifstream reading_file(terminal_string[1]);

//cast per il passaggio alla funzione read
const char* nome_file = terminal_string[1];

while(reading_file.is_open()) {

number_particles = read(nome_file, impact_x, impact_y, impact_z, electric_field, momentum_x, momentum_y, momentum_z, measure_id, reading_row);


if (measure_id_ceck == measure_id){
   reading_file.close();
}
else {
    measure_id_ceck = measure_id;
    dump(measure_id, impact_x, impact_y, impact_z, number_particles, electric_field, momentum_x, momentum_y, momentum_z);
}

}

return 0;

}
