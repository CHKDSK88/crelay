/******************************************************************************
 * 
 * Relay card control utility: Driver for XYZ relay card
 *   http:...
 * 
 * Description:
 * 
 * Author:
 *
 * Build instructions:
 *   gcc -c relay_drv_sample.c
 * 
 * Last modified:
 *   
 *
 *****************************************************************************/ 

/******************************************************************************
 * Communication protocol description
 * ==================================
 * 
 * < Describe here how the communication between the host and the card
 *   works, how the relay states are read and how the relays are set >
 * 
 *****************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_types.h"
#include "relay_drv.h"


/**********************************************************
 * Function detect_com_port_sample()
 * 
 * Description: Detect the port used for communicating 
 *              with the sample relay card
 * 
 * Parameters: portname (out) - pointer to a string where
 *                              the detected com port will
 *                              be stored
 * 
 * Return:  0 - success
 *         -1 - fail, no relay card found
 *********************************************************/
int detect_com_port_sample(char* portname)
{
   return 0;
}


/**********************************************************
 * Function get_relay_sample()
 * 
 * Description: Get the current relay state
 * 
 * Parameters: portname (in)     - communication port
 *             relay (in)        - relay number
 *             relay_state (out) - current relay state
 * 
 * Return:   0 - success
 *          -1 - fail
 *********************************************************/
int get_relay_sample(char* portname, uint8 relay, relay_state_t* relay_state)
{
   return 0;
}


/**********************************************************
 * Function set_relay_sample()
 * 
 * Description: Set new relay state
 * 
 * Parameters: portname (in)     - communication port
 *             relay (in)        - relay number
 *             relay_state (in)  - current relay state
 * 
 * Return:   o - success
 *          -1 - fail
 *********************************************************/
int set_relay_sample(char* portname, uint8 relay, relay_state_t relay_state)
{ 
   return 0;
}
 
