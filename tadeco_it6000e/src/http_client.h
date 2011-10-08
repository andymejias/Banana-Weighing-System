/*
 * http_client.h
 *
 *  Created on: Sep 27, 2011
 *      Author: ferd
 */

#ifndef HTTP_CLIENT_H_
#define HTTP_CLIENT_H_

// reserved ports
#define PORT_ETH0 0
#define PORT_SIM1 1
#define PORT_SIM2 2
#define PORT_SIM3 3
#define PORT_SIM4 4
#define PORT_SIM5 5
#define PORT_SIM6 6
#define PORT_FIELDBUS 7

#define PORT_MIN 8
#define PORT_MAX 31

// ports reserved for internal communication
#define PORT_INTERNAL_6000 6000
#define PORT_INTERNAL_2100 2100

#define PORT_OPT_SUCCESS 0

#define HTTP_CLIENT_SUCCESS 0;
#define HTTP_CLIENT_ERR_OPEN 1;
#define HTTP_CLIENT_ERR_BAD_IP 2;

#endif /* HTTP_CLIENT_H_ */
