#include <stdio.h>
#include "./menu.h"

int main(int argc, char const *argv[])
{
        display_menu();
        handle_input();
        return 0;
}

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
        // if system = debug then add wifi collect all
        // printf("[9] wificollector_collect_all\n");
        printf("\n");
        // TODO -- double check that this is how we are suppose to recieve the input
        printf("Option: (Enter 1-8 followed by CRTL-D or CRTL-D to quit) \n");

}

void handle_input()
{
        int input;
        while ((input = getc(stdin)) != EOF)
        {
                // Q: is getc the right way to read from the scanner in this case
                //    or should we should fgets or scanf?

                printf("INPUT: %c\n", input);

                // check that the input is a number
                if (input < '1' || input > '8')
                {
                        printf("PLEASE ENTER AN INTEGER INPUT BETWEEN 1-8\n");
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
}
