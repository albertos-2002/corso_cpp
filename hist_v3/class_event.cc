#include <vector>
#include "header/class_event.h"

using namespace std;

Event::Event( int id_evento, double impatto_x, double impatto_y, double impatto_z): 

  event_id(id_evento),
  impact_x(impatto_x),
  impact_y(impatto_y),
  impact_z(impatto_z)
  {
    ptr_partstruct.reserve(10);	     
  }
  
Event::~Event(){  

    for (Particle* c : ptr_partstruct){
    delete c;
    }
    
    ptr_partstruct.clear();
    
  }
  
//funzioni che aggiungono dati -------------------------------------------------------------------
  
  void Event::add(int campo_elettrico, double momento_x, double momento_y, double momento_z){

      ptr_partstruct.push_back(new Particle);
      int index = ptr_partstruct.size()-1;
      
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

  double Event::xdecay() const {
    return impact_x;
  }

  double Event::ydecay() const {
    return impact_y;
  }

  double Event::zdecay() const {
    return impact_z;
  }
  
  int Event::nParticles() const {
    return ptr_partstruct.size();
  }

  Event::Particle* Event::particles(unsigned int indexp) const {
    if(indexp < ptr_partstruct.size()) return ptr_partstruct.at(indexp);
    else return nullptr;
  }
