#ifndef class_event
#define class_event

class Event {

  private:                                                                           

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

  public:

  Event( int id_evento, float impatto_x, float impatto_y, float impatto_z, int num_particelle);     //costruttore (ho aggiunto il numero di particelle)

  ~Event();

  //funzioni che aggiungono dati -------------------------------------------------------------------

  void add(int campo_elettrico, float momento_x, float momento_y, float momento_z, int& index);

  //funzioni che ritornano i dati ------------------------------------------------------------------

  int eventNumber() const;
  float xdecay() const;
  float ydecay() const;
  float zdecay() const;
  int nParticles() const;
  Particle* particles(int indexp) const;

};

#endif
