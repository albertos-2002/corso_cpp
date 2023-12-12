#include "header/class_event.h"

class Event;

Event::Event( int id_evento, float impatto_x, float impatto_y, float impatto_z, int num_particelle):
  //costruttore (ho aggiunto il numero di particelle)
  event_id(id_evento),
  impact_x(impatto_x),
  impact_y(impatto_y),
  impact_z(impatto_z),
  number_particles(num_particelle)
  {
    ptr_partstruct = new Particle*[max_number_particle];   //al puntatore di puntatori alloco la memoria per 10 strutture particle
    for (int i=0; i<max_number_particle; ++i){             //setting di tutti i puntatori a "nullptr"
      ptr_partstruct[i] = nullptr;
    }
    for(int i=0; i<number_particles; ++i){
      ptr_partstruct[i] = new Particle;                   //per ogni particella presente alloco la memoria necessaria
    }
}

Event::~Event(){                                         

    for( int i = 0; i<10; ++i){
      delete ptr_partstruct[i];
    }
    delete[] ptr_partstruct;

}

void Event::add(int campo_elettrico, float momento_x, float momento_y, float momento_z, int& index){

    if (index < max_number_particle){
      ptr_partstruct[index] -> electric_field = campo_elettrico;
      ptr_partstruct[index] -> momentum_x = momento_x;
      ptr_partstruct[index] -> momentum_y = momento_y;
      ptr_partstruct[index] -> momentum_z = momento_z;
    }
    
  return;
}

//funzioni per il return dei dati

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
    return number_particles;
  }

  Event::Particle* Event::particles(int indexp) const {
    if(indexp < number_particles) return ptr_partstruct[indexp];
    else return nullptr;
  }
