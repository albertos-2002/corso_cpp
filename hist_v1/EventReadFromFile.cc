#include "header/EventReadFromFile.h"
#include "header/class_event.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) {
  file = new ifstream( name );

  //controllo sul file
  //if (file -> is_open()) {cout << "ERFF:file aperto"<< endl;}
  if (file -> fail()) {cout << "ERFF:qualcosa è fallito" << endl;}
  
}


EventReadFromFile::~EventReadFromFile() {
  delete file;
}


// get an event
const Event* EventReadFromFile::get() {
  return readFile();
}

// read an event (ex funzione read.h)
const Event* EventReadFromFile::readFile() {
  
  Event* ptr_classevent;

  if ( !(*file).eof() ) {

    *file >> event_id_r;
    *file >> impact_x_r;
    *file >> impact_y_r;
    *file >> impact_z_r;
    *file >> number_particles_r;

    ptr_classevent = new Event( event_id_r, impact_x_r, impact_y_r, impact_z_r);
	
    for (int i=0; i< number_particles_r; ++i) {

      *file >> electric_field_r;
      *file >> momentum_x_r;
      *file >> momentum_y_r;
      *file >> momentum_z_r;

      ptr_classevent -> add( electric_field_r, momentum_x_r, momentum_y_r, momentum_z_r);      
    }
  }

  else{
    return nullptr;
  }
  
  return ptr_classevent; 
}
