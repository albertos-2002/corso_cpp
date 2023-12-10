#include "header/ProperTime.h"
#include "header/class_event.h"
#include "header/class_constants.h"
#include "header/class_utilities.h"
#include "header/ParticleReco.h"

#include <cmath>
#include <vector>
using namespace std;

ProperTime::ProperTime(const Event& evento_m) {
   ParticleReco* ptr_particlereco_internal = new ParticleReco(); //particle reco è la ex funzione mass, mi calcola i valori di mass ecc
   ptr_particlereco_internal -> update( evento_m );

}

ProperTime::~ProperTime(){
  delete ptr_particlereco_internal;
}

void ProperTime::update( ){
  
  //calcolo del proper time
  time = ( ( ptr_particlereco_internal->get_distance() ) * (ptr_particlereco_internal->get_invariantmass()) ) / ( (Constants::lightVelocity) * (sqrt( pow((ptr_particlereco_internal->get_totalenergy()),2) - pow((ptr_particlereco_internal->get_invariantmass()),2) )) ); 

  //bisogna inserire la distanza in qualche modo
  return;
}

double ProperTime::decayTime(){
  return time;
}
