#ifndef S5_XBEE_H
#define S5_XBEE_H

#include <mbed.h>
#include <rtos.h>
#include "gant.h"
#include "config.h"
#include "XBeeLib.h"

#define NEW_PANID               0x1234


extern  Mail<gant_data, 25> xbeeMail;


void xbee_th(void);

void start_xbee(osThreadId mainId);
void send_data(char *res);

void send_broadcast_data(XBeeLib::XBeeZB& xbee, const char *data, uint16_t data_len);
void send_data_to_coordinator(XBeeLib::XBeeZB& xbee, const char *data, uint16_t data_len);


#endif