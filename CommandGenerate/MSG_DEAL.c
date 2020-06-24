#include "StdAfx.h"
#include "MSG_DEAL.h"




void init_uart(uartSendFuncDef uartSendFuncPara){
	uart_data.uartSendFunc=uartSendFuncPara;
};


/**
*����Buff����
*@param arg ������Buff
*@param pos1 ������Ϣ1
*@param pos2 ������Ϣ2
*@return len  ����
**/
uint32_t getCmdLenS(unsigned char *arg,uint32_t pos1,uint32_t pos2){
	int len=0;
	if(arg!=NULL){
		len=(len|arg[pos2])<<8|arg[pos1];
	}
	//printf("tx_len:%d",len);
	return len;
}


//��ӡ������Ϣ
void printBuff(u8 *recvBuff,uint32_t len){
	uint32_t i=0;
	if(len>128){
		printf("\n err data is too  long  _128");
		return;
	}
	printf(" \n buff: ");
	for(i;i<len;i++){
		printf("%x ",recvBuff[i]);
	}
}




/**����У��� 
*@param Buff ���������
*@param len  �ܳ���
*@return  У���
*/
uint32_t checkSumGenn(u8 *Buff,uint32_t len){
	uint32_t sum=0;
	uint32_t i=4;
	for(i;i<len-3;i++){
		sum += Buff[i];
	}
	return sum;
}

//16����У���תΪint
uint32_t hexTOintSUM(u8 *Buff,uint32_t len){
	uint32_t sum=0;
	sum=Buff[len-2]<<8|Buff[len-3];
#if print_log <=2
	printf("\n sum: %d",sum);
#endif
	return sum;
}

//intУ���תΪ16����
uint32_t intTOHexSum (u8 *Buff,uint32_t len,uint32_t sum){
	
	u8 sum_high=0;
	u8 sum_low=0;
	sum_low=sum;
	sum_high=sum>>8;
	Buff[len-2]=sum_high;
	Buff[len-3]=sum_low;
	return sum;
}

//У������
uint32_t CMD_CHECK(u8 *recvBuff,uint32_t len){
	uint32_t sum1=0;
	uint32_t sum2=0;
	sum1=hexTOintSUM(recvBuff,len);
	sum2=checkSumGenn(recvBuff,len);
	if(sum1==sum2){
		return 1;
	}
	return 0;
}

//����У��ֵ
uint32_t CMD_CHECK_fill(u8 *Buff,uint32_t len){
	Buff[6]=Buff[6]++;
	intTOHexSum(Buff,len,checkSumGenn(Buff,len));
	return 1;
}


//����У��ֵ
uint32_t GET_CMD_ID(u8 *Buff,uint32_t len){
	Buff[6]=Buff[6]++;
	intTOHexSum(Buff,len,checkSumGenn(Buff,len));
	return 1;
}

//����������id ����
u8 playVoiceBuf4[]={0xA5,0XFC,0x06,0x00,0xA1,0x92,0x00,0x80,0x91,0x00,0x00,0x00,0x00,0x00,0x00,0xFB};

//������id ����
u8 playVoiceBuf[]={0xA5,0XFC,0x06,0x00,0xA1,0x92,0x00,0x80,0x92,0x00,0x00,0x00,0x00,0x00,0x00,0xFB};

//������id���� ��ӭ
u8 playVoiceBuf2[]={0xA5,0XFC,0x06,0x00,0xA1,0x92,0x00,0x80,0x92,0x11,0x27,0x00,0x00,0x00,0x00,0xFB};

//������id����  �˳�����
u8 playVoiceBuf3[]={0xA5,0XFC,0x06,0x00,0xA1,0x92,0x00,0x80,0x92,0x12,0x27,0x00,0x00,0x00,0x00,0xFB};

//����ָ��
u8 playVoiceBuf5[]={0xA5,0XFC,0x05,0x00,0xA1,0x96,0x00,0x81,0x00,0x00,0x00,0x00,0x00,0x00,0xFB};


/**
*����������������
*@param Buf ������BUF
*@param  bufsegm  ��������ID��buf
*@param  segmpos1  ����������ID��λ��
*@param  segmpos1  ����ȡ����ID��λ��
*/
void playVoiceBufGen(u8 *Buf,u8 *bufsegm,uint32_t segmpos1,uint32_t segmpos2){
	int i=0;
	for(i;i<4;i++){
		Buf[segmpos1+i]=bufsegm[segmpos2+i];
	}
}




