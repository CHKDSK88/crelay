/******************************************************************************
 * 
 * Relay card control utility: Driver for HID API compatible relay cards
 * 
 * Description:
 *   This software is used to control the HID API compatible relay cards.
 *  This file contains the declaration of the specific functions.
 * 
 * Author:
 *   Ondrej Wisniewski (ondrej.wisniewski *at* gmail.com)
 * 
 * Last modified:
 *   07/03/2015
 *
 * Copyright 2015, Ondrej Wisniewski 
 * 
 * This file is part of crelay.
 * 
 * crelay is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with crelay.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *****************************************************************************/ 

#ifndef relay_drv_hidapi_h
#define relay_drv_hidapi_h

/**********************************************************
 * Function detect_com_port_hidapi()
 * 
 * Description: Detect the port used for communicating 
 *              with a HID API compatible relay card
 * 
 * Parameters: portname (out) - pointer to a string where
 *                              the detected com port will
 *                              be stored
 * 
 * Return:  0 - success
 *         -1 - fail, no relay card found
 *********************************************************/
int detect_com_port_hidapi(char* portname);


/**********************************************************
 * Function get_relay_hidapi()
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
int get_relay_hidapi(char* portname, uint8 relay, relay_state_t* relay_state);


/**********************************************************
 * Function set_relay_hidapi()
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
int set_relay_hidapi(char* portname, uint8 relay, relay_state_t relay_state);

#endif
