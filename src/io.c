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
  ssize_t bytes_read = getline(&line, &bytes_number, fp);

  for (int i = 0; i < 6; i++)
  {
    int num_hex = (int)strtol(&line[i*2+i+9], NULL, 16);                                    //extract consecutive hex values
    local_data->MAC[i] = num_hex;
  }

  //ESSID
#ifdef DEBUG
printf("getting ESSID\n");
#endif

  bytes_read = getline(&line, &bytes_number, fp);
  int len = strlen(line);
  printf("len: %d", len);
  len -=  8;
  line[len + 6] = '\0';
  string_copy(local_data->ESSID, &line[7], len);
  printf("%s\n", &line[7]);
  // printf("%s\n", local_data->ESSID);

  //Mode
#ifdef DEBUG
printf("getting mode\n");
#endif
  bytes_read = getline(&line, &bytes_number, fp);

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
  bytes_read = getline(&line, &bytes_number, fp);
  local_data->channel = atoi(&line[8]);

  //Encryption key
#ifdef DEBUG
printf("getting key\n");
#endif
  bytes_read = getline(&line, &bytes_number, fp);

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
  bytes_read = getline(&line, &bytes_number, fp);                               //first split read line into two parts
  line[10] = '\0';
  local_data->quality[0] = (short int)atoi(&line[8]);
  local_data->quality[1] = (short int)atoi(&line[11]);


  //Read other two lines, but don't store them
  bytes_read = getline(&line, &bytes_number, fp);                               //It's neccessary to read those two lines
  bytes_read = getline(&line, &bytes_number, fp);
                         //so we read correct values in the next loop iteration
  //free(line);
  return local_data;
}

/**Function remove_new_line****************************************************

  Synopsis           removes trailing new line symbol \n from read line

  Parameters         string - line to be corrected

  Return value       pointer to corrected line

  SideEffects        None

******************************************************************************/
char* remove_new_line(char* string)
{
  char key[] = "\n";
  size_t position = strcspn(string, key);
  if (position != strlen(string))
    string[position] = 0;
  return string;
}

/**Function extract************************************************************

  Synopsis           uses strtok() function to split read line and returns
                     required string

  Parameters         string - line from which we want to extract required string
                     delim - delimeter for strtok() functions
                     length - length of the table to which extracted strings
                     will be stored, than from that table we select required
                     string to be returned
                     position - specifies the position in the words table to
                     where the required string is stored

  Return value       pointer to the required string

  SideEffects        None

******************************************************************************/
char* extract(char* string, char* delim, int length, int position)
{
  char *words[length];                                                          //create list to store consecutive strings
  int i = 0;
  char *ptr = strtok(string, delim);
  while(ptr != NULL)
  {
    words[i++] = ptr;
    ptr = strtok(NULL, delim);
  }
  words[position] = remove_new_line(words[position]);                           //remove \n from string to be returned, if present
  return words[position];
}
void string_copy(char* destination, char* source, char char_nbr)
{
  for(int i = 0; i < char_nbr; i ++)
  {
    destination[i] = source[i];
  }
}
