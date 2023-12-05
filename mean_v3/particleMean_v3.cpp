#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
#include "header/class_event.h"
#include "header/class_constants.h"
#include "header/class_utilities.h"
#include "header/class_massmean.h"
#include "header/funzioni.h"

int main( int terminal_index, char* terminal_string[] ){
  
  string nome_file = terminal_string[1];
  
  ifstream reading_file( nome_file );
  
  //dichiarazione del dump --------------------------------------------
      string dump_bool = terminal_string[2];
    if (dump_bool == "dump"){
    cout << "Dump attivato" << endl;    
    }
    
    else {
    cout << "Dump disattivato" << endl;
    }
  //-----------------------------------------------------------------  

  MassMean obj_K0( 0.495 , 0.500 );
  MassMean obj_L0( 1.115 , 1.116 );

  if( !reading_file.is_open() ) return 1;                       // controllo apertura file

  while( !reading_file.eof() ){  

    Event* eventclass_ptr = read( reading_file );               //questa istruzione dovrebbe creare tutte le memorie necessarie

    obj_K0.add( *eventclass_ptr );
    obj_L0.add( *eventclass_ptr );
    
    if (dump_bool == "dump"){
    dump( *eventclass_ptr );
    }

    delete eventclass_ptr;

  }

  obj_K0.compute();
  obj_L0.compute();

  cout << "Ipotesi K0" << endl;
  cout << "Numero eventi:  " << obj_K0.nEvents() << endl;
  cout << "Media        :  " << obj_K0.mMean() << endl;
  cout << "RMS          :  " << obj_K0.mRMS() << endl;

  cout << "Ipotesi L0" << endl;
  cout << "Numero eventi:  " << obj_L0.nEvents() << endl;
  cout << "Media        :  " << obj_L0.mMean() << endl;
  cout << "RMS          :  " << obj_L0.mRMS() << endl;

  return 0;

}
