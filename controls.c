#include <stdio.h>
#include <string.h>
#include "controls.h"

/* 

functions for the main menu or for helping in the menu

*/

static void horizontal_line(void)
{
    int i;
    putchar('+');
    for (i = 0; i < MENU_WIDTH; i++)
        putchar('-');
    putchar('+');
    putchar('\n');
}


static void empty_line(void)
{
    int i;
    putchar('|');
    for (i = 0; i < MENU_WIDTH; i++)
        putchar(' ');
    putchar('|');
    putchar('\n');
}

static void left_line(const char * text)
{
    int len;
    len = (int)strlen(text);
    int i;

    if (len > MENU_WIDTH)                   // safety for the menu: if len > menu width, menu looks not good.
    {
        len = MENU_WIDTH;
    }

    putchar('|');
    printf("%.*s", len, text);              // printf with dynamic width, keep menu looking clean

    for (i = len; i < MENU_WIDTH; i++)      // rest filled with blanks
    {
        putchar(' ');
        
    }  
    putchar('|');
    putchar('\n');  
    
}

static void centered_line(const char * text)
{
    int len;
    len = (int)strlen(text);
    int i;

    if (len > MENU_WIDTH)                   // safety for the menu: if len > menu width, menu looks not good, copied from above (left_line)
    {
        len = MENU_WIDTH;
    }

    putchar('|');

    int space, space_left, space_right;
    space = MENU_WIDTH - len; // how much space is there?
    space_left = space / 2; // left space is space / 2
    space_right = space - space_left;  

    for (i = 0; i < space_left; i++)
        putchar(' ');

    printf("%.*s", len, text);  

    for (i = 0; i < space_right; i++)
    putchar(' ');

    putchar('|');
    putchar('\n');
}

void print_main_menu(void)
{
    horizontal_line();
    centered_line("RESISTOR NETWORK TOOL");
    centered_line("MAIN MENU");
    horizontal_line();

    left_line(" [1] Start Program");
    left_line(" [2] Help");
    left_line(" [3] Quit");

    horizontal_line();

}

void print_help_screen(void)
{
    horizontal_line();
    centered_line("HELP");
    horizontal_line();

    left_line(" This tool lets you enter a resistor network");
    left_line(" step by step and prints a (limited) ");
    left_line(" graphical view.");
    empty_line();

    left_line("HOW TO USE:");
    left_line(" - Enter supply voltage (0 if not wanted).");
    left_line(" - Enter resistor value(s) ");
    left_line(" - Choose (p) parallel, (r) series for next.");
    left_line(" - Enter (x) for finishing + print of schematic.");
    empty_line();

    left_line("Notes: ");
    left_line(" - ASCII only (stable on MAC/WINDOWS).");
    left_line(" - Printed schematic is clean up to");
    left_line(" 4 parallel resistors.");
    horizontal_line();

}

void wait_for_enter(void)
{
    printf("\nPress Enter to continue...");
    getchar();                                  

}

/*

functions for reading the voltage

*/

static void flush_line(void)
{
    int ch;
    do
    {    
        ch = getchar(); 
    } while (ch != '\n' && ch != EOF);
}

void read_supply_voltage(double * voltage_running)
{
    printf("Supply voltage (0 if none): ");

    if (scanf("%lf", voltage_running) != 1)
    {
        printf("Invalid input. Using 0 as value.\n");
        *voltage_running = 0.0;
    } 
    flush_line();

}

/*

functions for the sub menu

*/

static void clear_network(double values_network[MAX][MAX]) // clear matrix
{
    int r, c; //rows + columns
    for (r = 0; r < MAX; r++) // we defined MAX = 15, puts 0.0 in all spaces.
        for (c = 0; c < MAX; c++)
            values_network[r][c] = 0.0;
}

static void read_resistor_value(double *value, int res_id)
{
    printf("Enter resistor value R%d (ohm): ", res_id);

    if (scanf("%lf", value) != 1)
    {
        printf("Invalid input. Using 0.");
        * value = 0.0;

    }
    
    flush_line();

}


void start_program_sub_menu(double * voltage_running, double values_network[MAX][MAX], int * index)
{
    int row = 0;
    int col = 0;
    int rows_used = 0;
    int cols_used = 0;

    char choice = 'X';
    double resistor_value;

    /* new input*/
    clear_network(values_network); // clear matrix and set index = 0
    *index = 0;

    horizontal_line();
    centered_line("START PROGRAM");
    horizontal_line();
    
    read_supply_voltage(voltage_running); // read voltage from user and increment index, for the first resistor
    * index = * index + 1;

    read_resistor_value(&resistor_value, *index); // read the 1st resistor value
    values_network[row][col] = resistor_value; // safe resistor value in the network

    while (1) //we need to ask for more resistors or abort
    {
        printf("Parallel (p), series (r), finish (x)?");
        if (scanf(" %c", &choice) != 1)
        {
            printf("Invalid input.\n");
            flush_line();
            continue;
        }
        flush_line();

        if (choice == 'X' || choice == 'x')
        {
            break;
        }
        
        else if (choice == 'P' || choice == 'p')
        {
            col = col + 1; // one col right, we use it for graphics
            if (col > cols_used)
            {
                cols_used = col;
            }
        }
            
        
        else if (choice == 'r' || choice == 'R')
        {
            row = row + 1; // one row down
            col = 0; // saftey because you could've entered before so its not 0

            if (row > rows_used)
            {
                rows_used = row;
            }
    
        }
       
         else 
        {
            printf("Please enter P/R/X. \n");
            continue;
        }

        * index = * index + 1;
        read_resistor_value(&resistor_value, *index);
        values_network[row][col] = resistor_value;
    }    

    /* finished the input*/

    printf("\n Network input finished.");

    // Ausgabe graphics

    wait_for_enter();

    /* results */

    horizontal_line();
    centered_line("RESULT MENU");
    horizontal_line();
    left_line(" [1] Total resistance (not implemented)");
    left_line(" [2] Total current (not implemented)");
    left_line(" [3] Back");
    horizontal_line();

     wait_for_enter();
    
}


