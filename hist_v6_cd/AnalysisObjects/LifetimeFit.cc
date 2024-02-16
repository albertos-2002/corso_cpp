#include "header/LifetimeFit.h"
#include "../AnalysisFramework/header/class_event.h"
#include "header/ParticleReco.h"
#include "header/ProperTime.h"
#include <cmath>
#include <TGraph.h>
#include <TFile.h>
#include "../AnalysisUtilities/header/QuadraticFitter.h"
#include "../util/include/TFileProxy.h"
using namespace std;

  LifetimeFit::LifetimeFit( double min_mass, double max_mass, double max_time, double min_time, double max_scan, double min_scan, double step_scan):    

  min_invariant_mass(min_mass),
  max_invariant_mass(max_mass),
  min_time_range(min_time),
  max_time_range(max_time),
  min_scan_range(min_scan),
  max_scan_range(max_scan),
  scan_step(step_scan)
  {
  }
  
  LifetimeFit::~LifetimeFit(){  }                  

  bool LifetimeFit::add( const Event& evento_a ){  

   //creazione istanza a particle reco, svolgimento della ex funzione mass e estrazione della massa invariante
   static ParticleReco* ptr_particlereco = ParticleReco::instance();
   ptr_particlereco -> update( evento_a );
   
   //estrazione tempo proprio
   static ProperTime* ptr_propertime = ProperTime::instance(); 
   ptr_propertime -> update( evento_a );
    
   double massa_tmp;
   massa_tmp = ptr_particlereco -> get_invariantmass();
   
   double tempo_tmp;
   tempo_tmp = ptr_propertime->decayTime();
    
   if ( massa_tmp <= max_invariant_mass && massa_tmp >= min_invariant_mass ) {
    
     if ( tempo_tmp <= max_time_range && tempo_tmp >= min_time_range  ){
     decay_time_value.push_back( tempo_tmp );
     return true;
     }
     
     return false;
   }
   else{
     return false;
   }
   
  }
  
  void LifetimeFit::compute( string nome_grafico_parabola ) { 
    
    //calcolo della verosimiglianza -----------------------------------------
    double likelihood_part1 = 0; 
    double likelihood_part2 = 0; 
    double likelihood_part3 = 0; 
    double likelihood_part4 = 0; 
    double likelihood_part5 = 0;
    vector<double> likelihood_holder;
    vector<double> time_holder;
    double ts = min_scan_range;
    double likelihood_result = 0;
    double likelihood_sum = 0;
    
    while ( ts <= max_scan_range ){
    
      likelihood_sum = 0;
      time_holder.push_back(ts);
    
      for (auto k : decay_time_value){
      
        likelihood_part1 = k / ts ;
        likelihood_part2 = log(ts);
        likelihood_part3 = exp(-min_time_range/ts);
        likelihood_part4 = exp(-max_time_range/ts); 
        likelihood_part5 = log(likelihood_part3 - likelihood_part4);
      
        likelihood_result = likelihood_part1 + likelihood_part2 + likelihood_part5;
        likelihood_sum += likelihood_result;
      }
    
      likelihood_holder.push_back( likelihood_sum );
      ts += scan_step;
    }
    
    //-----------------------------------------------------------------------
    
    //controllo dimensione vettori
    if ( time_holder.size() != likelihood_holder.size() ){
    cout << "LifetimeFit.cc(89): Vettori dati dimensione diversa" << endl;
    return;
    }
    
    QuadraticFitter* ptr_quadraticfitter = new QuadraticFitter();
    
    for ( unsigned int i = 0; i<time_holder.size(); ++i){
      ptr_quadraticfitter -> add(time_holder.at(i), likelihood_holder.at(i));
    }
    
    //-----------------------------------------------------------------------
    
    mean_time = -( ptr_quadraticfitter->b() )/(2* (ptr_quadraticfitter->c()) );
    error_time = 1/sqrt(2* (ptr_quadraticfitter->c()) );    
    
    //grafico della parabola ------------------------------------------------  
      TDirectory* currentDir = gDirectory;
      string nome_grafico = nome_grafico_parabola+"Parabola"+".root";
      TFile* ptr_tfile = new TFile( nome_grafico.c_str() , "RECREATE");
      int dimensione = time_holder.size();
      TGraph *grp = new TGraph (dimensione, time_holder.data(), likelihood_holder.data());
      grp -> Write( nome_grafico_parabola.c_str() );
      ptr_tfile -> Close();
      currentDir -> cd();
      delete ptr_tfile;    
    //-----------------------------------------------------------------------
    
    delete ptr_quadraticfitter;
    return;
  }
  
//funzioni per il return dei dati -------------------------------

  int LifetimeFit::nEvents(){
    return decay_time_value.size();
  }

  double LifetimeFit::get_lifeTime(){
    return mean_time;
  }

  double LifetimeFit::get_lifeTimeError(){
    return error_time;
  }  
