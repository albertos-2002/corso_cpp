//#include "LazyObserver.h"
#include "Dispatcher.h"

#include <iostream>

//costruttore
//il "this" è riferito alla classe ActiveObserver (o alle derivate)
template <class T> LazyObserver<T>::LazyObserver() {
  Dispatcher<T>::subscribe( this );
}

//distruttore
template <class T> LazyObserver<T>::~LazyObserver() {
  Dispatcher<T>::unsubscribe( this );
}

template <class T> void LazyObserver<T>::lazyUpdate( const T& x ) {
  upToDate = false;
  updating = false;
  last = &x;
  return;
}

template <class T> void LazyObserver<T>::check() {
  if ( updating ) {
    std::cout << "warning, recursive call" << std::endl;
    return;
  }
  
  updating = true;
  if ( !upToDate ) update( *last );
  upToDate = true;
  updating = false;
  return;
}

