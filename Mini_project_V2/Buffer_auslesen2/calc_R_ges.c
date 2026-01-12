#include "buffer.h"

/*
Eigenschaften array Pointer 



Array enthält entsprechend dem Netzwerk Widerstandswerte

Dieses Array erhalten und Zweites array mit Ersatzwiderständen für jeweils alle Parallelwiderständen bilden
*/




double calc_R_ges(const double (*array)[15], network_values_calculated * str_p){  // same as array[][] Adresse für erstes Element im Array wird übergeben 

    double r_ges = 0.0;


    // Gesamtwiderstand bilden der Parallelwiderstände
    for(int i = 0; i < 15; i++)
     {
       for(int z = 0; z < 15; z++)
         {
            if(array[i][z] > 0) r_ges += 1.0/((array[i][z])); // Aufaddieren der Leitwerte 
         }
      
       str_p->network_r_ges[i][0] = r_ges = 1 / r_ges; // Kehrwert bilden 
     }


 //Gesamtwiderstand des gesamten Netzwerks bilden 
  r_ges = 0;

  for(int i = 0; i < 15; i++)
  {
    r_ges += str_p->network_r_ges[i][0]; // an erster Stelle dieses array sind die Ersatzwidersstände aller Parallelwiderständen gepseichert. 
  }
    
  str_p->sum_r_network = r_ges;

}