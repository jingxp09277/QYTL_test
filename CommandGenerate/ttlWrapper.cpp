#include "StdAfx.h"
#include "ttlWrapper.h"

#include<iostream>
#include<string>
#include<cstring> 
#include<cstdio>
#include "UARTLIST.h"

#include "WZSerialPort.h"


using namespace std;
 

WZSerialPort wzSerialPort;


int openPort(int portName,int baudrate){
	return	wzSerialPort.open(portName,baudrate, 0, 8, 1, 0);
}

int sendMsg(unsigned char *arr,int len){
	return wzSerialPort.send(arr,len);
}


unsigned char* recMsg(){
	 
	 return wzSerialPort.receive();

}

void closePort(){
	wzSerialPort.close();
}

void uartCOMGet(){
	UARTLIST comlist;
	comlist.enumPort();
}


