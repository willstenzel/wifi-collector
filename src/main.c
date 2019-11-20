#include "structure_and_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "menu.h"
#include "display_data.h"
#include "wifi_collector.h"

wifi_data data;
wifi_list *data_read;
int main(int argc, char const *argv[])
{
  // data.channel = 5;
  // data.quality[0] = 6;
  // data.quality[1] = 70;
  // push(&data, sizeof(data));
  // data.channel = 6;
  // data.quality[0] = 40;
  // data.quality[1] = 70;
  // push(&data, sizeof(data));
  // data.channel = 7;
  // data.quality[0] = 30;
  // data.quality[1] = 70;
  // push(&data, sizeof(data));
  // data.channel = 10;
  // data.quality[0] = 20;
  // data.quality[1] = 70;
  // push(&data, sizeof(data));
  // while((data_read = move_head())!=NULL)
  //   printf("%d\n", data_read->data->channel);
  // wificollector_delete_net(10);
  //   printf("\n");
  // while((data_read = move_head())!=NULL)
  //   printf("%d\n", data_read->data->channel);
  //
  // display_all_access_points();
  // printf("---------------------------------------\n");
  // wificollector_select_best();
  //wifi_data* x = wificollector_collect();
  wificollector_collect();
  //display_single_access_point(x);
  display_all_access_points();
  return 0;
}
