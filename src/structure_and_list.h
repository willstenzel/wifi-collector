#ifndef __STRUCTURE_AND_LIST_H
#define __STRUCTURE_AND_LIST_H

/**CHeaderFile*****************************************************************

  FileName    structure_and_list.h

  Synopsis    Contains the data types needed to store a single acess point
              or a list of access points

  Copyright   [Copyright (c) 2012 Carlos III University of Madrid
  All rights reserved.

  Permission is hereby granted, without written agreement and without license
  or royalty fees, to use, copy, modify, and distribute this software and its
  documentation for any purpose, provided that the above copyright notice and
  the following two paragraphs appear in all copies of this software.

  IN NO EVENT SHALL THE CARLOS III UNIVERSITY OF MADRID BE LIABLE TO ANY PARTY
  FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING
  OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF CARLOS III
  UNIVERSITY OF MADRID HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  CARLOS III UNIVERSITY OF MADRID SPECIFICALLY DISCLAIMS ANY WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
  "AS IS" BASIS, AND CARLOS III UNIVERSITY OF MADRID HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.]

******************************************************************************/

/*---------------------------------------------------------------------------*/
/* Constant declarations                                                     */
/*---------------------------------------------------------------------------*/

//#define DEBUG
#define MAX_ESSID_LENGTH 40
#define MAX_FILE_NAME 50

/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/**Enum************************************************************************

  Synopsis    Represents the different possible wifi modes for an access point

******************************************************************************/
typedef enum mode_vals {autos, adhoc, managed, master, repeater,
secondary, monitor, unknown}mode_vals;

/**Enum************************************************************************

  Synopsis    Represents wether or not the encrytpion is On or Off

******************************************************************************/
typedef enum encryption_vals {On, Off}encryption_vals;


/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

/**Struct**********************************************************************

  Synopsis    Stores all data neccessary for a wifi single access point

******************************************************************************/
typedef struct wifi_data
{
  int cell_ind;
  unsigned char MAC[6];
  char ESSID[MAX_ESSID_LENGTH];
  mode_vals mode;
  int channel;
  encryption_vals encrytpion_key;
  unsigned char quality[2];

}wifi_data;


/**Struct**********************************************************************

  Synopsis    Stores a list of wifi access points by storing the pointer to the
              next access point in the list

******************************************************************************/
typedef struct wifi_list
{
  wifi_data *data;
  struct wifi_list *next;
}wifi_list;


/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

struct wifi_list * list_head;


/*---------------------------------------------------------------------------*/
/* Function prototypes                                                       */
/*---------------------------------------------------------------------------*/

void list_init(void);
void push(wifi_data * object);
wifi_list * get_head(void);
wifi_list * move_head(void);
void sort_list(void);
void delete_list(void);

#endif
