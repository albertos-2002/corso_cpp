#include <iostream>
#include <fstream>
#include <cmath>
#include "header/struct.h"
#include "header/funzioni.h"
using namespace std;

int main( int terminal_index, char* terminal_string[] ) {

  ifstream reading_file(terminal_string[1]);
  if( !reading_file.is_open() ) return 1;

  int numero_eventi_accettati = 0;
  double sum_masse_invarianti = 0;
  double sqr_sum_masse_invarianti = 0;
  double mean_masse_invarianti = 0;
  double rms_masse_invarianti = 0;
  double rms_partial = 0;

//---------------------------------------------------------------------------------------
  
  while( !reading_file.eof() ){

      Event* event_ptr = read( reading_file );

      if ( add( *event_ptr, massMin, massMax, sum_masse_invarianti, sqr_sum_masse_invarianti ) ){
          numero_eventi_accettati += 1;
      }

//    dump( *event_ptr );         
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
