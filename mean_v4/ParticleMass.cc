#include <vector>
#include <iostream>
#include "header/class_massmean.h"
#include "header/AnalysisSteering.h"
#include "header/ParticleMass.h"
using namespace std;

class ParticleMass;

//costruttore
ParticleMass::ParticleMass(){
}

//distruttore
ParticleMass::~ParticleMass(){
}
  

void ParticleMass::beginJob(){

  ptr_massmean.reserve(2);
  //ipotesi lambda
  ptr_massmean.push_back( new MassMean( 1.115 , 1.116 ) );
  //ipotesi k
  ptr_massmean.push_back( new MassMean( 0.495 , 0.500 ) );

  return;
}

void ParticleMass::endJob(){

  for (int i=0; i<2; ++i){
  
  ptr_massmean.at(i) -> compute();
  
    if(i==0){
    
      cout << "Ipotesi L0" << endl;
      cout << "Numero eventi:  " << ptr_massmean.at(i) -> nEvents() << endl;
      cout << "Media        :  " << ptr_massmean.at(i) -> mMean() << endl;
      cout << "RMS          :  " << ptr_massmean.at(i) -> mRMS() << endl;
    
    }
    else{
  
      cout << "Ipotesi K0" << endl;
      cout << "Numero eventi:  " << ptr_massmean.at(i) -> nEvents() << endl;
      cout << "Media        :  " << ptr_massmean.at(i) -> mMean() << endl;
      cout << "RMS          :  " << ptr_massmean.at(i) -> mRMS() << endl;
  
    }
  
  }

  return;
}

void ParticleMass::process( const Event& classe_evento ){

  for (MassMean* c : ptr_massmean){
  
    c -> add( classe_evento );  //accessi di tipo puntatore
  
  }

  return;
}
