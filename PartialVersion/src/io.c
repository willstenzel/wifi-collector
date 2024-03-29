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
  char* ind = extract(line, " ", 3, 1);
  local_data->cell_ind = atoi(ind);

  //MAC
#ifdef DEBUG
printf("getting MAC\n");
#endif
  ssize_t bytes_read = getline(&line, &bytes_number, fp);

  char* hext = extract(line, " ", 3, 1);                                              //first split read line into two parts
  for (int i = 0; i < 6; i++)
  {
    char* hex = extract(hext, "::", 7, i);                                      //then from the second part
    int num_hex = (int)strtol(hex, NULL, 16);                                   //extract consecutive hex values
    local_data->MAC[i] = num_hex;
  }

  //ESSID
#ifdef DEBUG
printf("getting ESSID\n");
#endif
  bytes_read = getline(&line, &bytes_number, fp);

  char* essid = extract(line, "\"", 4, 1);
  //local_data->ESSID = essid;
  local_data->ESSID = malloc(strlen(essid)+1);
  strcpy(local_data->ESSID, essid);
  printf("%s\n", essid);
  printf("%s\n", local_data->ESSID);
  //free(local_data->ESSID);
  //printf("%s\n", local_data->ESSID);

  //Mode
#ifdef DEBUG
printf("getting mode\n");
#endif
  bytes_read = getline(&line, &bytes_number, fp);

  char* mode_name = extract(line, "::", 3, 1);

  if (!strcmp(mode_name, "Auto"))
  {
    local_data->mode = autos;
  }
  else if (!strcmp(mode_name, "Ad-Hoc"))
  {
    local_data->mode = adhoc;
  }
  else if (!strcmp(mode_name, "Managed"))
  {
    local_data->mode = managed;
  }
  else if (!strcmp(mode_name, "Master"))
  {
    local_data->mode = master;
  }
  else if (!strcmp(mode_name, "Repeater"))
  {
    local_data->mode = repeater;
  }
  else if (!strcmp(mode_name, "Secondary"))
  {
    local_data->mode = secondary;
  }
  else if (!strcmp(mode_name, "Monitor"))
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

  char* channel = extract(line, "::", 3, 1);
  local_data->channel = atoi(channel);

  //Encryption key
#ifdef DEBUG
printf("getting key\n");
#endif
  bytes_read = getline(&line, &bytes_number, fp);

  char* key = extract(line, "::", 3, 1);
  if (!strcmp(key, "on"))
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

  char* qualityt = extract(line, "=", 4, 1);
  for (int i = 0; i < 2; i++)
  {
    char* quality = extract(qualityt, "/", 4, i);                                   //then from the second part
    local_data->quality[i] = (short int)atoi(quality);                                //extract first(x) and second(y) value x/y
  }

  //Read other two lines, but don't store them
  bytes_read = getline(&line, &bytes_number, fp);                               //It's neccessary to read those two lines
  bytes_read = getline(&line, &bytes_number, fp);
#ifdef DEBUG
printf("freeing line\n");
#endif                           //so we read correct values in the next loop iteration
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
