#include <iostream>

void dump( int& measure_id, float& impact_x, float& impact_y, float& impact_z, int& number_particles, int electric_field[], float momentum_x[], float momentum_y[], float momentum_z[]) {

  std::cout << measure_id << std::endl;
  std::cout << impact_x << " " << impact_y << " " << impact_z << std::endl;
  std::cout << number_particles << std::endl;

  for(int i=0; i<number_particles; i++) {

    std::cout << electric_field[i] << " " << momentum_x[i] << " " << momentum_y[i] << " " << momentum_z[i] << std::endl;
    }
  return;
}
