#ifndef class_event
#define class_event

class Event {

  private:                   //dichiarato on top per poter utilizzare le struct dentro la classe

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
  vector<Particle*> ptr_partstruct;

  //------------------------------------------------------------------------------------------------

  public:

  Event( int id_evento, float impatto_x, float impatto_y, float impatto_z):     //costruttore 

  event_id(id_evento),
  impact_x(impatto_x),
  impact_y(impatto_y),
  impact_z(impatto_z)
  {
    ptr_partstruct.reserve(10);		//al puntatore di puntatori alloco la memoria per 10 strutture particle
  }

  ~Event(){                                             //distruttore
    
    for (Particle* c : ptr_partstruct){
    delete c;
    }
    
    ptr_partstruct.clear();
    
  }

  //funzioni che aggiungono dati -------------------------------------------------------------------
  //aggiornata rispetto alle versioni precedenti
  //dare il controllo della creazione di una particle

  void add(int campo_elettrico, float momento_x, float momento_y, float momento_z, int& index){

      ptr_partstruct.push_back(new Particle);      
      
      ptr_partstruct.at(index) -> electric_field = campo_elettrico;
      ptr_partstruct.at(index) -> momentum_x = momento_x;
      ptr_partstruct.at(index) -> momentum_y = momento_y;
      ptr_partstruct.at(index) -> momentum_z = momento_z;

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
    return ptr_partstruct.size();
  }

  Particle* particles(int indexp) const {
    if(indexp < ptr_partstruct.size()) return ptr_partstruct.at(indexp);
    else return nullptr;
  }

};

#endif
