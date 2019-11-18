#include "structure_and_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "menu.h"
#include "display_data.h"

wifi_data data;
wifi_list *data_read;
int main(int argc, char const *argv[])
{
  data.channel = 5;
  push(&data, sizeof(data));
  data.channel = 6;
  push(&data, sizeof(data));
  data.channel = 7;
  push(&data, sizeof(data));
  data.channel = 10;
  push(&data, sizeof(data));
  while((data_read = move_head())!=NULL)
    printf("%d\n", data_read->data->channel);
  wificollector_delete_net(10);
    printf("\n");
  while((data_read = move_head())!=NULL)
    printf("%d\n", data_read->data->channel);

  display_all_access_points();
  return 0;
}
