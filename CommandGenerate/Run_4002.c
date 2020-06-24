#include "StdAfx.h"
#include "UpCMD.h"
#include "DownCMD.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include  "ttlWrapper.h"

#include <windows.h>
#include "mod.h"

#define cmdPos 8   //������λ��
int light=0;

extern int now_cmd=-1;

//��������
//unsigned char testData[128]={0x58,0x46,0x23,0x00,0x06,0x39,0xFF,0x00,0x10,0x01,0xE7,0x05,0x64,0x61,0x33,0x20,0x6B,0x61,0x69,0x31,0x20,0x64,0x65,0x6E,0x67,0x31,0x20,0x67,0x75,0x61,0x6E,0x67,0x31,0x00,0x34};

struct audioLis{
int rank;
char name[50];
unsigned char order;
int time;
};
#if mode == 1
struct audioLis al[11]={{0,"���С��",0,0},
{1,"�򿪿յ�",4,0},
{2,"�رտյ�",42,0},
{3,"27��",27,0},
{4,"ʮ����",13,0},
{5,"�����¶�",51,0},
{6,"�����¶�",55,0},
{7,"�ͷ�ģʽ",57,0},
{8,"����ģʽ",69,0},
{9,"����ģʽ",70,0},
{10,"�Զ�ģʽ",82,0},
};
#else
struct audioLis al[11]={{0,"С��С��",0,0},
{1,"�򿪿յ�",4,0},
{2,"�رտյ�",42,0},
{3,"27��",27,0},
{4,"ʮ����",13,0},
{5,"�����¶�",51,0},
{6,"�����¶�",55,0},
{7,"�ͷ�ģʽ",57,0},
{8,"����ģʽ",69,0},
{9,"����ģʽ",70,0},
{10,"�Զ�ģʽ",82,0},
};
#endif


