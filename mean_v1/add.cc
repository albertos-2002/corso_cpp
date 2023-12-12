#include "header/struct.h"
#include "header/funzioni.h"

bool add( const Event& evento, const float& massMin, const float& massMax, double& sum_masse_invarianti, double& sqr_sum_masse_invarianti ) {

  double massa_invariante_test = 0;

  massa_invariante_test = mass( evento );

  if (massa_invariante_test < massMax && massa_invariante_test > massMin){

    sum_masse_invarianti += massa_invariante_test;
    sqr_sum_masse_invarianti += (massa_invariante_test*massa_invariante_test); 

    return true;
  }

  return false;
}
