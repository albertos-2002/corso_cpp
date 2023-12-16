#include "header/class_utilities.h"
#include <cmath>
using namespace std;

double Utilities::energia( const float& momento_x, const float& momento_y, const float& momento_z, const double& massa_invariante ) {

    double energia_particella;
    energia_particella = sqrt( (massa_invariante*massa_invariante) + ( (momento_x*momento_x)+(momento_y*momento_y)+(momento_z*momento_z) ) );

  return energia_particella;
  }

double Utilities::massa_invariante( double& momento_x, double& momento_y, double& momento_z, double& energia ) {

    double massa_invariante;
    massa_invariante = sqrt( (energia*energia) - ( (momento_x*momento_x)+(momento_y*momento_y)+(momento_z*momento_z) ) );

  return massa_invariante;
  }
