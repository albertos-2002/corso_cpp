#ifndef class_event
#define class_event

class Event {

  private:                                                                                          //dichiarato on top per poter utilizzare le struct dentro la classe

  struct Particle {

  int electric_field;
  float momentum_x;
  float momentum_y;
  float momentum_z;

  };

  int event_id;
  float impact_x;
  float impact_y;
  float impact_z;
  int number_particles;
  const static int max_number_particle = 10;
  Particle** ptr_partstruct;

  //------------------------------------------------------------------------------------------------

  public:

  Event( int id_evento, float impatto_x, float impatto_y, float impatto_z, int num_particelle):     //costruttore (ho aggiunto il numero di particelle)

  event_id(id_evento),
  impact_x(impatto_x),
  impact_y(impatto_y),
  impact_z(impatto_z),
  number_particles(num_particelle)
  {
    ptr_partstruct = new Particle*[max_number_particle];                                            //al puntatore di puntatori alloco la memoria per 10 strutture particle
    for (int i=0; i<max_number_particle; ++i){                                                      //setting di tutti i puntatori a "nullptr"
      ptr_partstruct[i] = nullptr;
    }
    for(int i=0; i<number_particles; ++i){
      ptr_partstruct[i] = new Particle;                                                             //per ogni particella presente alloco la memoria necessaria
    }
  }

  ~Event(){                                                                                         //distruttore

    for( int i = 0; i<10; ++i){
      delete ptr_partstruct[i];
    }
    delete ptr_partstruct;

  }

  //funzioni che aggiungono dati -------------------------------------------------------------------

  void add(int campo_elettrico, float momento_x, float momento_y, float momento_z, int& index){

    if (index < max_number_particle){
      ptr_partstruct[index] -> electric_field = campo_elettrico;
      ptr_partstruct[index] -> momentum_x = momento_x;
      ptr_partstruct[index] -> momentum_y = momento_y;
      ptr_partstruct[index] -> momentum_z = momento_z;
    }

    return;

  }

  //funzioni che ritornano i dati ------------------------------------------------------------------

  int eventNumber() const {
    return event_id;
  }

  float xdecay() const {
    return impact_x;
  }

  float ydecay() const {
    return impact_y;
  }

  float zdecay() const {
    return impact_z;
  }

  int nParticles() const {
    return number_particles;
  }

  Particle* particles(int indexp) const {
    if(indexp < number_particles) return ptr_partstruct[indexp];
    else return nullptr;
  }

};

#endif
