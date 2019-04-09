#include "xbeegant.h"

using namespace XBeeLib;

static Thread xbeeThread;
Mail<gant_data, 25> xbeeMail;

osThreadId mainID; 

void send_data(char *res)
{
    gant_data *data = (gant_data*)xbeeMail.alloc();
    if (data != NULL) {
    data->resultats[0] = res[0];
    data->resultats[1] = res[1];
    xbeeMail.put(data);
    }
    else
    {
        printf("Mailbox full\r\n");
    }
}

void start_xbee(osThreadId mainId)
{
    mainID = mainId;
    xbeeThread.start(xbee_th);
}

void xbee_th(void)
{
    printf("Xbee Init\r\n");
    
    XBeeZB xbee = XBeeZB(RADIO_TX, RADIO_RX, RADIO_RESET, NC, NC, 9600);
 
    RadioStatus radioStatus = xbee.init();
    MBED_ASSERT(radioStatus == Success);

    uint64_t current_panid;
    RadioStatus radioStatus2 = xbee.get_operating_panid(&current_panid);
    if (radioStatus2 != Success) {
        printf("Error reading the PAN ID\r\n");
        current_panid = 0;
    }
    printf("Current PAN ID is '%X%X', setting it to '%04X%04X'\r\n", UINT64_HI32(current_panid), UINT64_LO32(current_panid), UINT64_HI32(NEW_PANID), UINT64_LO32(NEW_PANID));
    RadioStatus radioStatus3 = xbee.set_panid(NEW_PANID);
    if (radioStatus3 != Success) {
        printf("Error when setting PAN ID\r\n");
    }

    RadioStatus radioStatus4 = xbee.get_operating_panid(&current_panid);
    if (radioStatus4 != Success) {
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
    printf("OK. Device has joined\r\n");
    osSignalSet(mainID, 0x1);

    while(1)
    {
        osEvent event = xbeeMail.get();
        if (event.status == osEventMail) {
            //Logger::getLogger().logDebug(DEBUG_APP, "Got mail");
            gant_data *data = (gant_data *)event.value.p;
            printf("%d, %d\r\n", data->resultats[0], data->resultats[1]);
            const char send_data[] = {data->resultats[0], data->resultats[1]};
            send_data_to_coordinator(xbee, send_data, 2);
            xbeeMail.free(data);
        }
        
    }
    
}


void send_broadcast_data(XBeeZB& xbee, const char *data, uint16_t data_len)
{
    
    //const uint16_t data_len = strlen(data);
 
    const TxStatus txStatus = xbee.send_data_broadcast((const uint8_t *)data, data_len);
    if (txStatus == TxStatusSuccess)
        printf("send_broadcast_data OK %d\r\n", data_len);
    else
        printf("send_broadcast_data failed with %d\r\n", (int) txStatus);
}

void send_data_to_coordinator(XBeeZB& xbee, const char *data, uint16_t data_len)
{
    //const uint16_t data_len = strlen(data);
 
    const TxStatus txStatus = xbee.send_data_to_coordinator((const uint8_t *)data, data_len);
    if (txStatus == TxStatusSuccess)
        printf("send_data_to_coordinator OK - %d\r\n", data_len);
    else
        printf("send_data_to_coordinator failed with %d\r\n", (int) txStatus);
}