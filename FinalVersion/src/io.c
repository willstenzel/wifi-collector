#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure_and_list.h"
#include "io.h"

/**CFile***********************************************************************

  FileName    io.c

  Synopsis    Contains functions needed for the input of access points

  Description Contains core functionality to be able ro read a wifi access
              point along with some helper functions like string_copy and
              string_compare

  Copyright   [Copyright (c) 2012 Carlos III University of Madrid
  All rights reserved.

  Permission is hereby granted, without written agreement and without license
  or royalty fees, to use, copy, modify, and distribute this software and its
  documentation for any purpose, provided that the above copyright notice and
  the following two paragraphs appear in all copies of this software.

  IN NO EVENT SHALL THE CARLOS III UNIVERSITY OF MADRID BE LIABLE TO ANY PARTY
  FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING
  OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE CARLOS III
  UNIVERSITY OF MADRID HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  THE CARLOS III UNIVERSITY OF MADRID SPECIFICALLY DISCLAIMS ANY WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
  "AS IS" BASIS, AND CARLOS III UNIVERSITY OF MADRID HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.]

******************************************************************************/

/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/

/**Function read_access_point**************************************************

  Synopsis           reads consecutive fields of the access point from opened
                     cell file and stores them in a local wifi_data object

  Parameters         fp - pointer to the open file
                     line - buffer for consecutive lines read from file

  Return value       pointer to newly created wifi_data object, which stores
                     read data

  SideEffects        None

******************************************************************************/
wifi_data* read_access_point(FILE *fp, char* line, size_t bytes_number)
{
  wifi_data* local_data = (struct wifi_data*) malloc(sizeof(struct wifi_data)); //local wifi_data object

  //Cell identifier
  #ifdef DEBUG
  printf("atoing cell\n");
  #endif
  local_data->cell_ind = atoi(&line[5]);

  //MAC
  #ifdef DEBUG
  printf("getting MAC\n");
  #endif
  getline(&line, &bytes_number, fp);

  for (int i = 0; i < 6; i++)
  {
    int num_hex = (int)strtol(&line[i*2+i+9], NULL, 16);                                    //extract consecutive hex values
    local_data->MAC[i] = num_hex;
  }

  //ESSID
  #ifdef DEBUG
  printf("getting ESSID\n");
  #endif

  getline(&line, &bytes_number, fp);
  int len = strlen(line);
  len -=  8;
  line[len + 6] = '\0';
  string_copy(local_data->ESSID, &line[7], len);


  //Mode
  #ifdef DEBUG
  printf("getting mode\n");
  #endif
  getline(&line, &bytes_number, fp);

  if (!strcmp(&line[5], "Auto\n"))
  {
    local_data->mode = autos;
  }
  else if (!strcmp(&line[5], "Ad-Hoc\n"))
  {
    local_data->mode = adhoc;
  }
  else if (!strcmp(&line[5], "Managed\n"))
  {
    local_data->mode = managed;
  }
  else if (!strcmp(&line[5], "Master\n"))
  {
    local_data->mode = master;
  }
  else if (!strcmp(&line[5], "Repeater\n"))
  {
    local_data->mode = repeater;
  }
  else if (!strcmp(&line[5], "Secondary\n"))
  {
    local_data->mode = secondary;
  }
  else if (!strcmp(&line[5], "Monitor\n"))
  {
    local_data->mode = monitor;
  }
  else
  {
    local_data->mode = unknown;
  }

  //Channel
  #ifdef DEBUG
  printf("getting channel\n");
  #endif
  getline(&line, &bytes_number, fp);
  local_data->channel = atoi(&line[8]);

  //Encryption key
  #ifdef DEBUG
  printf("getting key\n");
  #endif
  getline(&line, &bytes_number, fp);

  if (!strcmp(&line[15], "on"))
  {
    local_data->encrytpion_key = On;
  }
  else
  {
    local_data->encrytpion_key = Off;
  }

  //Quality
  #ifdef DEBUG
  printf("getting quality\n");
  #endif
  getline(&line, &bytes_number, fp);                               //first split read line into two parts
  line[10] = '\0';
  local_data->quality[0] = (short int)atoi(&line[8]);
  local_data->quality[1] = (short int)atoi(&line[11]);


  //Read other two lines, but don't store them
  getline(&line, &bytes_number, fp);
  getline(&line, &bytes_number, fp);
  return local_data;
}

/**Function string_copy**************************************************

  Synopsis           copies string from source to destination with char_nbr
                     number of characters

  Parameters         destitantion - pointer to destination char array
                     source - pointer to source char array
                     char_nbr - numbers of characters to copy

  Return value       none

  SideEffects        ensure that there is enouth space allocated for destination

******************************************************************************/
void string_copy(char* destination, char* source, char char_nbr)
{
  for(int i = 0; i < char_nbr; i ++)
  {
    destination[i] = source[i];
  }
}

/**Function string_compare**************************************************

  Synopsis           copies string from source to destination with char_nbr
                     number of characters

  Parameters         string1 - pointer to first char array
                     string2 - pointer to second char array
                     char_nbr - numbers of characters to comapre

  Return value       [0] - strings are same
                     [1] - strings differ

  SideEffects        none

******************************************************************************/
int string_compare(char* string1, char* string2, char char_nbr)
{
  for(int i = 0; i < char_nbr; i ++)
  {
    if (string1[i] != string2[i])
    {
      return 1;
    }
  }
  return 0;
}
