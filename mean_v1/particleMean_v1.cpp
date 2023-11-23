#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

//definizione delle strutture e delle variabili globali

struct Particle {                                                                                   // stessa dimensione della versione 1

  int electric_field;
  float momentum_x;
  float momentum_y;
  float momentum_z;

};

struct Event {

  int event_id;
  float impact_x;
  float impact_y;
  float impact_z;
  int number_particles;
  Particle** ptr_partstruct;                                                                        //incomplete type declaration; crea un puntatore che punta a un array di puntatori a strutture particle

};

const double massPion    = 0.1395706;   // GeV/c^2
const double massProton  = 0.938272;    // GeV/c^2
const double massK0      = 0.497611;    // GeV/c^2
const double massLambda0 = 1.115683;    // GeV/c^2

const float massMin = 0.490;
const float massMax = 0.505;

typedef const Particle* type_part_ptr;

//--------------------------------------------------------------------------------------------------

//definizione delle funzioni necessarie alla computazione

//funzione per la lettura dei valori dal file sorgente

Event* read(ifstream& file_reading) {

  Event* eventptr_read = new Event;                                                                 //alloco la memoria per un "Event", la assegno ad un puntatore (devo accedere con ->)

  if ( !file_reading.eof() ) {

    file_reading >> eventptr_read -> event_id;
    file_reading >> eventptr_read -> impact_x;
    file_reading >> eventptr_read -> impact_y;
    file_reading >> eventptr_read -> impact_z;
    file_reading >> eventptr_read -> number_particles;

    eventptr_read -> ptr_partstruct = new Particle*[eventptr_read -> number_particles];             //al "puntatore di puntatori" ho allocato un numero di puntatori a "Particle" pari al numero di particelle

    for (int i=0; i<eventptr_read -> number_particles; ++i) {

      eventptr_read -> ptr_partstruct[i] = new Particle;                                            //nel ciclo alloco ad ogni puntatore del "puntatore di puntatori" una memoria pari ad una "Particle"

      file_reading >> eventptr_read -> ptr_partstruct[i] -> electric_field;                         //scrivo dentro la "Particle" con (doppio accesso)
      file_reading >> eventptr_read -> ptr_partstruct[i] -> momentum_x;
      file_reading >> eventptr_read -> ptr_partstruct[i] -> momentum_y;
      file_reading >> eventptr_read -> ptr_partstruct[i] -> momentum_z;

    }

  }

  else return nullptr;                                                                              //se siamo alla fine del file ritorniamo un puntatore nullo

  return eventptr_read;                                                                             //ritornando il puntatore ritorno per così dire la memoria

}

//funzione per la pulizia della memoria dinamica

void clear( Event* ptrdel ) {

  for(int i=0; i < ptrdel -> number_particles; ++i) {

  delete ptrdel -> ptr_partstruct[i];                                                               //elimina i puntatori e di conseguenza le stutture "Particle" contenute nel "puntatore di puntatori"

  }

  delete ptrdel -> ptr_partstruct;                                                                  //elimina il puntatore che contine i puntatori e quindi lo spazio di memori che contiene i suddetti puntatori
  delete ptrdel;                                                                                    //elimina il putatore a Event, eliminado anche lo spazio di memoria associato ad Event

}

//funzione per il printing del file sul cout (autoesplicativa)

void dump( const Event& eventr_dump ) {

  cout << eventr_dump.event_id << endl;
  cout << eventr_dump.impact_x << " " << eventr_dump.impact_y << " " << eventr_dump.impact_z << endl;
  cout << eventr_dump.number_particles << endl;

  for( int i=0; i<eventr_dump.number_particles; ++i ) {

    cout << eventr_dump.ptr_partstruct[i] -> electric_field << " " ;
    cout << eventr_dump.ptr_partstruct[i] -> momentum_x << " " << eventr_dump.ptr_partstruct[i] -> momentum_y << " " <<  eventr_dump.ptr_partstruct[i] -> momentum_z << endl;

   }

}

//definizione della funzione che calcola l'energia

double energia( const float& momento_x, const float& momento_y, const float& momento_z, const double& massa_invariante ) {

  double energia_particella;
  energia_particella = sqrt( (massa_invariante*massa_invariante) + ( (momento_x*momento_x)+(momento_y*momento_y)+(momento_z*momento_z) ) );

  return energia_particella;

}

//definizione della funzione che calcola la massa invariante

double massa_invariante( double& momento_x, double& momento_y, double& momento_z, double& energia ) {

  double massa_invariante;
  massa_invariante = sqrt( (energia*energia) - ( (momento_x*momento_x)+(momento_y*momento_y)+(momento_z*momento_z) ) );

  return massa_invariante;

}

