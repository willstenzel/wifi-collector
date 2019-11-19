#include <stdio.h>
#include <stdlib.h>
#include "structure_and_list.h"
#include "display_data.h"

void wificollector_select_best()
{
  wifi_data *best_network;
  wifi_list *wifi_ptr;

  while((wifi_ptr = move_head()) != NULL)
  {
    if (best_network == NULL)
    {
      best_network = wifi_ptr->data;
    }
    else if (best_network->quality[0] > wifi_ptr->data->quality[0])
      {
        best_network = wifi_ptr->data;
      }
  }
  display_single_access_point(best_network);
}
