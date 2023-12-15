#ifndef class_event
#define class_event

#include <vector>

using namespace std;

class Event {

  private:      

  struct Particle {

  int electric_field;
  double momentum_x;
  double momentum_y;
  double momentum_z;

  };

  int event_id;
  double impact_x;
  double impact_y;
  double impact_z;
  vector<Particle*> ptr_partstruct;

  //------------------------------------------------------------------------------------------------

  public:

  Event( int id_evento, double impatto_x, double impatto_y, double impatto_z); 
  
  ~Event();

  //funzioni che aggiungono dati -------------------------------------------------------------------

  void add(int campo_elettrico, double momento_x, double momento_y, double momento_z);

  //funzioni che ritornano i dati ------------------------------------------------------------------

  int eventNumber() const;

  double xdecay() const;

  double ydecay() const;

  double zdecay() const;
  
  int nParticles() const;

  Particle* particles(unsigned int indexp) const;

};

#endif
