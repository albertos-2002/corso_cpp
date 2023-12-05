#include "EventDump.h"
#include "Event.h"
#include <iostream>

using namespace std;

EventDump::EventDump() {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  return;
}


// function to be called for each event ( es funzione dump.h )
void EventDump::process( const Event& event_dump ) {

  cout << event_dump.eventNumber() << endl;
  cout << event_dump.xdecay() << " " << event_dump.ydecay() << " " << event_dump.zdecay() << endl;
  cout << event_dump.nParticles() << endl;

  for( int i=0; i<event_dump.nParticles(); ++i ) {

    cout << event_dump.particles(i) -> electric_field << " " ;
    cout << event_dump.particles(i) -> momentum_x << " " << event_dump.particles(i) -> momentum_y << " " <<  event_dump.particles(i) -> momentum_z << endl;

   }

  return;

}

