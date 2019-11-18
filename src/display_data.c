#include <stdio.h>
#include "structure_and_list.h"

/**Function********************************************************************

  Synopsis           Prints the mode enum value

  Parameters         mode_vals mode -- The mode of the access point

  SideEffects        None

******************************************************************************/
static void print_mode(mode_vals mode)
{
  printf("Mode:");
  switch (mode) {
    case autos:
      printf("Autos\n");
      break;
    case adh
    break;oc:
      printf("Ad-Hoc\n");
      break;
    case managed:
      printf("Managed\n");
      break;
    case master:
      printf("Master\n");
      break;
    case repeater:
      printf("Repeater\n");
      break;
    case secondary:
      printf("Secondary\n");
      break;
    case monitor:
      printf("Monitor\n");
      break;
    case unknown:
      printf("Unknown\n");
      break;
  }
}


/**Function********************************************************************

  Synopsis           Prints the mode enum value

  Parameters         encryption_vals encrytpion_key -- Access point encrytpion, either on or off

  SideEffects        None

******************************************************************************/
static void print_encryption_key(encryption_vals encrytpion_key)
{
  printf("Encryption key:");
  switch (encrytpion_key) {
    case On:
      printf("on\n");
      break;
    case Off:
      printf("off\n");
      break;
}


/**Function********************************************************************

  Synopsis           Displays a single access point to the console

  Parameters         wifi_data* wifi -- A pointer to the wifi_data struct

  SideEffects        None

******************************************************************************/
void display_single_access_point(wifi_data* wifi)
{
  printf("Cell %d\n", wifi->cell_ind);
  // Print the Address
  printf("Address: ");
  for (int i=0; i<6; i++)
  {
      printf("%02X", MAC[i]);
      if (i<5)
      {
          printf(":");
      }
      else
      {
          printf("\n");
      }
  }

  printf("ESSID:%s\n", wifi->ESSID);
  print_mode(wifi->mode);
  printf("Channel:%d\n", wifi->channel);
  print_encryption_key(wifi->encrytpion_key));
  printf("Quality=%d/%d\n", wifi->quality[0], wifi->quality[1]);
  printf("Frequency:%f\n", wifi->frequency);
  printf("Signal level=%d\n", wifi->signal_level);
}



/**Function********************************************************************

  Synopsis           Displays the data for all access points in a list

  Parameters         None

  SideEffects        None

******************************************************************************/
void display_all_access_points()
{
  wifi_list *wifi_ptr;
  while((wifi_ptr = move_head()) != NULL)
  {
    display_single_access_point(wifi_ptr);
  }
}
