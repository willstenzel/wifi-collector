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
  FILE *fp = NULL;
  char* buff = NULL;                                                     //buffer for sequentially read lines
  char another_access_point = 'N';
  wifi_data* new_ap = NULL;
  size_t bytes_number = 0;
  char char_nbr;


  do
  {
    printf("What cell do you want to collect? (1-21)\n");
    char_nbr = scanf(" %d", &selected_cell);
    if(char_nbr == -1)
      break;

    while (getc(stdin)!='\n')
      continue;
    while (selected_cell < 1 || selected_cell > 21)
    {
      printf("Wrong number!\n");
      printf("What cell do you want to collect? (1-21)\n");
      char_nbr = scanf(" %d", &selected_cell);

      while (getc(stdin)!='\n')
        continue;
    }
    if(char_nbr == -1)
      break;
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
      while (getline(&buff, &bytes_number, fp) >= 0)                      //If everything is fine, read the first line
      {
        buff[strlen(buff)-1] = '\0';
        if (strcmp(buff, cell_number) == 0)               //If the line == "Cell x", where x = [1,21]
        {
          new_ap = read_access_point(fp, buff, bytes_number);   //read new access point
          printf("Loaded %s from cell number %d\n", new_ap->ESSID, new_ap->cell_ind);
          push(new_ap);
                                          //and push it to the list
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
  if(get_head() == NULL)
  {
    printf("Data list is empty\n");
    return;
  }
    char char_nbr, found = 0;
    char essid[MAX_ESSID_LENGTH];

    printf("Indicate the ESSID: ");
    char_nbr = scanf(" %s", essid);

    if(char_nbr == -1)
      return;


#ifdef DEBUG
printf("%d ESSID --> %s\n", len, buffer);
#endif

    // loop throught all the access points
    wifi_list *wifi_ptr = NULL;

    while((wifi_ptr = move_head()) != NULL)
    {
      if (string_compare(essid, wifi_ptr->data->ESSID, strlen(essid)) == 0)
      {
        // print each access point that has a matching ESSID
        display_single_access_point(wifi_ptr->data);
        found = 1;
      }
    }
    if(!found)
      printf("No network %s found", essid);
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

  if(get_head() == NULL)
  {
    printf("Data list is empty\n");
    return;
  }

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

/**Function wificollector_delete_net******************************************

  Synopsis     deletes all data concerning one net with correct ESSID

  SideEffects  None

******************************************************************************/
void wificollector_delete_net()
{
  wifi_list *current, *previous = list_head;

  if(get_head() == NULL)
  {
    printf("Data list is empty\n");
    return;
  }
  char char_nbr;
  char essid[MAX_ESSID_LENGTH];

  printf("Indicate the ESSID: ");
  char_nbr = scanf(" %s", essid);

  if(char_nbr == -1)
    return;


#ifdef DEBUG
printf("ESSID --> %s\n", essid);
#endif

  while((current = move_head()) != NULL)
  {
    if (strcmp(essid, current->data->ESSID) == 0)
    {
      if(current == list_head)              //if it is first element
        list_head = current->next;
      else
        previous->next = current->next;
      printf("Deleted %s from cell number %d\n", current->data->ESSID, current->data->cell_ind);
      free(current->data);
      free(current);
    }
    previous = current;
  }
}


/** Function wificollector_export ******************************************

  Synopsis     Writes a binary file with the currently stored data

  SideEffects  Creates a binary file containing all the wifi data

******************************************************************************/
void wificollector_export() {


  char file_name[40];
  char selected_name[40];

  if(get_head() == NULL)
  {
    printf("Data list is empty\n");
    return;
  }
  // Ask user to get the name of the file
  printf("Indicate the name of the file:\n");
  if(scanf("%s", selected_name) == -1)
    return;


  sprintf(file_name, "%s.bin", selected_name);
  FILE *fd = fopen(file_name, "wb");

  if (fd == NULL)
  {
      printf("ERROR: There was an error opening your file");
      return;
  }

  wifi_list *wifi_ptr = NULL;

  while((wifi_ptr = move_head()) != NULL)
  {
	    // Save the
    	fwrite(&(wifi_ptr->data->cell_ind), sizeof(wifi_ptr->data->cell_ind), 1, fd);
      fwrite((wifi_ptr->data->MAC), sizeof(wifi_ptr->data->MAC), 1, fd);
      fwrite((wifi_ptr->data->ESSID), sizeof(wifi_ptr->data->ESSID), 1, fd);

      fwrite(&(wifi_ptr->data->mode), sizeof(wifi_ptr->data->mode), 1, fd);
      fwrite(&(wifi_ptr->data->channel), sizeof(wifi_ptr->data->channel), 1, fd);
      fwrite(&(wifi_ptr->data->encrytpion_key), sizeof(wifi_ptr->data->encrytpion_key), 1, fd);
      fwrite((wifi_ptr->data->quality), sizeof(wifi_ptr->data->quality), 1, fd);



  }

  fclose(fd);

  return;

}



/** Function wificollector_import ******************************************

  Synopsis     Reads a binary file with the saved wifi data

  SideEffects  Adds the data from the file into the local memory

******************************************************************************/
void wificollector_import()
{
  char file_name[40];
  char selected_name[40];

  printf("Indicate the name of the file:\n");
  if(scanf("%s", selected_name) == -1)
    return;
  sprintf(file_name, "%s.bin", selected_name);

  FILE *fd = fopen(file_name, "rb");

  if (fd == NULL)
  {
      printf("ERROR: There was an error opening your file");
      return;
  }

  wifi_data* local_data = (struct wifi_data*) malloc(sizeof(struct wifi_data)); //local wifi_data object
  wifi_list* wifi_ptr;

  while(!feof(fd))
  {
      wifi_ptr = get_head();
#ifdef DEBUG
      printf("new object\n");
#endif
    	fread(&(local_data->cell_ind), sizeof(local_data->cell_ind), 1, fd);
      fread((local_data->MAC), sizeof(local_data->MAC), 1, fd);
      fread((local_data->ESSID), sizeof(local_data->ESSID), 1, fd);

      fread(&(local_data->mode), sizeof(local_data->mode), 1, fd);
      fread(&(local_data->channel), sizeof(local_data->channel), 1, fd);
      fread(&(local_data->encrytpion_key), sizeof(local_data->encrytpion_key), 1, fd);
      fread((local_data->quality), sizeof(local_data->quality), 1, fd);

      short alread_present = 0, inc = 0;
      while(wifi_ptr!= NULL)
      {
        inc++;
        if(!string_compare((char*)local_data->MAC, (char*)wifi_ptr->data->MAC, 6))
        {
          if(local_data->cell_ind == wifi_ptr->data->cell_ind)
          {
#ifdef DEBUG
            printf("found copy\n");
#endif
            alread_present = 1;
            break;
          }
        }
        wifi_ptr=wifi_ptr->next;
      }
#ifdef DEBUG
      printf("objects in list: %d\n", inc);
#endif
      if (alread_present == 0)
      {
#ifdef DEBUG
        printf("pushing...: %s\n", local_data->ESSID);
#endif
        push(local_data);
      }
    }
    free(local_data);
}
void wificollector_sort()
{
  sort_list();
}
