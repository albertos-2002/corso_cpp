#include <string>
#include <iostream>
#include <fstream>
#include "header/ParticleMass.h"
#include "header/EventSource.h"
#include "header/class_event.h"
#include "header/class_massmean.h"
#include "header/AnalysisInfo.h"
#include "header/SourceFactory.h"
#include "header/AnalysisFactory.h"
using namespace std;


int main( int terminal_index, char* terminal_string[] ) {

  AnalysisInfo* ptr_analysisinfo = new AnalysisInfo( terminal_index, terminal_string );
  
  //puntatore ai derivati di EventSource
  EventSource* ptr_eventsource_derived = SourceFactory::create(ptr_analysisinfo);

//------------------------------------------------------------------------------------------------------
  
  //contenitore di puntatori agli analizzatori
  AnalysisFactory::create( ptr_analysisinfo );
  
  // initialize all analyzers
  Dispatcher<AnalysisInfo::AnalysisStatus>::notify( AnalysisInfo::begin );

  // loop over events
  ptr_eventsource_derived->run();

  // finalize all analyzers
  Dispatcher<AnalysisInfo::AnalysisStatus>::notify( AnalysisInfo::end );

  delete ptr_eventsource_derived;
  delete ptr_analysisinfo;
  return 0;
}
