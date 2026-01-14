#include <stdio.h>
#include <string.h>
#include "controls.h"
#include "buffer.h"
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


/******************************************************************************************** */
// Funktion aus buffer.h
/******************************************************************************************** */

void read_supply_voltage(double * voltage_running, storage_voltage_imput * p_voltage_1 )
{
    printf("Supply voltage (0 if none): ");

    user_input_voltage(p_voltage_1); // jetzt ist im struct voltage der eingebene Wert als lf gespeichert
    *voltage_running = p_voltage_1 ->voltage_value; // speichert lf wert aus struct ind voltage_running
/*
    if (scanf("%lf", voltage_running) != 1)
    {
        printf("Invalid input. Using 0 as value.\n");
        *voltage_running = 0.0;
    } 
    flush_line();
*/
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

/************************************************************************************* */
// funktion aus buffer.h einbinden
/************************************************************************************* */
static void read_resistor_value(double *value, int res_id, r_value_user * p_User_values_r_1  )
{
    printf("Enter resistor value R%d (ohm): ", res_id);
    
    user_input(p_User_values_r_1 ); //Speichert im struct voltage den lf wert 

    *value = p_User_values_r_1->r_value;

    /*
    if (scanf("%lf", value) != 1)
    {
        printf("Invalid input. Using 0.");
        * value = 0.0;

    }
    
    flush_line();
*/

}

/* build function for creating the graphics */

static int count_row_matrix(double values_network[MAX][MAX], int row) // count how many resistors in one row
{
    int count, n = 0;
    for (count = 0; count < MAX; count++) // goes from. 0 --> max
    {
        if (values_network[row][count] != 0.0) // is there a resistor ?
        {
            n++; // increment n
        }
        
    }
    return n; // value for resistors in this row
}

static void print_rail_graphic(int n)
{
    int i, j;
    putchar('+');
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < 7; j++) 
        {
            putchar('-');  
        }
        putchar('+');
    }
    putchar('\n');
}


void print_resistor_graphic(double voltage_running, double values_network[MAX][MAX]) // main function to print graphic
{
    int row, col;
    int last_row = -1; // for right indexing
    int resistor_id = 1;
    int i;

    for (row = 0; row < MAX; row++) // last row used ?
    {
        for (col = 0; col < MAX; col++)
        {
            if (values_network[row][col] != 0.0)
            {
                last_row = row;
            }
            
        }
        
    }

    printf("\n"); 
    
    if (voltage_running != 0.0) // print voltage
    {
        printf("U = %.2f V\n", voltage_running);
    }
    printf("\n");
    printf("V_in\n");

    if (last_row < 0) // what happens for no entered resistors ?
    {
        printf("No entered resistors. \n");
        printf("GROUND");
    }

    for (row = 0; row <= last_row; row++) // print actual scheme
    {
        int n = count_row_matrix(values_network, row);

        if (n == 0) // no values entered in this row
        {
            continue;
        }
        
        printf("| \n");
        printf("| \n");
        if (n == 1)
        {
            printf("[R%d]\n", resistor_id);
            resistor_id++;
        }
        else if (n <= 4) // we print pretty for max 4 resistors
        {
            print_rail_graphic(n); // connection for parallel
            for (i = 0; i < n; i++) 
            {
                printf("[R%d]    ", resistor_id);
                resistor_id++;
            }
            putchar('\n');

            print_rail_graphic(n);
        }
        else
        {
            printf("PARALLEL RESISTORS: ");
            for (i = 0; i < n; i++)
            {
                printf("[R%d]", resistor_id);
                resistor_id++;
            }
            printf("\n");
        }
        
    }
    printf("|\n");
    printf("GND\n\n");
}


void start_program_sub_menu(double * voltage_running, double values_network[MAX][MAX], int * index, network_values_calculated * p_user_network, r_value_user * p_User_values_r, storage_voltage_imput * p_voltage )
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
    // Dann wäre die erste zeile aber immer ungenutzt also nur 14x15 Widerstände möglich 
    //benötigt struct welche user input zu voltage enthält 
    read_supply_voltage(voltage_running, p_voltage); // read voltage from user and increment index, for the first resistor
    * index = * index + 1; // erste linie nur für spannung nicht für widerstand ?

    read_resistor_value(&resistor_value, *index, p_User_values_r); // read the 1st resistor value
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
        read_resistor_value(&resistor_value, *index, p_User_values_r);
        values_network[row][col] = resistor_value;
    }    

    /* finished the input*/

    //calculate komplette Widerstand ***********************************************************************************************
    calc_R_ges(values_network, p_user_network); // gleich wie &networkvalue[0] Hier noch feheler

    printf("\n Network input finished.");
    printf("\n");
    printf("\n");

    // Ausgabe graphics

    print_resistor_graphic(*voltage_running, values_network);

    wait_for_enter();

    /* results */

    horizontal_line();
    centered_line("RESULT MENU");
    horizontal_line();
    left_line(" [1] Total resistance (not implemented)");
    left_line(" [2] Total current (not implemented)");
    left_line(" [3] Back");
    horizontal_line();

    int control = 0;
    int choicexyz = 0;

    do{
        control = scanf("%i", &choicexyz);
        if(control != 1){
            printf("falsche Eingabe\n");
        }
        flush_line();
    }while(control != 1);

    if(choicexyz == 1){
        printf("%lf Ohm\n",p_user_network->sum_r_network);
    }

    if(choicexyz == 2){
        double ausgabe = 0;
        ausgabe = *voltage_running / (p_user_network->sum_r_network);
        printf("%lf A\n",ausgabe);
    }


    wait_for_enter();
    
}


