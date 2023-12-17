#include "header/ProperTime.h"
#include "header/class_event.h"
#include "header/class_constants.h"
#include "header/class_utilities.h"
#include "header/ParticleReco.h"
#include "LazyObserver.h"
#include "Singleton.h"

#include <cmath>
#include <vector>
using namespace std;

ProperTime::ProperTime(const Event& evento_m) : Singleton<Event>(), LazyObserver<Event>() {
   ptr_particlereco_internal = new ParticleReco(); //ParticleReco è la ex funzione mass
   ptr_particlereco_internal -> update( evento_m );

}

ProperTime::~ProperTime(){
  delete ptr_particlereco_internal;
}

void ProperTime::update(const Event& evento_m){

//-------------------------------

//LazyObserver<Event>::check();

//-------------------------------

  double distanza = ptr_particlereco_internal->get_distance();
  double massa_invariante = ptr_particlereco_internal->get_invariantmass();
  double energia = ptr_particlereco_internal->get_totalenergy();
  double momento = sqrt( pow( energia ,2) - pow( massa_invariante ,2) );
  
  //calcolo del proper time
  time = ( distanza * massa_invariante ) / ( Constants::lightVelocity * momento ); 

  return;
}

double ProperTime::decayTime(){
  return time;
}
