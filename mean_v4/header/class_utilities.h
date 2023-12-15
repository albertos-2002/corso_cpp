#ifndef class_utilities
#define class_utilities

class Utilities{

public:

  static double energia( const float& momento_x, const float& momento_y, const float& momento_z, const double& massa_invariante );  

  static double massa_invariante( double& momento_x, double& momento_y, double& momento_z, double& energia ); 

};

#endif
