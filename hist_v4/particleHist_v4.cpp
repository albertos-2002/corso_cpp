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

//per il file proxy creiamo un oggetto globale
//TFileProxy* ptr_tfileproxy = new TFileProxy("hist.root", "update");

int main ( int terminal_index, char* terminal_string[] ) {

  AnalysisInfo* ptr_analysisinfo = new AnalysisInfo( terminal_index, terminal_string );
  
  EventSource* ptr_eventsource = SourceFactory::create( ptr_analysisinfo );
  
  // create a list of analyzers
  vector<AnalysisSteering*> aList = AnalysisFactory::create( ptr_analysisinfo );

  // initialize all analyzers
  for ( auto as: aList ) as->beginJob();

  ptr_eventsource -> run();

  // finalize all analyzers
  for ( auto as: aList ) {
    as->endJob();
    delete as;
  }

  delete ptr_eventsource;

  return 0;

}

  
  
  
  
  
  
  
  
  
  
  
  
/*
  ParticleMass* ptr_partmass = new ParticleMass();


  //creazione degli oggetti massmean  
  ptr_partmass -> beginJob();

  //loop su tutti gli eventi
  const Event* eventclass_ptr;
  while( ( eventclass_ptr = ptr_eventsource -> get() ) != nullptr ){ 

  ptr_partmass -> process(*eventclass_ptr); //dereferencing

  }
    
  ptr_partmass -> endJob();
    
  delete ptr_partmass;
  delete ptr_eventsource;
  delete ptr_analysisinfo;


  
  return 0;
}
*/
