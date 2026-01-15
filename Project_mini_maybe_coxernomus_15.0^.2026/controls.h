#ifndef CONTROLS_H
#define CONTROLS_H

#define MENU_WIDTH 50
#define MAX 15

 typedef struct   network_values_calculated network_values_calculated; //gesamter widerstand und Reihenwiderstände
 typedef struct   r_value_user r_value_user ; // enthält alle info zu eingegenen Widerstand des users
 typedef struct   storage_voltage_imput storage_voltage_imput; //enthält eingegebener Spannungswert
/* Vorward deklaration 
man kann unbegrenzt oft eine variable genau gleich deklarieren da dies nur aussagt, dass es eine Variable mit diesem Name geben wird
also hier dann in die Funktion als Argument struct... sagt es wird ein struct geben das so heißt wird
aber erst in der buffer.h initialisiert also die Variablen angelegt.
in der Funktion muss dann klar sein das die Funktion struct adressen erhält als argument */


void print_main_menu();             // Prototype for printing main (start) menu.

void print_help_screen();           // Prototype for printing a help screen.
/*
    network_values_calculated user_network; //gesamter widerstand und Reihenwiderstände
    r_value_user User_values_r; // enthält alle info zu eingegenen Widerstand des users
    storage_voltage_imput voltage; //enthält eingegebener Spannungswert
*/
// Betriebsspannung --> netzwerkmatrix ---> netzwerk werte struct --> struct für r Eingabe ds useres ---> struct für v eingabe des users
void start_program_sub_menu(double *voltage_running, 
                            double values_network[MAX][MAX], 
                            int * index, 
                            network_values_calculated * p_user_network, 
                            r_value_user * p_User_values_r, 
                            storage_voltage_imput * p_voltage);   

void print_resistor_graphic(double voltage_running, double values_network[MAX][MAX]); // print the resistor graphic (very simplified)

void wait_for_enter();              // Prototype: waiting for user to do something.

void read_supply_voltage(double * voltage_running, storage_voltage_imput * p_voltage_1 );


#endif