/**
*����������ֵ����data������Ϣ ���� �����id(CMD_id)λ��
*��ȡ����getCmdLenS(recvBuff,2,3);��ȡCMD_IDgetCmdLenS(recvBuff,7,8)
*@param arg ������Buff
*@param pos1 ������Ϣλ��1
*@param pos2 ������Ϣλ��2
*@return num  ��Ӧ��ֵ
**/
uint32_t getCmdNum(unsigned char *arg,uint32_t pos1,uint32_t pos2){
	int num=0;
	if(arg!=NULL){
		num=(num|arg[pos2])<<8|arg[pos1];
	}
	return num;
}






uint32_t depth=0;
int recv_deal(u8 *recvBuff){
	int temp=-1;
	uint32_t dataLen=getCmdLenS(recvBuff,2,3);
	uint32_t  len=dataLen+10;
	depth++;
	if(recvBuff[0]!=0xA5||recvBuff[1]!=0xFC||dataLen>7||recvBuff[len-1]!=0xFB){
		printf("\n err data is too  long  _7");
		depth=0;
		return 0;
	}
#if print_log <=2
	printf("\n  %d--",sizeof(playVoiceBuf));
	printBuff(recvBuff,len);
#endif

	temp =CMD_CHECK(recvBuff,len);

#if print_log <=2
	if(temp!=1){
		printf("\ncheck sum err");
	}
	temp=-1;
#endif
	
	switch(recvBuff[4]){
	case MSG_TYPE_UP://ʶ����
		switch(recvBuff[5]){
		case 0x91:
			{
				uint32_t i=0;
				uint32_t base=5+2;
				printf("\n voice result  semanticID:");
				for(i;i<dataLen-1;i++){
					printf("%x ",recvBuff[base+i]);
				}
				printf("\n voice result  score: %d  cmd_id:%d",recvBuff[base+dataLen-1],getCmdNum(recvBuff,7,8));

				//��������������
				printf("\n ++++++++++ \n send playVoice");
				playVoiceBufGen(playVoiceBuf,recvBuff,9,base);
				CMD_CHECK_fill(playVoiceBuf,sizeof(playVoiceBuf));
				//uart_data.uartSendFunc(playVoiceBuf,sizeof(playVoiceBuf));
				#if print_log==1
					printBuff(playVoiceBuf,sizeof(playVoiceBuf));
				#endif
				
				printf("\n");
				break;
			}
		default:
			break;
		}
		break;
	case MSG_TYPE_DOWN:
		switch(recvBuff[5]){
		case 0x92:
			{
				printf("\n  Play the voice");	
				break;
			}
		default:
			break;
		}
			break;
	case MSG_reply:
		switch(recvBuff[5]){
		case 0x91:
			{
				printf("\n  ACK reply");	
				break;
			}
		case 0x92:
			{
				printf("\n  ACK reply");	
				break;
			}
		default:
			break;
		}
		break;
	case MSG_notice:
		switch(recvBuff[5]){
		case 0x9A:
			{
				uint32_t base=5+2+1;
				printf("\n Status notification: ");
				switch(recvBuff[base]){
				case 0xb0:
					printf("POWER ON ");
					CMD_CHECK_fill(playVoiceBuf2,sizeof(playVoiceBuf2));
					uart_data.uartSendFunc(playVoiceBuf2,sizeof(playVoiceBuf2));
				   	printBuff(playVoiceBuf2,sizeof(playVoiceBuf2));
					break;
				case 0xb1:
					printf("Wake up the state ");
					break;
				case 0xb2:
					printf("Exit the wake up ");
					CMD_CHECK_fill(playVoiceBuf3,sizeof(playVoiceBuf3));
				   uart_data.uartSendFunc(playVoiceBuf3,sizeof(playVoiceBuf3));
				   	printBuff(playVoiceBuf3,sizeof(playVoiceBuf3));
					break;
				case 0xb3:
					printf("play start ");
					break;
				case 0xb4:
					printf("play end ");
					break;
				default:
					break;
				}
				break;
			}
		default:
			break;
		}
		break;
	default:
		break;
	}

	printf("\n---------------------------------------------------\n");
	//ճ������
	if(recvBuff[len]==0xA5 && recvBuff[len+1]==0xFC&&depth<=3){
		//printf("\n depth=%d",depth);
		recv_deal(&recvBuff[len]);
	}
	depth=0;
	return 0;

};

