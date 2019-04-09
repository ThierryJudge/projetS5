#include "message.h"


char hand_pos[10] = {0x00, 
                    0x08, 
                    0x0A, 
                    0x1A,
                    0x0F,
                    0x1F,
                    0x0E,
                    0x0D,
                    0x0B,
                    0x07};

void create_hand_message(char hand_state, char swipe, message_t& message)
{
    message.message[0] = 0xFF;
    message.message[1] = 'a';
    message.message[2] = hand_state;
    message.message[3] = interpret_sign_number(hand_state);
    message.message[4] = swipe;
    message.message[5] = 0xFE;

    message.len = 6;

}


void send_message(Serial& serial, message_t& message)
{
    for(int i= 0; i < message.len; i++)
    {
        printf("0x%02x\r\n", message.message[i]);
        serial.putc(message.message[i]);
    }
}

char read_hand_state(char hand_state)
{
    for(int i =0; i < 10; i++)
    {
        if(hand_state == hand_pos[i])
        {
            printf("%d\r\n", i);
            printf("%c\r\n", i+0x30);
            return (char) (i + 0x30);
        }
    }

    return '0';

}