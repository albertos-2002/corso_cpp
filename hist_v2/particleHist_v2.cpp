#include <string>
#include <iostream>
#include <fstream>
#include "header/ParticleMass.h"
#include "header/EventSource.h"
#include "header/class_event.h"
#include "header/class_massmean.h"
#include "header/AnalysisInfo.h"
#include "header/SourceFactory.h"

using namespace std;

int main ( int terminal_index, char* terminal_string[] ) {

  AnalysisInfo* ptr_analysisinfo = new AnalysisInfo( terminal_index, terminal_string );
  
  EventSource* ptr_eventsource = SourceFactory::create( ptr_analysisinfo );
  
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
