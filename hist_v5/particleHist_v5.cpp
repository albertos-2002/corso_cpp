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
#include "TFileProxy.h"
using namespace std;


int main( int argc, char* argv[] ) {

  // store command line parameters
  AnalysisInfo* info = new AnalysisInfo( argc, argv );

  // create data source
  EventSource* es = SourceFactory::create( info );

  // create a list of analyzers
  AnalysisFactory::create( info );

  // initialize all analyzers
  Dispatcher<AnalysisInfo::AnalysisStatus>::notify( AnalysisInfo::begin );

  // loop over events
  es->run();

  // finalize all analyzers
  Dispatcher<AnalysisInfo::AnalysisStatus>::notify( AnalysisInfo::end );

  delete es;

  return 0;

}



/*

int main ( int terminal_index, char* terminal_string[] ) {

  AnalysisInfo* ptr_analysisinfo = new AnalysisInfo( terminal_index, terminal_string );
  
  //puntatore ai derivati di EventSource
  EventSource* ptr_eventsource_derived = SourceFactory::create(ptr_analysisinfo);
  
//------------------------------------------------------------------------------------------------------
  
  //contenitore di puntatori agli analizzatori
  vector<AnalysisSteering*> aList = AnalysisFactory::create( ptr_analysisinfo );

//inizzializzazione degli analizzatori------------------------------------------------------
  for (auto c : aList){
    c -> beginJob();
  }

//inizzializzazione degli analizzatori------------------------------------------------------
  ptr_eventsource_derived -> run();

//calcolo e print dei risultati ------------------------------------------------------------
  for (auto c : aList){
    c -> endJob();
  }

//deallocazione della memoria --------------------------------------------------------------
  for (auto c : aList){
    delete c; 
  }
  aList.clear();

  delete ptr_eventsource_derived; 
  delete ptr_analysisinfo;

  return 0;
}

*/ 
