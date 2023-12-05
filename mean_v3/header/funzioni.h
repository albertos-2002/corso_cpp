#include <iostream>
using namespace std;
#include "class_event.h"

//funzione read ------------------------------------------------------------------------------------------------

Event* read(ifstream& file_reading);

//funzione dump ------------------------------------------------------------------------------------------------

void dump( const Event& event_dump );

//funzione mass ------------------------------------------------------------------------------------------------

double mass( const Event& evento_m );
