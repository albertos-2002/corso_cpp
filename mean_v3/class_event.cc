#include <vector>
#include "header/class_event.h"

using namespace std;

//costruttore
Event::Event( int id_evento, float impatto_x, float impatto_y, float impatto_z): 

  event_id(id_evento),
  impact_x(impatto_x),
  impact_y(impatto_y),
  impact_z(impatto_z)
  {
    ptr_partstruct.reserve(10);	    //al puntatore di puntatori alloco la memoria per 10 strutture particle
  }

//distruttore
Event::~Event(){  

    for (Particle* c : ptr_partstruct){
    delete c;
    }
    
    ptr_partstruct.clear();
    
  }
  
//funzioni che aggiungono dati -------------------------------------------------------------------
  
  void Event::add(int campo_elettrico, float momento_x, float momento_y, float momento_z, int& index){

      ptr_partstruct.push_back(new Particle);      
      
      ptr_partstruct.at(index) -> electric_field = campo_elettrico;
      ptr_partstruct.at(index) -> momentum_x = momento_x;
      ptr_partstruct.at(index) -> momentum_y = momento_y;
      ptr_partstruct.at(index) -> momentum_z = momento_z;

    return;

  }
  
//funzioni che ritornano i dati ------------------------------------------------------------------

  int Event::eventNumber() const {
    return event_id;
  }

  float Event::xdecay() const {
    return impact_x;
  }

  float Event::ydecay() const {
    return impact_y;
  }

  float Event::zdecay() const {
    return impact_z;
  }
  
  int Event::nParticles() const {
    return ptr_partstruct.size();
  }

  Event::Particle* Event::particles(int indexp) const {
    if(indexp < ptr_partstruct.size()) return ptr_partstruct.at(indexp);
    else return nullptr;
  }