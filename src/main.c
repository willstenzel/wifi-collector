#include "structure_and_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "menu.h"
#include "display_data.h"
#include "wifi_collector.h"


/**CFile***********************************************************************

  FileName    main.c

  Synopsis    Contains only the main function for our program

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
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

wifi_data data;
wifi_list *data_read;


/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/


int main(int argc, char const *argv[])
{
  data.channel = 5;
  data.quality[0] = 6;
  data.quality[1] = 70;
  push(&data, sizeof(data));
  data.channel = 6;
  data.quality[0] = 40;
  data.quality[1] = 70;
  push(&data, sizeof(data));
  data.channel = 7;
  data.quality[0] = 30;
  data.quality[1] = 70;
  push(&data, sizeof(data));
  data.channel = 10;
  data.quality[0] = 20;
  data.quality[1] = 70;
  push(&data, sizeof(data));
  while((data_read = move_head())!=NULL)
    printf("%d\n", data_read->data->channel);
  wificollector_delete_net(10);
    printf("\n");
  while((data_read = move_head())!=NULL)
    printf("%d\n", data_read->data->channel);

  display_all_access_points();
  printf("---------------------------------------\n");
  wificollector_select_best();

  // handle_menu_input();
  return 0;
}
