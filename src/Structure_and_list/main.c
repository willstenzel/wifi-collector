#include "structure_and_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

wifi_data data;
wifi_list *data_read;
int main(int argc, char const *argv[])
{
  data.channel = 5;
  push(&data, sizeof(data));
  data_read = get_head();
  printf("%d", data_read->data->channel);
  return 0;
}
