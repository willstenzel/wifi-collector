#ifndef __STRUCTURE_AND_LIST_H
#define __STRUCTURE_AND_LIST_H

typedef enum mode_vals {autos, adhoc, managed, master, repeater,
secondary, monitor, unknown}mode_vals;
enum enctryption_vals {On, Off};
typedef struct wifi_data
{
  int cell_ind;
  unsigned char MAC[6];
  char* ESSID;
  mode_vals mode;
  int channel;
  enum enctryption_vals encrytpion_key;
  unsigned char quality[2];

}wifi_data;

typedef struct wifi_list
{
  wifi_data *data;
  struct wifi_list *next;
}wifi_list;

int list_init(void);
void push(wifi_data * data, int data_size);
wifi_list * get_head(void);

#endif
