#ifndef BUFFER_H
#define BUFFER_H

 /*
 Schreibweisen:
 1k2
 1.2k
 1,2k
 1200
 k2 = 200

 sinvolle Dezimalpräfixe:

 n , µ/u , m , k , M , G
 auch erlaubt r und R wegen:
 3r2 & 3R2 = 3,2


 buffer.c 
 auswertung des eingebenen:
 speichern von Zahlen entsprechend eingabe
 Vermerk von Punkt und Prefixposition 
 interpretation entsprechend
 7k7 k gleichzeitig , und dezimalpräfix
 also benötigt  auswertung position und info welches dezimalpräfix

 */
 extern char allowed_char[4][15]; // definition in buffer.c


 typedef struct
   {
      char number[15];
      char prefix;
      int point_index; // index an welcher stelle komma stehen muss
      int prefix_index;
      int with;
      double r_value; // Wert als Zahl
      char komma;
      int index_for_prefix_number;
   } r_value_user;


   //Values des eingegeben Netzwerks
 typedef struct
   {  
      double sum_r_network;
      double network_r_ges[15][15];
   }network_values_calculated;

   //struct welches Eingaewerte für Spannung enthält

 typedef struct 
   {
     char number_v[100];
     char prefix;
     char komma;
     double voltage_value;
   }storage_voltage_imput;
 
   //Praser für Eingabe der Spannug
   int user_input_voltage(storage_voltage_imput * str_p);


   int user_input(r_value_user * str_p);

 /*
 Im struct sind alle informationen zu Zahl gespeichert bzw zum Wert welcher eingegeben wurde
 Also kann aus struct Wert berechenet werden
 */
 double struct_to_value(r_value_user * str_p);


 //int store_r_value(); // in Struct der Main ist r_value abgelegt soll den Wert an richtige stelle im array speichern

 double calc_R_ges(const double (*array)[15], network_values_calculated * str_p); // Berechnet die Ersatzwiderstände


#endif