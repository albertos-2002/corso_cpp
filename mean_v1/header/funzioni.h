#include <fstream>
using namespace std;

bool add( const Event& evento, const float& massMin, const float& massMax, double& sum_masse_invarianti, double& sqr_sum_masse_invarianti );
void clear( Event* ptrdel );
void dump( const Event& eventr_dump );
double energia( const float& momento_x, const float& momento_y, const float& momento_z, const double& massa_invariante );
double massa_invariante( double& momento_x, double& momento_y, double& momento_z, double& energia );
double mass( const Event& evento );
Event* read(ifstream& file_reading);
