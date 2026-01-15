#include <stdio.h>
#include "buffer.h"
#include <math.h>
/*
ungültige Darstellungen:

5g8j9d
k,75
7,k5

Wenn Komma enthalten dann muss Prefix ganz am ende stehen
Darstellungen:
7
7,0
7.0
7k
7k0
7,0k
7.0k
k7 
r7
7r

7 -> 7  direkt Wert

7,0 7.0 7k0 k7 r7

Information in struct

Breite der Zahl
Position von präfix
position von . oder ,

 typedef struct
   {
      char number[15];
      char prefix;
      int point_index; // index an welcher stelle komma stehen muss
      int prefix_index;
      int with;
      double r_value; // Wert als Zahl
      char komma;
   } r_value_user;
*/
// {'n' , 'u' , 'm' , 'k' , 'M', 'G' , 'R' , 'r'},
//double prefix_Number[] = {1e-9, 1e-6, 1e-3, 1e3, 1e6, 1e9, 1, 1}; // kann entsprechend aus dem Wert i_2_2 encodet werden


double struct_to_value(r_value_user * str_p){

    //string bzw char array zu float

    double r_value_lf = 0;
    int i = str_p ->with;
    double prefix_Number[] = {1e-9, 1e-6, 1e-3, 1e3, 1e6, 1e9, 1, 1};

    if((str_p -> komma == ',' || str_p -> komma == '.') && str_p -> prefix_index == 0) i -= 2; // wieso mal +1 und -1 keine Ahnung war geraten
    if(str_p -> point_index && str_p -> prefix_index) i -= 3;
    if(str_p->prefix_index && !(str_p->point_index)) i -= 2;
    if(!(str_p->prefix_index) && !(str_p->point_index)) i -= 1;
    //else i = str_p -> with ;

    for(; i>= 0 ; i--)
    {
       r_value_lf = r_value_lf * 10 + (str_p -> number[i] - '0'); // char Zahl - '0' ergibt Zahl
    }

    //printf("%lf\n", r_value_lf);
    //printf("%i\n", str_p -> with);


   // r_value_lf ist jetzt ein flaot Wert.
   //Falls Komma vorhanden Komma setzen
   int power = 0;

   if(str_p->point_index)
   {
      power = str_p->with - str_p->point_index;
      if(str_p->prefix_index) power--; // wenn prefix vorhanden dann muss das bei power beachtet werden 
   }
   

   //Prefix als Komma verwendet

   if(!(str_p->point_index) && (str_p->prefix_index))
    {
       power = str_p->with - str_p->prefix_index;;
    }

    r_value_lf = r_value_lf / pow(10,power);

    //prefix aufmultiplizieren

    if(str_p->prefix_index) r_value_lf = r_value_lf * prefix_Number[str_p->index_for_prefix_number];

    printf("%lf\n",r_value_lf);

    str_p->r_value = r_value_lf;


}

