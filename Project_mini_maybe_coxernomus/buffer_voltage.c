#include <stdio.h>
#include "buffer.h"
#include <string.h>
#include <math.h>
#include <ctype.h>

int user_input_voltage(storage_voltage_imput * str_p){

    //Buffer auswerten
  int index_buffer_v = 0;
  int index_row_allowed_chars = 0;
  int index_col_allowed_char = 0;
  int number_with_v = 0;
  int index_komma_v = 0;
  int index_prefi_v = 0;
  int amount_prefix = 0;
  int amount_komma = 0;
  int error = 0;
  short index_value_prefix_v = 0;


  char allowed_chars_v[][11]=
    {
       {'0','1','2','3','4','5','6','7','8','9','\0'},
       {'n','u','m','k','M','G','\0'},
       {',','.', '\0'}
    };

    double values_prefix_v[7] = {1e-9, 1e-6, 1e-3, 1e3, 1e6, 1e9, 1};

     //Speicherort des inputstreams
     char buffer_v[100] = {'\0'};



  do{ // solange nicht '\0' gelesen wird im buffer_v
      
     if(error) printf("falsche Einngabe!\n");

     index_buffer_v = 0;
     index_row_allowed_chars = 0;
     index_col_allowed_char = 0;
     number_with_v = 0;
     index_komma_v = 0;
     index_prefi_v = 0;
     amount_prefix = 0;
     amount_komma = 0;
     error = 0;
     index_value_prefix_v = 6;

     fgets(buffer_v, sizeof(buffer_v), stdin); // Speicherort Grenze Quelle
     buffer_v[strcspn(buffer_v, "\n")] = '\0'; // ersetzt \n mit \0 terminator um \n zu erntfernen 
     if(isspace(buffer_v[index_buffer_v])) index_buffer_v ++; // Leerzeichen überspringen 



      //Eingabe Auswerten

      do
       {
          if(buffer_v[index_buffer_v] == allowed_chars_v[index_row_allowed_chars][index_col_allowed_char])
            {
                if(index_row_allowed_chars == 0)
                 {
                     //Number schieben wenn number_with_v -(amount_komma + amount_prefix)
                     if(number_with_v && (number_with_v -(amount_komma + amount_prefix))) // bedinung für Number schieben
                       {
                         for (int jk = (number_with_v - amount_komma-amount_prefix); jk > 0; jk--)
                           {
                             str_p->number_v[jk] = str_p->number_v[jk - 1];
                           }
                       }
                     str_p->number_v[0] = allowed_chars_v[index_row_allowed_chars][index_col_allowed_char];
                     number_with_v++;
                 }
                if(index_row_allowed_chars == 1) str_p->prefix = allowed_chars_v[index_row_allowed_chars][index_col_allowed_char],index_prefi_v = number_with_v, number_with_v++, amount_prefix++, index_value_prefix_v = index_col_allowed_char;
                if(index_row_allowed_chars == 2 && (buffer_v[index_buffer_v] != '\0')) str_p->komma = allowed_chars_v[index_row_allowed_chars][index_col_allowed_char], index_komma_v = number_with_v, number_with_v++, amount_komma++;  
                index_col_allowed_char = 0;
                index_row_allowed_chars = 0;
                index_buffer_v++;
            }else{
                   index_col_allowed_char ++;
                   //printf("%c",allowed_chars_v[index_row_allowed_chars][index_col_allowed_char] );
                   if(allowed_chars_v[index_row_allowed_chars][index_col_allowed_char] == '\0') index_row_allowed_chars++, index_col_allowed_char = 0;
                   
                } 
          

        }while(index_row_allowed_chars < 3 );

           //Eingabefehler      
         if(amount_komma > 1 || amount_prefix > 1 || ((index_komma_v > index_prefi_v) && (amount_komma&&amount_prefix)) || (index_prefi_v && index_komma_v &&((index_prefi_v + 1) != number_with_v ))) error = 1;

         if(index_row_allowed_chars == 3 && buffer_v[index_buffer_v] != '\0') error = 1; // Wert in in allowed chars
      
     //index_buffer_v++;

    }while(buffer_v[index_buffer_v] != '\0' || error);

//******************************************************************************************************* */

    //Umwandlung von chars in Wert

    /*
    Prefix als Komma 
    Komma als Komma 
    
    12,34 komma_index = 2 Power = Zahlweite also 5 - 1 - 2 = 2
    12,3456 komma index 2 Power = 7 - 1 - 2 = 4  Komma erhöht Weite um 1 und index Komma muss abgezogen werden
    */
     
    int Potenz_v = 0;

    Potenz_v = number_with_v - index_komma_v - (1 && amount_prefix) - (1 && amount_komma); // 12,34k  6 - 2 - 1 - 1 = 2
    //3k2 
    if(!amount_komma) Potenz_v = Potenz_v - index_prefi_v; // 3 - 0 - 1 - 0 = 2   2 - 1 = 1
    //if((amount_komma || amount_prefix) && (index_komma_v == 0 || index_prefi_v == 0)) Potenz_v -= 2;
    //Zahlen char array in Wert wandeln 
    if(!amount_komma && !amount_prefix) Potenz_v = 0;
    // 34,34k number_with_v - (1 && amount_komm) - (1 && amount_prefix) wäre hier 4

    number_with_v -= (1 && amount_komma) + (1 && amount_prefix);

    short index_number_v = number_with_v - 1;//weil 0 mitgezählt wird bei array index
    str_p ->voltage_value = 0;

    for(; index_number_v >= 0; index_number_v--)
      {
         str_p->voltage_value += (str_p->number_v[index_number_v] - '0');
         if(index_number_v) str_p->voltage_value *= 10;
      }

    //Prefix anwenden auf Zahl und Komma

    str_p->voltage_value /= pow(10,Potenz_v);
    str_p->voltage_value *= values_prefix_v[index_value_prefix_v];





    //printf("----->%lf", str_p->voltage_value);





  }