#include "header/EventSource.h"
#include "Dispatcher.h"


EventSource::EventSource() {
}


EventSource::~EventSource() {
}

void EventSource::run(){
  
  // loop over events
  const Event* ev;
  while ( ( ev = get() ) != nullptr ) {
    Dispatcher<Event>::notify( *ev );
    //delete ev;
  }  

  return;
}
