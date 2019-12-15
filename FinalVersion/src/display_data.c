#include <stdio.h>
#include "structure_and_list.h"

/**CFile***********************************************************************

  FileName    display_data.c

  Synopsis    Displays the wifi data to to the user

  Description Either shows a single cell's info or all info from the cells

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
static void print_mode(mode_vals mode);
static void print_encryption_key(encryption_vals encrytpion_key);


/**Function print_mode ********************************************************

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
    case adhoc:
    break;
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


/**Function print_encryption_key *********************************************

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
}


/**Function display_single_access_point ***************************************

  Synopsis           Displays a single access point to the console

  Parameters         wifi_data* wifi -- A pointer to the wifi_data struct

  SideEffects        None

******************************************************************************/
void display_single_access_point(wifi_data* wifi)
{
  if(wifi != NULL)
  {
    printf("Cell %d\n", wifi->cell_ind);
    // Print the Address
    printf("Address: ");
    for (int i=0; i<6; i++)
    {
        printf("%02X", wifi->MAC[i]);
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
    print_encryption_key(wifi->encrytpion_key);
    printf("Quality=%d/%d\n", wifi->quality[0], wifi->quality[1]);
  }
}



/**Function display_all_access_points *****************************************

  Synopsis           Displays the data for all access points in a list

  Parameters         None

  SideEffects        None

******************************************************************************/
void display_all_access_points()
{
  wifi_list *wifi_ptr;
  while((wifi_ptr = move_head()) != NULL)
  {
    display_single_access_point(wifi_ptr->data);
  }
}
