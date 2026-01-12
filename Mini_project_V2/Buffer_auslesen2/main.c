#include <stdio.h>

#include "buffer.h"


//Total resistance
//Total Current funktion erhält Spannungswert als argument und adresse zum Struct mir r_ges_sum rtörn I = ...
//Praser Function für Spannung
// 

void main(){

 double network_values[15][15];
 int index_row = 0; //row 
 int index_column = 0; //col

 network_values_calculated user_network; // enthält Werte des Netzwerks 
 int control = 0;
 r_value_user value_r_display; // beinhaltet info zu eingebenem Wert
 storage_voltage_imput voltage; 
 
 for(int v = 0; v < 1; v++)
 {
    control = user_input(&value_r_display); // return Wert ist die Breite der Zahl 
    for(int h = 0; h < 15 ; h++){
      network_values[v][h] = value_r_display.r_value;
    }
 }  

 calc_R_ges(network_values,&user_network);
 printf("fertig\n");

 user_input_voltage(&voltage);

 // struct_to_value(&value_r_display);
}