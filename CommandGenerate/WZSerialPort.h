 
#ifndef _WZSERIALPORT_H
#define _WZSERIALPORT_H
#include <iostream>
using namespace std;

 
class WZSerialPort
{
public:
	WZSerialPort();
	~WZSerialPort();
 
	// �򿪴���,�ɹ�����true��ʧ�ܷ���false
	// portname(������): ��Windows����"COM1""COM2"�ȣ���Linux����"/dev/ttyS1"��
	// baudrate(������): 9600��19200��38400��43000��56000��57600��115200 
	// parity(У��λ): 0Ϊ��У�飬1Ϊ��У�飬2ΪżУ�飬3Ϊ���У��
	// databit(����λ): 4-8��ͨ��Ϊ8λ
	// stopbit(ֹͣλ): 1Ϊ1λֹͣλ��2Ϊ2λֹͣλ,3Ϊ1.5λֹͣλ
	// synchronizable(ͬ�����첽): 0Ϊ�첽��1Ϊͬ��
	bool open(int portname, int baudrate=9600, char parity=0, char databit=8, char stopbit=1, char synchronizeflag=0);
 
	//�رմ��ڣ���������
	void close();
 
	//�������ݻ�д���ݣ��ɹ����ط������ݳ��ȣ�ʧ�ܷ���0
	int send(unsigned char *dat,int len);
 
	//�������ݻ�����ݣ��ɹ����ض�ȡʵ�����ݵĳ��ȣ�ʧ�ܷ���0
	unsigned char* receive();
 
private:
	int pHandle[16];
	char synchronizeflag;
};
 
#endif
