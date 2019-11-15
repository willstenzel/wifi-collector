#include "structure_and_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"


struct wifi_list * list_head;

int list_init(void)
{
  list_head = NULL;
}

/**Function********************************************************************

  Synopsis           adds one object to list, on the start of the list, pushing
                     all other objects forward. Before first use call list_init()

  Parameters         data - pointer to wifi_data struct about to be stored
                     in list.
                     data_size - size of the structure, call sizeof() to
                     determine its size.

  SideEffects        always call delete_list() function before exiting program

******************************************************************************/
void push(wifi_data * data, int data_size)
{
  //create a link
  struct wifi_list *link = (struct wifi_list*) malloc(sizeof(struct wifi_list));
  link->data  = malloc(data_size);
  //copy data to the list
  memcpy(link->data, data, data_size);

  //point it to old first node
  link->next = list_head;

  //point first to new first node
  list_head = link;
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

void delete_list(void)
{
  wifi_list * pointer;
  while((pointer = move_head())!=NULL)
    free(pointer);
}
void wificollector_delete_net(int channel)  //by channel, todo by ESSID
{
  wifi_list *current, *previous = list_head;

  while((current = move_head()) != NULL)
  {
    if(current->data->channel == channel)   //if it is the one
    {
      if(current == list_head)              //if it is first element
        list_head = current->next;
      else
        previous->next = current->next;
      free(current);
    }
    previous = current;
  }
}
