#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure_and_list.h"
#include "display_data.h"
#include "io.h"

/**CFile***********************************************************************

  FileName    wifi_collector.c

  Synopsis    conatins all the functionality for the wifi_collector options
              in the menu

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


/**Function wificollector_collect**********************************************

  Synopsis           asks user to introduce the number of the cell to be read
                     then invokes a function read_access_point and push to read
                     new access point and store it in a list of access points -
                     - wifi_list

******************************************************************************/
void wificollector_collect()
{
  int selected_cell = 0;
  char cell_name[50];                                                    //buffer for the name of selected cell's file
  char cell_number[10];                                                  //buffer for the string "Cell x" which indicates new access point in a cell
  FILE *fp;
  char* buff = NULL;                                                     //buffer for sequentially read lines
  char another_access_point = 'N';
  wifi_data* new_ap = NULL;

  do {
    printf("What cell do you want to collect? (1-21)\n");
    scanf(" %d", &selected_cell);

    while (selected_cell < 1 || selected_cell > 21)
    {
      printf("Wrong number!\n");
      printf("What cell do you want to collect? (1-21)\n");
      scanf(" %d", &selected_cell);
    }

    sprintf(cell_name, "../cells/info_cell_%d.txt", selected_cell);
    sprintf(cell_number, "Cell %d", selected_cell);

    fp = fopen(cell_name, "r");
    if (fp == NULL)
    {
      printf("Could not open file");                                       //If given file doesn't exist, stop exection
      break;
    }
    else
    {
      size_t bytes_number = 0;
      while (getline(&buff, &bytes_number, fp) >= 0)                      //If everything is fine, read the first line
      {
        if (strcmp(remove_new_line(buff), cell_number) == 0)               //If the line == "Cell x", where x = [1,21]
        {
          new_ap = read_access_point(fp, buff, bytes_number);   //read new access point
          printf("%s\n", new_ap->ESSID);
          push(new_ap, sizeof(new_ap));                                  //and push it to the list
          free(new_ap);
        }
      }
    }
    free(buff);
    buff = NULL;
    fclose(fp);
    printf("Do you want to add another access point? [y/N]\n");
    scanf(" %c", &another_access_point);
  } while(another_access_point == 'y');
  //return new_ap;
}

/**Function wificollector_show_data_one_network *******************************

  Synopsis

  SideEffects

******************************************************************************/
void wificollector_show_data_one_network()
{
    printf("Indicate the ESSID (use “”): \n");
    // scanf or get line for the next line
    char *buffer;
    size_t buff_max = 80;
    size_t bytes_read;

    buffer = (char *)malloc(buff_max * sizeof(char));

    bytes_read = getline(&buffer, &buff_max, stdin);

    char line[buff_max];

    // strcmp(remove_new_line(buffer), line);

    char* essid = extract(buffer, "\"", 3, 0);

    printf("ESSID --> %s\n", essid);  // TODO: Remove after testing

    // loop throught all the access points
    wifi_list *wifi_ptr = NULL;

    while((wifi_ptr = move_head()) != NULL)
    {
      if (strcmp(essid, wifi_ptr->data->ESSID) == 0)
      {
        // print each access point that has a matching ESSID
        display_single_access_point(wifi_ptr->data);
      }
    }
}


/**Function wificollector_select_best******************************************

  Synopsis     Selects and displays data for the access point with the largest
               signal strength

  SideEffects  None

******************************************************************************/
void wificollector_select_best()
{
  wifi_data *best_network = NULL;
  wifi_list *wifi_ptr = NULL;

  while((wifi_ptr = move_head()) != NULL)
  {
    if (best_network == NULL)
    {
      best_network = wifi_ptr->data;
    }
    else if (best_network->quality[0] < wifi_ptr->data->quality[0])
      {
        best_network = wifi_ptr->data;
      }
  }
  display_single_access_point(best_network);
}
