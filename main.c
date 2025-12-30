#include <stdio.h>
#include "menu.h"

#define MAX_ROWS 10    // definition for the size of the matrix
#define MAX_COLUMNS 10 // definition for the size of the matrix

int main(void)
{

    double matrix[MAX_ROWS][MAX_COLUMNS];
    int rows = 0;
    int columns = 0;
    int has_circuit = 0;

    /* !ONLY FOR CLEANING THE MATRIX! */
    int rws, cols;
    for (rws = 0; rws < MAX_ROWS; rws++)
    {
        for (cols = 0; cols < MAX_COLUMNS; cols++)
        {
            matrix[rws][cols] = 0.0;
        }
    }
    /* !ONLY FOR CLEANING THE MATRIX! */

    int running = 1;
    int choice = 0;

    while (running)
    {
        print_menu();
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) // successfull scanf = 1, otherwise abort
        {
            printf("Invalid input. Exiting.\n");
            return 1;
        }

        switch (choice)
        {
        case 1:

            printf("Enter the number of rows (1..10): \n");
            scanf("%d", &rows);
            if (rows >= 1 && rows <= MAX_ROWS)
            {
                printf("Enter the number of columns (1..10): \n");
                scanf("%d", &columns);
                if (columns >= 1 && columns <= MAX_COLUMNS)
                {
                    has_circuit = 1;
                }
                else
                {
                    printf("Value is not in range. \n");
                    break;
                }
            }
            else
            {
                printf("Value is not in range. \n");
                break;
            }

            if (has_circuit == 1)
            {
                printf("Size of matrix you entered: [%d][%d] \n", rows, columns);
            }

            break;

        case 2:
            printf("Option 2 selected.\n");
            break;

        case 3:
            printf("Option 3 selected.\n");
            break;

        case 4:
            printf("Option 4 selected.\n");
            break;

        case 5:
            printf("Option 5 selected.\n");
            break;

        case 6:
            printf("Quitting...\n");
            running = 0;
            break;

        default:
            printf("Please choose a number from 1 to 6.\n");
            break;
        }

        printf("\n");
    }

    return 0;
}
