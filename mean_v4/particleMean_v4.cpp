#include <string>
#include <iostream>
#include <fstream>
#include "header/ParticleMass.h"
#include "header/AnalysisSteering.h"
#include "header/EventSource.h"
#include "header/EventDump.h"
#include "header/EventReadFromFile.h"
#include "header/EventSim.h"
#include "header/class_constants.h"
#include "header/class_event.h"
#include "header/class_massmean.h"
#include "header/class_utilities.h"
#include "header/funzioni.h"
using namespace std;

int main ( int terminal_index, char* terminal_string[] ) {

  string process_decider = terminal_string[1];
  
  //puntatore ai derivati di EventSource
  EventSource* ptr_eventsource_derived;
  
//controllo su input / sim ---------------------------------------------------------------------------

  if( process_decider == "input" ){
  
    string filename_str = terminal_string[2];
    
    //puntatore alla classe che si occupa di leggere il file
    ptr_eventsource_derived = new EventReadFromFile(filename_str);

  }
  else if( process_decider == "sim" ){
  
    string numeroeventi_str = terminal_string[2];
    string seednumber_str = terminal_string[3];
    
    unsigned int numeroeventi_numb = stoul(numeroeventi_str);
    unsigned int seednumber_numb = stoul(seednumber_str);
    
    //puntatore alla classe che si occupa di simulazre gli eventi
    ptr_eventsource_derived = new EventSim( numeroeventi_numb, seednumber_numb);  
    
  }
  else{
    cout << "keyword invalida" << endl;
    return -1;
  }
  
//------------------------------------------------------------------------------------------------------
  
  //contenitore di puntatori agli analizzatori
  vector<AnalysisSteering*> aList;
  aList.push_back(new ParticleMass());  //creazione analizzatore di tipo ParticleMass
  aList.push_back(new EventDump());     //creazione analizzatore di tipo dump 
  
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
  delete ptr_eventsource_derived;
  for (auto c : aList){
    delete c; 
  }
  aList.clear();

  return 0;
}
