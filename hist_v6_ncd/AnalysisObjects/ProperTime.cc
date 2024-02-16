#include "header/ProperTime.h"
#include "../../AnalysisFramework/header/class_event.h"
#include "../../AnalysisUtilities/header/class_constants.h"
#include "header/ParticleReco.h"
#include "LazyObserver.h"
#include "Singleton.h"
#include <cmath>
#include <vector>
using namespace std;

class ParticleReco;

ProperTime::ProperTime() : Singleton<ProperTime>(), LazyObserver<Event>() {
}

ProperTime::~ProperTime(){
}

void ProperTime::update(const Event& evento_m){

   static ParticleReco* ptr_particlereco_internal = ParticleReco::instance(); //ParticleReco è la ex funzione mass
   ptr_particlereco_internal -> update( evento_m );

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
