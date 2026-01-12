/*
07.01.2026
Programm Läuft 
Johannes Kiener

*/






#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define max_linindex_allowed_char 2
#define max_columindex_allowd_char 1
#define max_number_of_chars 2

char allowed_char[4][15] = 
    {
         {'n' , 'u' , 'm' , 'k' , 'M', 'G' , 'R' , 'r'},
         { '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , '0' },
         {',' , '.'}
    };

 int user_input(r_value_user * str_p){

       // const char * p_input = &input;
   int i = 0; //index für input
   int i_2 = 0;
   int i_2_2 = 0; // index für allowd_char
   int Faktor = 0;
   float r_value = 0;
   int number_with = 0; //Stellenwertigkeit verfolgen
  // r_value_user r_value_display; // struct um benutzer Wert anzuzeigen
   int failed = 0; //falls nichts sinvolles im buffer 
   short prefix = 0;
   short count_chars_in_number = 0;
   short komma_1 = 0;

   str_p ->point_index = 0;
   str_p ->prefix_index = 0;

do{
    char input[100];
    printf("Widerstandswert eingeben:\n");
    fgets(input, sizeof(input), stdin); // speichert Eingabe in input also ... \n \0  - stdin ist die Quelle der Eingabe
    input[strcspn(input, "\n")] = '\0'; // ersetzt \n mit \0 terminator um \n zu erntfernen

   // const char * p_input = &input;
    i = 0; //index für input
    i_2 = 0;
    i_2_2 = 0; // index für allowd_char
    Faktor = 0;
    r_value = 0;
    number_with = 0; //Stellenwertigkeit verfolgen
  // r_value_user r_value_display; // struct um benutzer Wert anzuzeigen
    failed = 0; //falls nichts sinvolles im buffer 
    prefix = 0;
    count_chars_in_number = 0;
    komma_1 = 0;

   str_p -> komma = '\0'; // wenn komma steht dann ensprechendes char enthalten 


   do{
       while(isspace(input[i])) i++ ; //entfernt alle leerzeichen etc. 
       //Was passiert wenn nichts gefunden wird ?
       while(input[i] != allowed_char[i_2][i_2_2] && !failed) // solange wie kein Zeichen gefunden und zulässiges Zeichen enthalten
          {
             i_2_2++; // Eingabe auf sinvolles untersuchen
             if((i_2 == 0 && i_2_2 > 7) || (i_2 == 1 && i_2_2 > 9) ) i_2++, i_2_2 = 0; // oder ende erreicht von ersten Zeile ? 
             if(i_2 >= max_linindex_allowed_char && i_2_2 > max_columindex_allowd_char)failed = 1;
          }
       if(!failed)
           {
             if(number_with && i_2 == 1) 
                {
                  for(int x = number_with; x > 0; x--)
                    {
                      str_p -> number[x] = str_p -> number[x - 1]; //schiebt Wert um eine stelle Wenn z.b. 70   (*str_p).number  strp -> number
                    }
                }
             if(i_2 == 1) str_p -> number[0] = allowed_char[i_2][i_2_2], number_with++; // Wert speichern und Breite vergrößern wenn neuer Wert hinzukommt

             //prefix speichern
             else if(i_2 == 0)
               {
                  str_p -> prefix = allowed_char[i_2][i_2_2];
                  str_p->index_for_prefix_number = i_2_2; // int array mit Zahlenwerte kann so ausgelesen werden
                  prefix ++ ;
                  if(komma_1) str_p -> prefix_index = number_with + 2; //Prefix speichern
                  else str_p -> prefix_index = number_with + 1; 
                  count_chars_in_number++;
                } 

             //Komma speichern
             else if (i_2 == 2)
               {
                  str_p -> komma = allowed_char[i_2][i_2_2];
                  str_p -> point_index = number_with + 1; // Wenn ,k dann muss fehlermeldung kommen 
                  count_chars_in_number++; // vermutlich nicht nötig
                  komma_1 ++;
                }
             i++; //increment wenn kein whitespace kommt
             i_2 = 0;
             i_2_2 = 0;

           }else
              {
                 printf("Bitte korrekte Werte eingeben\n");
                 break;
              }
            
            if(count_chars_in_number > max_number_of_chars || prefix > 1 || komma_1 > 1)
              {
                 printf("Bitte korrekt eingeben! \n");
                 failed = 1;
              }



    }while (input[i] != '\0'); //sizeof(char) == 1 byte
    
    if(prefix || komma_1) str_p -> with = number_with + 1; // 7k with = 2
    if(komma_1 && prefix) str_p -> with = number_with + 2;  //7.2
    if(!komma_1 && !prefix) str_p -> with = number_with; 


    if((str_p ->prefix_index && str_p->point_index && ((str_p->prefix_index != str_p->with)) || (str_p ->prefix_index && str_p->point_index) && number_with == 1)) failed = 1, printf("Falsche Eingabe\n"); // z.b. 12k,5 

}while(failed);
/*
    if(prefix || komma_1) str_p -> with = number_with + 1; // 7k with = 2
    if(komma_1 && prefix) str_p -> with = number_with + 2;  //7.2
    if(!komma_1 && !prefix) str_p -> with = number_with;
*/


   //After this buffer is succesful read out
  
    //Aufruf von struct to value damit Wert man lf erhält 
    struct_to_value(str_p);


    return str_p -> with;
}