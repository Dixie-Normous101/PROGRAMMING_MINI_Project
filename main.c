#include <stdio.h>
#include "controls.h"

/* flush rest of line after scanf */
static void flush_line(void)
{
    int ch;
    do { ch = getchar(); } while (ch != '\n' && ch != EOF);
}



int main (void)
{
    double values_network[15][15];
    int index = 0;
    double voltage_running = 0.0;

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

            start_program_sub_menu(&voltage_running, values_network, &index);

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

