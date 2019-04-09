/**
 * Copyright (c) 2015 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */

#include "mbed.h"
#include "XBeeLib.h"
#include "message.h"
#include "traitement.h"



using namespace XBeeLib;

Serial serial(p28, p27, 115200);


// /** Callback function, invoked at packet reception */
static void receive_cb(const RemoteXBeeZB& remote, bool broadcast, const uint8_t *const data, uint16_t len)
{
    const uint64_t remote_addr64 = remote.get_addr64();

    //printf("\r\nGot a %s RX packet [%08x:%08x|%04x], len %d\r\nData: ", broadcast ? "BROADCAST" : "UNICAST", UINT64_HI32(remote_addr64), UINT64_LO32(remote_addr64), remote.get_addr16(), len);
    printf("Got Packet - %d\r\n", len);
    for (int i = 0; i < len; i++)
        printf("%02x ", data[i]);
    printf("\r\n");

    printf("Chiffre lu: %d\r\n", interpret_number(data[0]));
	printf("Signe lu: %d\r\n\n", interpret_sign_number(data[0]));
    if(data[1] == 1){
        printf("--------------------------------Swipe Left\r\n");
    }
    else if(data[1] == 3){
        printf("--------------------------------Swipe Right\r\n");
    }

	message_t message;
	create_hand_message(data[0], data[1], message);
	send_message(serial, message);
}
	


int main()
{
    printf("Sample application to demo how to receive unicast and broadcast data with the XBeeZB\r\n\r\n");

    XBeeZB xbee = XBeeZB(RADIO_TX, RADIO_RX, RADIO_RESET, NC, NC, 9600);

    /* Register callbacks */
    xbee.register_receive_cb(&receive_cb);

    RadioStatus const radioStatus = xbee.init();
    MBED_ASSERT(radioStatus == Success);

    uint64_t current_panid;
    RadioStatus radioStatus2 = xbee.get_operating_panid(&current_panid);
    if (radioStatus2 != Success) {
        printf("Error reading the PAN ID\r\n");
        current_panid = 0;
    }
    printf("Current PAN ID is '%X%X'\r\n", UINT64_HI32(current_panid), UINT64_LO32(current_panid));

    /* Wait until the device has joined the network */
    printf("Waiting for device to join the network: ");
    while (!xbee.is_joined()) {
        wait_ms(1000);
        printf(".");
    }
    printf("OK\r\n");

    while (true) {
        xbee.process_rx_frames();
        wait_ms(100);
        printf(".");
    }
}
/*
int main()
{
    Serial serial(p9, p10, 115200);
    DigitalOut led(LED1);
    while(1)
    {
        message_t message;
        char hand_state = 0x1F;
        create_hand_message(hand_state, message);
        send_message(serial, message);
        wait(0.1);
        led = !led;

    }
}
*/

// DigitalOut reset(p8);
// Serial xbee(p13, p14);
// Serial pc(USBTX, USBRX);
// int 
// main() {
// 	//printf("Hello world55!!!!\r\n");
	
// 	reset = 0; 

// 	wait(0.4);
	
// 	reset = 1; 
	
// 	wait(0.4);
	
// 	//set_pan_id(0);
	
	
// 	while(1) {
// 		if (xbee.readable() && pc.writeable()){
// 			pc.putc(xbee.getc());
// 		}
// 		if (pc.readable() && xbee.writeable()){
// 			xbee.putc(pc.getc());
// 		}
// 	}
// }
