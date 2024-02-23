#ifndef Singleton_H
#define Singleton_H

template <class T> class Singleton {

 public:

  // get the object instance
  static T* instance();  //"per definizione" la stessa istanza per tutto il programma
  static bool verbose;

 protected:

  // the object can be created only through a derived object
  // created in its turn by the "instance()" function
  
  //costruttore
  Singleton();
  //distruttore
  virtual ~Singleton();

};

#include "Singleton.hpp"

#endif

