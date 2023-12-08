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
  
  ParticleMass* ptr_partmass = new ParticleMass();
  
  if( process_decider == "input" ){
  
    string filename_str = terminal_string[2];
    
    EventReadFromFile* ptr_eventreadfromfile = new EventReadFromFile(filename_str);        

    //creazione degli oggetti massmean
    
    ptr_partmass -> beginJob();

    //loop su tutti gli eventi
    
    while( ptr_eventreadfromfile -> file_state() ){ 

    const Event* eventclass_ptr = ptr_eventreadfromfile -> readFile(); 

    ptr_partmass -> process(*eventclass_ptr); //dereferencing

    }
    
    ptr_partmass -> endJob();
    
    delete ptr_partmass;
    delete ptr_eventreadfromfile;    
  
  }
  else if( process_decider == "sim" ){
  
    string numeroeventi_str = terminal_string[2];
    string seednumber_str = terminal_string[3];
    
    unsigned int numeroeventi_numb = stoul(numeroeventi_str);
    unsigned int seednumber_numb = stoul(seednumber_str);
    
    EventSim* eventi_simulati = new EventSim( numeroeventi_numb, seednumber_numb);
    
    const Event* eventclass_simulazione;
    
    //creazione degli oggetti massmean
    ptr_partmass -> beginJob();
    
     while ( ( eventclass_simulazione = eventi_simulati->get() ) != nullptr ) {
  
    ptr_partmass -> process(*eventclass_simulazione); //dereferencing
    
    }
    
    ptr_partmass -> endJob();

    delete eventi_simulati;
    delete ptr_partmass;
  
  }
  else{
  
    cout << "keyword invalida" << endl;
    return -1;
  
  }

  return 0;

}
