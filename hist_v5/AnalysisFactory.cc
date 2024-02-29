#include "header/AnalysisFactory.h"
#include "header/AnalysisInfo.h"

#include <iostream>
#include <map>

using namespace std;

AnalysisFactory::AnalysisFactory() {
}


AnalysisFactory::~AnalysisFactory() {
}


// create all requested analysis objects
vector<AnalysisSteering*> AnalysisFactory::create( const AnalysisInfo* info ) {
  //creazione di un vettore di oggetti puntatore ad analysissteering
  vector<AnalysisSteering*> aList;
  // loop over analysis object factories
  static map<string,AbsFactory*>* fm = factoryMap();
  for ( const auto& element: *fm ) {
    // create analysis object if its name is listed in the command line
    if ( info->contains( element.first ) )
        aList.push_back( element.second->create( info ) );
  }
  return aList;
}


// function to add analyzer concrete factories
void AnalysisFactory::registerFactory( const string& name, AbsFactory* b ) {
  static map<string,AbsFactory*>& fm = *factoryMap();
  fm[name] = b;
  return;
}


// map to associate analyzer names with corresponding factories
map<string,AnalysisFactory::AbsFactory*>*
           AnalysisFactory::factoryMap() {
  static map<string,AbsFactory*>* fm = new map<string,AbsFactory*>;
  return fm;
}

