#ifndef S5_MESSAGE_H
#define S5_MESSAGE_H

#include "mbed.h"
#include "traitement.h"

extern char hand_pos[10];


typedef struct message_t
{
    char message[10];
    int len;
} message_t;

char read_hand_state(char hand_state);

void send_message(Serial& serial, message_t& message);

void create_hand_message(char hand_state,char swipe, message_t& message);


#endif