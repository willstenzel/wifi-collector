#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure_and_list.h"
#include "io.h"

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
  getline(&line, &bytes_number, fp);                               //It's neccessary to read those two lines
  getline(&line, &bytes_number, fp);
                         //so we read correct values in the next loop iteration
  //free(line);
  return local_data;
}

void string_copy(char* destination, char* source, char char_nbr)
{
  for(int i = 0; i < char_nbr; i ++)
  {
    destination[i] = source[i];
  }
}
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
