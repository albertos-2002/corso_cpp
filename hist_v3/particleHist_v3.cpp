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

int main ( int terminal_index, char* terminal_string[] ) {

  AnalysisInfo* ptr_analysisinfo = new AnalysisInfo(terminal_index, terminal_string);
  
  //puntatore ai derivati di EventSource
  EventSource* ptr_eventsource_derived = SourceFactory::create(ptr_analysisinfo);
  
//------------------------------------------------------------------------------------------------------
  
  //contenitore di puntatori agli analizzatori
  vector<AnalysisSteering*> aList = AnalysisFactory::create( ptr_analysisinfo );
  
//inizzializzazione degli analizzatori------------------------------------------------------
  for (auto c : aList){
    c -> beginJob();
  }
  
  //puntatore alla classe event
  const Event* eventclass_ptr;
  
//loop su tutti gli eventi -----------------------------------------------------------------
  while( ( eventclass_ptr = ptr_eventsource_derived -> get() ) != nullptr ){ 

    //chiamata alla funzione "analizzatrice" degli analizzatori
    for (auto c : aList){
      c -> process(*eventclass_ptr);
    }
  }
  
  
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
