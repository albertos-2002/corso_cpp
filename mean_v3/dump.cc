#include "header/class_event.h"
#include <iostream>
using namespace std;

void dump( const Event& event_dump ) {

  cout << event_dump.eventNumber() << endl;
  cout << event_dump.xdecay() << " " << event_dump.ydecay() << " " << event_dump.zdecay() << endl;
  cout << event_dump.nParticles() << endl;

  for( int i=0; i<event_dump.nParticles(); ++i ) {

    cout << event_dump.particles(i) -> electric_field << " " ;
    cout << event_dump.particles(i) -> momentum_x << " " << event_dump.particles(i) -> momentum_y << " " <<  event_dump.particles(i) -> momentum_z << endl;
   }

  return;
}
