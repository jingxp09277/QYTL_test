#pragma once
#ifndef _MSGDEAL_H
#define _MSGDEAL_H

#define print_log 1;

typedef unsigned char  u8;
typedef unsigned int uint32_t;

#define MSG_TYPE_UP 0xA0   //order   recognize the result
#define MSG_TYPE_DOWN 0xA1   //order  playVoice
#define MSG_reply 0xA2   //Error response
#define MSG_notice 0xA3   //Notification of state change of voice module




typedef int (*uartSendFuncDef)(u8 *buffer,int lenth);
typedef int (*uartRecvFuncDef)(u8 *buffer,int lenth);


typedef struct data_types {
	uartSendFuncDef uartSendFunc;
	//uartRecvFuncDef uartRecvFunc;
	unsigned cmdBuffer[128];
	unsigned char *coomandArr;
}data_type;


data_type uart_data;
void init_uart(uartSendFuncDef uartSendFuncPara);
int recv_deal(u8 *recvBuff);

#endif