#ifndef class_event
#define class_event

#include <vector>

using namespace std;

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
  vector<Particle*> ptr_partstruct;

  //------------------------------------------------------------------------------------------------

  public:

  Event( int id_evento, float impatto_x, float impatto_y, float impatto_z); 

  ~Event();

  //funzioni che aggiungono dati -------------------------------------------------------------------

  void add(int campo_elettrico, float momento_x, float momento_y, float momento_z);

  //funzioni che ritornano i dati ------------------------------------------------------------------

  int eventNumber() const;

  float xdecay() const;

  float ydecay() const;

  float zdecay() const;
  
  int nParticles() const;

  Particle* particles(unsigned int indexp) const;

};

#endif
