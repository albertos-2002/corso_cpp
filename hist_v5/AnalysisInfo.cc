#include "header/AnalysisInfo.h"
#include <string>

using namespace std;

// value to return for keys not found
string AnalysisInfo::defaultString = "";


AnalysisInfo::AnalysisInfo( int argc, char* argv[] ) {
  args.resize( argc );
  int iarg;
  for ( iarg = 1; iarg < argc; ++iarg ) args[iarg] = argv[iarg];
}


AnalysisInfo::~AnalysisInfo() {
}


// get the list of all words
const vector<string>& AnalysisInfo::argList() const {
  return args;
}


// get the word coming after the word 'key'
const string& AnalysisInfo::value( const string& key ) const {
  // loop over words
  int i = 0;
  int n = args.size() - 1;
  while ( i < n ) {
    // if word is equal to key, return next word
    if ( args[i++] == key ) return args[i];
	/*
	si nota che all'interno del ciclo if viene utilizzato un
	post-incremento, questo significa che prima viene ritornato il
	contenuto di args alla posizione i (che viene confrontato con
	il valore della key desiderata), successivamente i viene
	incrementata di una unità e quindi si passa alla prossima istruzione,
	dato che l'incremento è avvenuto nel controllo, l'istruzione successiva
	ritorna un valore che si trova alla posizione successiva rispetto al controllo
	*/
  }
  // if key not found, return a default string
  return defaultString;
}


// check if the word 'key' is present
bool AnalysisInfo::contains( const string& key ) const {
  // loop over words
  for ( const string& s: args ) {
    // if word is equal to key, return true
    if ( s == key ) return true;
  }
  // if key not found, return false
  return false;
}

