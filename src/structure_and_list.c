
#include "structure_and_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "io.h"
#include "display_data.h"

/**CFile***********************************************************************

  FileName    structure_and_list.c

  Synopsis    conatins all functions connected to linked list and it's
              structure.

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

/**Function list_init**********************************************************

  Synopsis           initialize the variable that stores the list head

  SideEffects        sets the variable list_head to NULL

******************************************************************************/
void list_init(void)
{
  list_head = NULL;
}


/**Function********************************************************************

  Synopsis           adds one object to list, on the start of the list, pushing
                     all other objects forward. Before first use call list_init()

  Parameters         data - pointer to wifi_data struct about to be stored
                     in list.
                     object_size - size of the structure, call sizeof() to
                     determine its size.

  SideEffects        always call delete_list() function before exiting program

******************************************************************************/
void push(wifi_data * object)
{
  //create a link
#ifdef DEBUG
printf("push: allocating memory\n");
#endif

  struct wifi_list *link = (struct wifi_list*) malloc(sizeof(struct wifi_list));
  link->data  = (wifi_data* ) malloc(sizeof(struct wifi_data));

  link->data->cell_ind = object->cell_ind;
  for (int i = 0; i < 6; i++)
  {
    link->data->MAC[i] = object->MAC[i];
  }

  string_copy(link->data->ESSID, object->ESSID, strlen(object->ESSID)+1);
  //link->data->ESSID[strlen(object->ESSID)] = '\0';
  //printf("%s %s %d\n",link->data->ESSID ,object->ESSID, strlen(object->ESSID));
  link->data->mode = object->mode;
  link->data->channel = object->channel;
  link->data->encrytpion_key = object->encrytpion_key;
  for (int i = 0; i < 2; i++)
  {
    link->data->quality[i] = object->quality[i];
  }

  //point it to old first node
  link->next = list_head;

  //point first to new first node
  list_head = link;
#ifdef DEBUG
printf("object pushed\n");
#endif
}
wifi_list *get_head(void)
{
  return list_head;
}


/**Function********************************************************************

  Synopsis           returns, with every execution, pointer to next element
                     from the list. At the end of list returns NULL and goes
                     back to head.

  Parameters         none

  SideEffects        cannot be used pararell with the same function (static)

  SeeAlso            example of use: (to print every channel of list)
                     while((data_read = move_head())!=NULL)
                          printf("%d\n", data_read->data->channel);

******************************************************************************/
wifi_list *move_head(void)
{
  static wifi_list *local_head = NULL;
  static wifi_list *return_head = NULL;

  if(list_head == NULL)
    return NULL;

  if(local_head == NULL)  //if it is first object or prievous one was last
  {
    local_head = list_head;
    if(return_head != NULL) //if it is not first object but previous one was last
      return NULL;
  }
  return_head = local_head;
  local_head = local_head->next;
  return return_head;
}

wifi_list *move_head_ptr(wifi_list* local_head)
{
  return local_head->next;
}


/**Function********************************************************************

  Synopsis           Frees all objects dynamicly located in linked list.
                     Has to be called before exiting the program.

  Parameters         none

******************************************************************************/
void delete_list(void)
{
  wifi_list * pointer;
  while((pointer = move_head())!=NULL)
  {
    if(pointer != NULL)
    {
      free(pointer->data);
      free(pointer);
    }
  }
}


/**Function********************************************************************

  Synopsis           Sorts the wifi_list from higest to lowest quality

  Parameters         none

  SideEffects        Mutates the wifi_list data so the list remains sorted

******************************************************************************/
void sort_list(void)
{
  wifi_list *curr_pointer;
  wifi_data *data;
  char change = 1;
  while(change)
  {
    change = 0;
    while ((curr_pointer = move_head()) != NULL)
    {
      if(curr_pointer->next != NULL)
      {
        if(curr_pointer->data->quality[0] < curr_pointer->next->data->quality[0])
          {
#ifdef DEBUG
            printf("new object sort\n");
#endif
            change = 1;
            data = curr_pointer->data;
            curr_pointer->data = curr_pointer->next->data;
            curr_pointer->next->data = data;
        }
      }
    }
  #ifdef DEBUG
    printf("next round\n");
  #endif

  }
  #ifdef DEBUG
  printf("sorted\n");
  #endif

  while ((curr_pointer = move_head()) != NULL)
  {
    display_single_access_point(curr_pointer->data);
  }
}
