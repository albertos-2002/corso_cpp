#include <iostream>
#include <fstream>
#include "header/struct.h"
using namespace std;

Event* read(std::ifstream& file_reading);
void dump( const Event& eventr_dump );
void clear( Event* ptrdel );

int main( int terminal_index, char* terminal_string[] ) {

  ifstream reading_file(terminal_string[1]);
  // controllo apertura file
  if( !reading_file.is_open() ) return 1;                                        

   while( !reading_file.eof() ){

     Event* event_ptr = read( reading_file );
     dump( *event_ptr );  
     clear( event_ptr );
   }

  return 0;
}