//definizione della funzione mass

double mass( const Event& evento ) {

  //definizione delle variabili

  int counter_positive_particles = 0;
  int counter_negative_particles = 0;

  /*float*/ double sum_momentum_x = 0;
  /*float*/ double sum_momentum_y = 0;
  /*float*/ double sum_momentum_z = 0;

  /*float*/ double sum_energy_K0 = 0;
  /*float*/ double sum_energy_L0 = 0;

  /*float*/ double invariantmass_K0 = 0;
  /*float*/ double invariantmass_L0 = 0;

  type_part_ptr tp_part_ptr;  

  //loop over Particles

  for(int i=0; i<evento.number_particles; ++i) {
      
    tp_part_ptr = evento.ptr_partstruct[i];                                             

    if ( tp_part_ptr -> electric_field > 0 ){
      counter_positive_particles += 1;
    }
    else{
      counter_negative_particles += 1;
    }

    sum_momentum_x += tp_part_ptr -> momentum_x;
    sum_momentum_y += tp_part_ptr -> momentum_y;
    sum_momentum_z += tp_part_ptr -> momentum_z;

    //calcolo energia ipotesi K0

    sum_energy_K0 += energia( tp_part_ptr -> momentum_x, tp_part_ptr -> momentum_y, tp_part_ptr -> momentum_z, massPion );

    //calcolo energia ipotesi L0

    if (tp_part_ptr -> electric_field > 0 ) {
      sum_energy_L0 += energia( tp_part_ptr -> momentum_x, tp_part_ptr -> momentum_y, tp_part_ptr -> momentum_z, massProton );
    }
    else {
      sum_energy_L0 += energia( tp_part_ptr -> momentum_x, tp_part_ptr -> momentum_y, tp_part_ptr -> momentum_z, massPion );
    }

  }

  if ( counter_positive_particles != 1 && counter_negative_particles != 1 ) return -1;

  invariantmass_K0 = massa_invariante( sum_momentum_x, sum_momentum_y, sum_momentum_z, sum_energy_K0 );
  invariantmass_L0 = massa_invariante( sum_momentum_x, sum_momentum_y, sum_momentum_z, sum_energy_L0 );

  double controllo_K0 = invariantmass_K0 - massK0;
  double controllo_L0 = invariantmass_L0 - massLambda0;

  if ( controllo_K0 < controllo_L0 ) {
    return invariantmass_K0;
  }
  else{
    return invariantmass_L0;
  }

}

//definizione della funzione add

bool add( const Event& evento, const float& massMin, const float& massMax, double& sum_masse_invarianti, double& sqr_sum_masse_invarianti ) {

  double massa_invariante_test = 0;

  massa_invariante_test = mass( evento );

  if (massa_invariante_test < massMax && massa_invariante_test > massMin){

    sum_masse_invarianti += massa_invariante_test;
    sqr_sum_masse_invarianti += (massa_invariante_test*massa_invariante_test);
    return true;

  }

  return false;

}

//--------------------------------------------------------------------------------------------------

//definizione del main

int main( int terminal_index, char* terminal_string[] ) {

  ifstream reading_file(terminal_string[1]);

  int numero_eventi_accettati = 0;
  double sum_masse_invarianti = 0;
  double sqr_sum_masse_invarianti = 0;
  double mean_masse_invarianti = 0;
  double rms_masse_invarianti = 0;
  double rms_partial = 0;



  if( !reading_file.is_open() ) return 1;                                                           // controllo apertura file

  while( !reading_file.eof() ){

    Event* event_ptr = read( reading_file );

    if ( add( *event_ptr, massMin, massMax, sum_masse_invarianti, sqr_sum_masse_invarianti ) ){
        numero_eventi_accettati += 1;
    }

//  dump( *event_ptr );                                                                             //possiamo passare un oggetto non const in quanto const nella funzione dice che non lo modificherà ma non impone nessuna restrizione
    clear( event_ptr );

  }

  mean_masse_invarianti = sum_masse_invarianti / numero_eventi_accettati;
  rms_partial = (sqr_sum_masse_invarianti / numero_eventi_accettati) - (mean_masse_invarianti*mean_masse_invarianti);

  if( rms_partial > 0 ) {
    rms_masse_invarianti = sqrt( rms_partial );
  }
  else{
    rms_masse_invarianti = 0;  
  }

  cout << "Mean: " << mean_masse_invarianti << endl;
  cout << "RMS:  " << rms_masse_invarianti << endl;

  return 0;

}
