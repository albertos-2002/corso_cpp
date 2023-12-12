#include "class_event.h"
#include <fstream>
using namespace std;

void dump( const Event& event_dump );
double mass( const Event& evento_m );
Event* read(ifstream& file_reading);
