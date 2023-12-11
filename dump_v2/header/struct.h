struct Particle {

   int electric_field;
   float momentum_x;
   float momentum_y;
   float momentum_z;
};

struct Event {

   int event_id;
   float impact_x;
   float impact_y;
   float impact_z;
   int number_particles;
   Particle** ptr_partstruct; 
};
