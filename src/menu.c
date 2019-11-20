#include <stdio.h>
#include "./menu.h"
#include "./wifi_collector.h"

/**CFile***********************************************************************

  FileName    menu.case

  Synopsis    Displays the menu to the user and delegates to the right function

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


/**Function display_menu ******************************************************

   Synopsis           Displays the menu

   Description        Displays the menu which allows the user to interact with
                     the program

   Parameters         None

   SideEffects        None

******************************************************************************/
void display_menu()
{
        printf("[2019] SUCEM S.L. Wifi Collector\n\n");
        printf("[1] wificollector_quit\n");
        printf("[2] wificollector_collect\n");
        printf("[3] wificollector_show_data_one_network\n");
        printf("[4] wificollector_select_best\n");
        printf("[5] wificollector_delete_net\n");
        printf("[6] wificollector_sort\n");
        printf("[7] wificollector_export\n");
        printf("[8] wificollector_import\n");
        printf("\n");
        printf("Option: \n");

}




/**Function handle_menu ******************************************************

   Synopsis           Handles User Input for the menu

   Description        Read user input from stdin and delegate to the right function

   Parameters         None

   SideEffects        Mutates or prints data based on what the user inputs

******************************************************************************/
void handle_menu()
{
        int input;
        int quit = 0;

        display_menu();

        while (((input = getc(stdin)) != EOF) && (quit != 1))
        {
                // if the system reads a new line char it can ignore it
                if (input == '\n') {
                        continue;
                }

                // check that the input is a number between 1 and 8
                if (input < '1' || input > '8')
                {
                        printf("Please enter an integer input between 1-8\n");
                        continue;
                }
                // converty to char to integer
                switch (input - '0')
                {
                case 1:
                        quit = 1;  // Set quit to true to exit the while loop
                        break;
                case 2:
                        wificollector_collect();
                        break;
                case 3:
                        // wificollector_show_data_one_network();
                        break;
                case 4:
                        // wificollector_select_best();
                        break;
                case 5:
                        // wificollector_delete_net();
                        break;
                case 6:
                        // wificollector_sort();
                        break;
                case 7:
                        // wificollector_export();
                        break;
                case 8:
                        // wificollector_import();
                        break;
                default:
                        break;
                }
                display_menu();
        }

        // free_all_data();
}
