#include <iostream>
#include <fstream>

struct Particle {

   int electric_field; // stessa dimensione della versione 1
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
   Particle** ptr_partstruct; //incomplete type declaration

};

//------------------------------------------------------------------------------

Event* read(std::ifstream& file_reading) {

   Event* eventptr_read = new Event;                                            //alloco la memoria per un evento e la assegno ad un untatore (devo accedere con ->)

   if ( !file_reading.eof() ) {

      file_reading >> eventptr_read -> event_id;
      file_reading >> eventptr_read -> impact_x;
      file_reading >> eventptr_read -> impact_y;
      file_reading >> eventptr_read -> impact_z;
      file_reading >> eventptr_read -> number_particles;

      eventptr_read -> ptr_partstruct = new Particle*[eventptr_read -> number_particles];

      for (int i=0; i<eventptr_read -> number_particles; ++i) {

          eventptr_read -> ptr_partstruct[i] = new Particle;                    //allocazione della memoria

          file_reading >> eventptr_read -> ptr_partstruct[i] -> electric_field;  //scrivo dentro la particole con "doppio accesso"
          file_reading >> eventptr_read -> ptr_partstruct[i] -> momentum_x;
          file_reading >> eventptr_read -> ptr_partstruct[i] -> momentum_y;
          file_reading >> eventptr_read -> ptr_partstruct[i] -> momentum_z;

      }

   }

   else return nullptr;

   return eventptr_read;

}

void dump( const Event& eventr_dump ) {

   std::cout << eventr_dump.event_id << std::endl;
   std::cout << eventr_dump.impact_x << " " << eventr_dump.impact_y << " " << eventr_dump.impact_z << std::endl;
   std::cout << eventr_dump.number_particles << std::endl;

   for( int i=0; i<eventr_dump.number_particles; ++i ) {

     std::cout << eventr_dump.ptr_partstruct[i] -> electric_field << " " ;
     std::cout << eventr_dump.ptr_partstruct[i] -> momentum_x << " " << eventr_dump.ptr_partstruct[i] -> momentum_y << " " <<  eventr_dump.ptr_partstruct[i] -> momentum_z << std::endl;

   }

}

void clear( Event* ptrdel ) {

   for(int i=0; i < ptrdel -> number_particles; ++i) {

     delete ptrdel -> ptr_partstruct[i];

   }

   delete ptrdel -> ptr_partstruct;
   delete ptrdel;

}

//------------------------------------------------------------------------------

int main( int terminal_index, char* terminal_string[] ) {

   std::ifstream reading_file(terminal_string[1]);

   if( !reading_file.is_open() ) return 1;                                        // controllo apertura file

   while( !reading_file.eof() ){

     Event* event_ptr = read( reading_file );
     dump( *event_ptr );                                                          //possiamo passare un oggetto non const in quanto const nella funzione dice che non lo modificherà ma non impone nessuna restrizione
     clear( event_ptr );

   }

  return 0;

}
