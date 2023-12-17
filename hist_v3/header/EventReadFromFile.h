#ifndef EventReadFromFile_h
#define EventReadFromFile_h

#include "EventSource.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Event;

class EventReadFromFile: public EventSource {

 public:

  // read data from file "name"
  EventReadFromFile( const std::string& name );
  // deleted copy constructor and assignment to prevent unadvertent copy
  EventReadFromFile           ( const EventReadFromFile& x ) = delete;
  EventReadFromFile& operator=( const EventReadFromFile& x ) = delete;

  ~EventReadFromFile() override;

 private:

  // read and event  
  const Event* readFile();

  // get an event
  const Event* get() override;

  // input file
  std::ifstream* file;  
  
  
  float event_id_r = 0;
  float impact_x_r = 0;
  float impact_y_r = 0;
  float impact_z_r = 0;
  int electric_field_r = 0;
  float momentum_x_r = 0;
  float momentum_y_r = 0;
  float momentum_z_r = 0;
  int number_particles_r = 0;

};

#endif
