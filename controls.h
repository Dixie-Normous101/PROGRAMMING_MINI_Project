#ifndef CONTROLS_H
#define CONTROLS_H

#define MENU_WIDTH 50
#define MAX 15


void print_main_menu();             // Prototype for printing main (start) menu.
void print_help_screen();           // Prototype for printing a help screen.
void start_program_sub_menu(double *voltage_running, double values_network[MAX][MAX], int * index);   

void wait_for_enter();              // Prototype: waiting for user to do something.

void read_supply_voltage(double * voltage_running);


#endif
