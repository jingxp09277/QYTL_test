#ifndef TTLWRAPPER_H_
#define TTLWRAPPER_H_


#ifdef __cplusplus
extern "C"
{
#endif
	int openPort(int portName,int baudrate);
	int sendMsg(unsigned char *arr,int len);
	unsigned char* recMsg();
	void closePort();
	void uartCOMGet();

#ifdef __cplusplus
}
#endif

#endif // WRAPPER_H_