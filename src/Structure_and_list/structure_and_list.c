#include "structure_and_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"


struct wifi_list * list_head;

int list_init(void)
{
  list_head = NULL;
}

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
wifi_list * get_head(void)
{
  return list_head;
}
wifi_list *move_head(void)
{
  static wifi_list *local_head;
  if(local_head->next != NULL)
}
/*int remove_by_index(node_t ** head, int n)
{
  int i = 0;
  int retval = -1;
  node_t * current = *head;
  node_t * temp_node = NULL;

  if (n == 0)
  {
      return pop(head);
  }

  for (i = 0; i < n-1; i++)
  {
      if (current->next == NULL)
      {
          return -1;
      }
      current = current->next;
  }

  temp_node = current->next;
  retval = temp_node->val;
  current->next = temp_node->next;
  free(temp_node);

  return retval;

}*/

// int main(int argc, char const *argv[])
// {
//   /* code */
//   struct wifi_data sth;
//   sth.mode = adhoc;
//   printf("%s",sth.mode);
//   return 0;
// }
