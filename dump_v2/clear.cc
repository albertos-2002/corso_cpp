#include "header/struct.h"
using namespace std;

void clear( Event* ptrdel ) {

   for(int i=0; i < ptrdel -> number_particles; ++i) {

     delete ptrdel -> ptr_partstruct[i];

   }

   delete ptrdel -> ptr_partstruct;
   delete ptrdel;

}
