//#include "ActiveObserver.h"
#include "Dispatcher.h"
#include <iostream>

//costruttore
//il "this" è riferito alla classe ActiveObserver (o alle derivate)
template <class T> ActiveObserver<T>::ActiveObserver() {
  Dispatcher<T>::subscribe( this );
}

//distruttore
template <class T> ActiveObserver<T>::~ActiveObserver() {
  Dispatcher<T>::unsubscribe( this );
}

