#include <stdio.h>
#include "controls.h"
#include "buffer.h"

/* flush rest of line after scanf */
static void flush_line(void)
{
    int ch;
    do { ch = getchar(); } while (ch != '\n' && ch != EOF);
}



int main (void)
{
    //enthält das Netzwerk 15 auf 15
    double values_network[15][15];
    for (int net_row = 0; net_row < 15; net_row++){
        for(int net_column = 0; net_column < 14; net_column++ ){
            values_network[net_row][net_column] = 0;
        }
    } // die kacke war nicht null

    int index = 0; // Speicherindex für die netzwerkmatrix
    double voltage_running = 0.0;// Benutzerspannung
    network_values_calculated user_network; //gesamter widerstand und Reihenwiderstände
    r_value_user User_values_r; // enthält alle info zu eingegenen Widerstand des users
    storage_voltage_imput voltage; //enthält eingegebener Spannungswert

    
    int running = 1;
    

    while (running)
    {
        int choice = 0; // switch case use for the menus

        print_main_menu();
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Exiting & stopping.");
            flush_line();
            continue;
        }

        flush_line();

        switch (choice)
        {
        case 1:
            // das hier ruft die Funktionen auf für Eingabe
            start_program_sub_menu(&voltage_running, values_network, &index, &user_network, &User_values_r, &voltage);

            break;
        
        case 2:

            print_help_screen();
            wait_for_enter();
        
            break;


            
        case 3:

            printf("Quitting....");
            running = 0;
            break;

        default:    

            printf("Please choose 1,2 or 3.");
            wait_for_enter();
            break;
        }
        
        printf("\n");

    }
    
    return 0;

}

