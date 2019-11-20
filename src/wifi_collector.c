#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure_and_list.h"
#include "display_data.h"
#include "io.h"

/**Function wificollector_collect**********************************************

  Synopsis           asks user to introduce the number of the cell to be read
                     then invokes a function read_access_point and push to read
                     new access point and store it in a list of access points -
                     - wifi_list

******************************************************************************/
void wificollector_collect()
{
  int selected_cell = 0;
  char cell_name[20];                                                    //buffer for the name of selected cell's file
  char cell_number[10];                                                  //buffer for the string "Cell x" which indicates new access point in a cell
  FILE *fp;
  char *buff = NULL;                                                     //buffer for sequentially read lines
  char another_access_point = 'N';

  do {
    printf("What cell do you want to collect? (1-21)\n");
    scanf("%d", &selected_cell);

    while (selected_cell < 1 || selected_cell > 21)
    {
      printf("Wrong number!\n");
      printf("What cell do you want to collect? (1-21)\n");
      scanf("%d", &selected_cell);
    }

    sprintf(cell_name, "info_cell_%d.txt", selected_cell);
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
      while (getline(&buff, &bytes_number, fp) != -1)                      //If everything is fine, read the first line
      {
        if (strcmp(remove_new_line(buff), cell_number) == 0)               //If the line == "Cell x", where x = [1,21]
        {
          wifi_data* new_ap = read_access_point(fp, buff);                 //read new access point
          push(new_ap, sizeof(new_ap));                                    //and push it to the list
        }
      }
    }
    fclose(fp);
    printf("Do you want to add another access point? [y/N]\n");
    scanf(" %c", &another_access_point);
  } while(another_access_point == 'y');
}

/**Function wificollector_select_best******************************************

  Synopsis

  SideEffects

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
