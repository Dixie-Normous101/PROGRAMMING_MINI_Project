#include <stdio.h>
#include <string.h>
#include "menu.h"

/* declare how big the menu will be (without any other signs) */

#define MENU_WIDTH 50

void line_horizontal(void)
{
    int i;
    putchar('+');
    for (i = 0; i < MENU_WIDTH; i++)
    {
        putchar('-');
    }
    putchar('+');
    putchar('\n');
}

void empty_line(void)
{

    int i;
    putchar('|');
    for (i = 0; i < MENU_WIDTH; i++)
    {
        putchar(' ');
    }
    putchar('|');
    putchar('\n');
}

void centered_line(const char *text)
{
    int length = (int)strlen(text); // length of the text
    int free_space = MENU_WIDTH - length;
    int left_space;
    int right_space;
    int i;

    left_space = free_space / 2;
    right_space = free_space - left_space;

    putchar('|');
    for (i = 0; i < left_space; i++)
    {
        putchar(' ');
    }

    printf("%s", text);

    for (i = 0; i < right_space; i++)
    {
        putchar(' ');
    }
    putchar('|');
    putchar('\n');
}

void left_line(const char *text)
{
    int lenght = (int)strlen(text);
    int i;

    if (lenght > MENU_WIDTH)                    // safety for looks
    { 
        lenght = MENU_WIDTH;
    }
    

    putchar('|');
    printf("%s", text);

    for (i = lenght; i < MENU_WIDTH; i++)
    {
        putchar(' ');
    }
    putchar('|');
    putchar('\n');
}

void print_menu(void)
{
    line_horizontal();
    centered_line("MINI PROJECT - ET");
    centered_line("Resistor Network Tool");
    line_horizontal();
    left_line(" [1] Enter circuit (matrix)");
    left_line(" [2] Compute equivalent resistance");
    left_line(" [3] Output total voltage / current");
    left_line(" [4] Show circuit (matrix)");
    left_line(" [5] Show virtual representation of circuit");
    left_line(" [6] Quit");

    line_horizontal();
    centered_line("By Johannes Kiener & Paul Steinhof");
    line_horizontal();
    
}
