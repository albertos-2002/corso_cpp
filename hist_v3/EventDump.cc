#include "header/EventDump.h"
#include "header/class_event.h"
#include "header/AnalysisInfo.h"
#include "header/AnalysisFactory.h"
#include <iostream>
using namespace std;

//from eventdump of bragplotv3 --------------------------------------------------------------------------------------------------------

// concrete factory to create an EventDump analyzer
class EventDumpFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "dump" as name for this analyzer and factory
  EventDumpFactory(): AnalysisFactory::AbsFactory( "dump" ) {}
  // create an EventDump when builder is run
  AnalysisSteering* create( const AnalysisInfo* info ) override {
    return new EventDump( info );
  }
  
};
// create a global EventDumpFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;

//-------------------------------------------------------------------------------------------------------------------------------------

EventDump::EventDump(const AnalysisInfo* info_arg): AnalysisSteering(info_arg){
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