char* printTime(){
SYSTEMTIME sys; 
char time[256]={0};
GetLocalTime( &sys ); 
printf( "%4d/%02d/%02d %02d:%02d:%02d.%03d ����%1d\n\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds,sys.wDayOfWeek); 
sprintf(time,"%4d/%02d/%02d %02d:%02d:%02d.%03d ����%1d\n\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds,sys.wDayOfWeek); 
return time;
}



void print_list(){
	FILE* fp = NULL; // �ļ�ָ��
	int i=0;
	char txt_out[1024]={0};
	errno_t eResult;

	sprintf(txt_out,"%s",printTime());
	sprintf(txt_out+strlen(txt_out),"%s","=========================================\n");
	sprintf(txt_out+strlen(txt_out),"%s","| ������� |  ����� | ʶ���� |\n");

	printf("=========================================\n");
	printf("| ������� |  ����� | ʶ���� |\n");

	for(i=0;i<sizeof(al)/sizeof(al[0]);i++){
	sprintf(txt_out+strlen(txt_out),"%s","|----------+---------+--------+\n");
	printf("|----------+---------+--------+\n");

	sprintf(txt_out+strlen(txt_out),"|    %hhu  |    %s   |    %d  |\n",al[i].order,al[i].name,al[i].time);
	printf("|    %hhu  |    %s   |    %d  |\n",al[i].order,al[i].name,al[i].time);
	}

	sprintf(txt_out+strlen(txt_out),"%s","=========================================\n");
	printf("=========================================\n");


	
 
	// �Ը��ӷ�ʽ�򿪿ɶ�/д���ļ�, ���û�д��ļ������д�����Ȼ���Ը��ӷ�ʽ�򿪿ɶ�/д���ļ�
	eResult = fopen_s(&fp, "recognize.txt", "a+");
 
	// ���ļ�ʧ��
	if (eResult != 0)
		exit(-1);
 
	// ��׷������д���ļ�ָ�뵱ǰ��λ��
	fputs(txt_out, fp);
 
	// ���Ҫ����,�رմ򿪵��ļ�~~~
	fclose(fp);




}



void writTime(){

}






int setLight(int num,int flag){
	if(flag==0){
		light=num;
	}else if(flag==1){
		light+=num;	
	}else{
		light-=num;	
	}

	if(light<0){
		light=0;
	}
	if(light>1000){
		light=100;
	}
	return light;
}



unsigned char* wakeUpMode(int i){
	unsigned char* buf=NULL;
	//printf("����ָ�� :");
	switch(i){
		case 1:
			printf("���ֽ���ģʽ\n");
			buf=generateCommand(3, 0, 0x11, 0x01, MBL_param(3,1,1), 0xFF); //����ָ��  ���ŵ�һ������   ���ֽ����м䷽����Ƶѭ��ʶ��  ��ʱ255s
			sendMsg(buf,getCmdLen(buf));
			break;
		case 2:
				//printf("ASR\n");
				buf=generateCommand(3, 0, 0x11, 0x00, MBL_param(1,1,0), 0x14); //����ָ��  ���ŵ�һ������   ASR�м䷽����Ƶѭ��ʶ��  ��ʱ20s
				sendMsg(buf,getCmdLen(buf));
			break;
		case 3:
				//printf("�����������\n");
				buf=generateCommand(3, 0, 0x01,0x00,0xaa,0x0a ); //��������С
				sendMsg(buf,getCmdLen(buf));
		break;
		case 4:
				////printf("ASR\n");
				//buf=generateCommand(3, 0, 0x11, 0x00, MBL_param(1,1,0), 0x14); //����ָ��  ���ŵ�һ������   ASR�м䷽����Ƶѭ��ʶ��  ��ʱ20s
				//sendMsg(buf,getCmdLen(buf));
		break;
		case 5:
				////printf("ASR\n");
				//buf=generateCommand(3, 0, 0x11, 0x00, MBL_param(1,1,0), 0x14); //����ָ��  ���ŵ�һ������   ASR�м䷽����Ƶѭ��ʶ��  ��ʱ20s
				//sendMsg(buf,getCmdLen(buf));
		break;
		default:
				//printf("ASR\n");
				buf=generateCommand(3, 0, 0x11, 0x00, MBL_param(1,1,1), 0x14); //����ָ��  ���ŵ�һ������   ASR�м䷽����Ƶѭ��ʶ��  ��ʱ20s
				sendMsg(buf,getCmdLen(buf));
			break;
	}

	return buf;

};

	
int upCmdParsing(unsigned char *arg){
	unsigned int allLen=getCmdLen(arg);
	unsigned char *arr=NULL; //����ʶ���ı�
	unsigned char *playOrder=NULL;
	unsigned char  playNum=0; 
	int i=0;
	if(upCmdCheck(arg,allLen)==0){
		printf("�������\n");
		return 0;
	}
	switch(arg[cmdPos]){
	case 0x01: //ͨ��״̬����������ϵͳ��ʼ���ɹ�������֡�Ƿ���Ч
		{
			switch(arg[cmdPos+1]){
			case 0x00: // ��ʼ���ɹ�  
					 printf("��ʼ���ɹ�\n");
					 wakeUpMode(1);
				break; 
			case 0x10: //  �յ���ȷ����֡
					//printf("�յ���ȷ����֡\n");
				break; 
			case 0x11: //  �յ���������֡
					printf("�յ���������֡\n");
				break;
			case 0x12: //  ��������
					printf("��������\n");
				break;
			case 0x13: //   �յ���ȷ�������ϳ�������ز�֧�ִ˹���
					printf("��֧�ִ˹���\n");
				break;
			default:
				break;
			}
		}
		break;
	case 0x02: //�����̼��汾��Ϣ
			if(allLen<14){
				return 0;
			}
		//printf("%d.%d.%d.%d",arg[cmdPos+1],arg[cmdPos+2],arg[cmdPos+3],arg[cmdPos+4]+1000);
		break;
	case 0x03: //������ǰ����״̬
		{
			switch(arg[cmdPos+1]){
			case 0x00: // ���к;���״̬
					printf("���к;���״̬\n");
				break; 
			case 0x10: // ����ʶ��״̬
					printf(" ����ʶ��״̬\n");
				break; 
			case 0x11: //  ��������״̬
				 	printf(" ��������״̬\n");
				break;
			case 0x12: //  �����ϳ�״̬
					printf(" �����ϳ�״̬\n");
				break;
			case 0x13: //   ϵͳ���ߣ��͹��ģ�״̬
					printf(" ϵͳ���ߣ��͹��ģ�״̬\n");
				break;
			default:
					printf(" ��Ч״̬\n");
				break;
			}
		}
		break;
	case 0x10: //��������ʶ����
		{
			//printf("+++++++++++++++++\n+++++++++++++++++\n");
			if(allLen<14){
				return 0;
			}
			//printf("score:%d  ", getNum(arg[cmdPos+2],arg[cmdPos+3]));
			arr = (unsigned char *)malloc(sizeof(unsigned char)*(allLen-cmdPos-4));
			memcpy(arr,&arg[cmdPos+4],allLen-cmdPos-4-1);
			arr[allLen-cmdPos-5]='\0';
			//printf("text:%s\n",arr);
			free(arr);

		}
			//printf("++++++++++++++++++\n+++++++++++++++++\n");
			playNum=arg[cmdPos+1];
			for(i=0;i<sizeof(al)/sizeof(al[0]);i++){
				if(al[i].order==playNum){
					al[i].time++;
					//system("cls");
					print_list();
					now_cmd=playNum;
					break;
				}
			}
			//printf("��˵���ǵ� %d ��ָ�� ������ǣ�%s  ������%d\n",playNum,al[i].name,al[i].time);
			switch(playNum){
			case 0:
				playNum+=0x01;
				break;
			case 1:
				playNum+=0x01;
				setLight(50,0);
				break;
			case 2:
				if(setLight(10,1)>=100){
					playNum+=0x02;
				}else{
					playNum+=0x01;
				}
				break;
			case 3:
				if(setLight(10,2)<=10){
					playNum+=0x03;
				}else{
					playNum+=0x02;
				}
				break;

			case 4:
				setLight(0,0);
				playNum+=0x03;
				break;
			default:
				break;
			}
			//if(playNum>0x02)
			//	playNum=0x02;
			//playOrder=generateCommand(4, 0, 0x12, playNum, 0x00, 0x00, 0x00);  //��x������ָ��
			//sendMsg(playOrder,getCmdLen(playOrder));
		break;
	case 0x11: //ʶ��ʱ״̬����
		if(arg[cmdPos+1]==0x01){   //��ʱ
			printf("ʶ��ʱ\n");
			//playOrder=generateCommand(3, 0, 0x11, 0x00, MBL_param(2,1,1), 0x14); //����ָ��  ���ŵ�һ������   ASR�м䷽����Ƶѭ��ʶ��  ��ʱ20s
			//sendMsg(playOrder,getCmdLen(playOrder));
		}
	    if(arg[cmdPos+1]==0x10){   //�������
			printf("�������\n");
		}
		break;
	case 0x20: //������������
		//wakeUpMode(2);
		printf("++++++++++++++++++++++++��������+++++++++++++++++++++++++");
		break;
	case 0x30: //�ϳɽ�������
		printf("�ϳɽ���\n");
		break;
	default:
		break;
	}

	//printf("\n_________________________________________________________\n");
return 1;
}


/*
void main(){
	 generateCommand(3, 0, 0x11, 0x01, MBL_param(3,1,1), 0x14); //����ָ��  ���ŵ�һ������   ���ֽ����м䷽����Ƶѭ��ʶ��  ��ʱ20s

	 ////printf("score:%d  ",getNum(arg[cmdPos+2],arg[cmdPos+3]));
	//upCmdParsing(testData);
	while(1);
}*/