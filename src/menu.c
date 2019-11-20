#include <stdio.h>
#include "./menu.h"

#define DEBUG 1

// TODO: Just used for testing, can be removed later
int main(int argc, char const *argv[])
{
        display_menu();
        handle_input();
        return 0;
}

/**Function********************************************************************

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
        #ifdef DEBUG
        printf("[9] wificollector_collect_all\n");
        #endif
        printf("\n");
        // TODO -- double check that this is how we are suppose to recieve the input
        printf("Option: \n");

}


/**Function********************************************************************

   Synopsis           Handles User Input

   Description        Read user input from stdin and delegate to the right function

   Parameters         None

   SideEffects        Mutates or prints data based on what the user inputs

******************************************************************************/
void handle_input()
{
        int input;
        // Q: is getc the right way to read from the scanner in this case
        //    or should we should fgets or scanf?

        while ((input = getc(stdin)) != EOF)
        {
                // Remove this before submitting the project
                #ifdef DEBUG
                if (input == '9')
                {
                        // wificollector_collect_all();
                        continue;
                }
                #endif

                // if the system reads a new line char it can ignore it
                if (input == '\n') {
                        printf("Read new line\n");
                        continue;
                }

                printf("INPUT: %c\n", input);

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
                        // wificollector_quit();
                        break;
                case 2:
                        // wificollector_collect();
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
        }

        // free_all_data();
}
