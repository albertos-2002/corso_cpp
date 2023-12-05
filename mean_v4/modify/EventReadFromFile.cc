#include "EventReadFromFile.h"

#include "Event.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) {
  file = new ifstream( name.c_str(), ios::binary );
}


EventReadFromFile::~EventReadFromFile() {
  delete file;
}


// get an event
const Event* EventReadFromFile::get() {
  return readFile();
}


// read an event (ex funzione read.h)
const Event* EventReadFromFile::readFile( ifstream& file_reading ) {

  Event* ptr_classevent;

  if ( !file_reading.eof() ) {

    file_reading >> event_id_r;
    file_reading >> impact_x_r;
    file_reading >> impact_y_r;
    file_reading >> impact_z_r;
    file_reading >> number_particles_r;

    ptr_classevent = new Event( event_id_r, impact_x_r, impact_y_r, impact_z_r);
	
    for (int i=0; i< number_particles_r; ++i) {

      file_reading >> electric_field_r;
      file_reading >> momentum_x_r;
      file_reading >> momentum_y_r;
      file_reading >> momentum_z_r;

      ptr_classevent -> add( electric_field_r, momentum_x_r, momentum_y_r, momentum_z_r, i);

    }

  }

  else return nullptr;

  return ptr_classevent; 

}

