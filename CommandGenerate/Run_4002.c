#include "StdAfx.h"
#include "UpCMD.h"
#include "DownCMD.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include  "ttlWrapper.h"

#include <windows.h>
#include "mod.h"

#define cmdPos 8   //命令字位置
int light=0;

extern int now_cmd=-1;

//测试数组
//unsigned char testData[128]={0x58,0x46,0x23,0x00,0x06,0x39,0xFF,0x00,0x10,0x01,0xE7,0x05,0x64,0x61,0x33,0x20,0x6B,0x61,0x69,0x31,0x20,0x64,0x65,0x6E,0x67,0x31,0x20,0x67,0x75,0x61,0x6E,0x67,0x31,0x00,0x34};

struct audioLis{
int rank;
char name[50];
unsigned char order;
int time;
};
#if mode == 1
struct audioLis al[11]={{0,"你好小奥",0,0},
{1,"打开空调",4,0},
{2,"关闭空调",42,0},
{3,"27度",27,0},
{4,"十六度",13,0},
{5,"降低温度",51,0},
{6,"升高温度",55,0},
{7,"送风模式",57,0},
{8,"制冷模式",69,0},
{9,"制热模式",70,0},
{10,"自动模式",82,0},
};
#else
struct audioLis al[11]={{0,"小飞小飞",0,0},
{1,"打开空调",4,0},
{2,"关闭空调",42,0},
{3,"27度",27,0},
{4,"十六度",13,0},
{5,"降低温度",51,0},
{6,"升高温度",55,0},
{7,"送风模式",57,0},
{8,"制冷模式",69,0},
{9,"制热模式",70,0},
{10,"自动模式",82,0},
};
#endif


char* printTime(){
SYSTEMTIME sys; 
char time[256]={0};
GetLocalTime( &sys ); 
printf( "%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d\n\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds,sys.wDayOfWeek); 
sprintf(time,"%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d\n\n",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds,sys.wDayOfWeek); 
return time;
}



void print_list(){
	FILE* fp = NULL; // 文件指针
	int i=0;
	char txt_out[1024]={0};
	errno_t eResult;

	sprintf(txt_out,"%s",printTime());
	sprintf(txt_out+strlen(txt_out),"%s","=========================================\n");
	sprintf(txt_out+strlen(txt_out),"%s","| 命令序号 |  命令词 | 识别数 |\n");

	printf("=========================================\n");
	printf("| 命令序号 |  命令词 | 识别数 |\n");

	for(i=0;i<sizeof(al)/sizeof(al[0]);i++){
	sprintf(txt_out+strlen(txt_out),"%s","|----------+---------+--------+\n");
	printf("|----------+---------+--------+\n");

	sprintf(txt_out+strlen(txt_out),"|    %hhu  |    %s   |    %d  |\n",al[i].order,al[i].name,al[i].time);
	printf("|    %hhu  |    %s   |    %d  |\n",al[i].order,al[i].name,al[i].time);
	}

	sprintf(txt_out+strlen(txt_out),"%s","=========================================\n");
	printf("=========================================\n");


	
 
	// 以附加方式打开可读/写的文件, 如果没有此文件则会进行创建，然后以附加方式打开可读/写的文件
	eResult = fopen_s(&fp, "recognize.txt", "a+");
 
	// 打开文件失败
	if (eResult != 0)
		exit(-1);
 
	// 将追加内容写入文件指针当前的位置
	fputs(txt_out, fp);
 
	// 最后不要忘了,关闭打开的文件~~~
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
	//printf("唤醒指令 :");
	switch(i){
		case 1:
			printf("多轮交互模式\n");
			buf=generateCommand(3, 0, 0x11, 0x01, MBL_param(3,1,1), 0xFF); //唤醒指令  播放第一条语言   多轮交互中间方向音频循环识别  超时255s
			sendMsg(buf,getCmdLen(buf));
			break;
		case 2:
				//printf("ASR\n");
				buf=generateCommand(3, 0, 0x11, 0x00, MBL_param(1,1,0), 0x14); //唤醒指令  播放第一条语言   ASR中间方向音频循环识别  超时20s
				sendMsg(buf,getCmdLen(buf));
			break;
		case 3:
				//printf("音量调到最大\n");
				buf=generateCommand(3, 0, 0x01,0x00,0xaa,0x0a ); //音量调最小
				sendMsg(buf,getCmdLen(buf));
		break;
		case 4:
				////printf("ASR\n");
				//buf=generateCommand(3, 0, 0x11, 0x00, MBL_param(1,1,0), 0x14); //唤醒指令  播放第一条语言   ASR中间方向音频循环识别  超时20s
				//sendMsg(buf,getCmdLen(buf));
		break;
		case 5:
				////printf("ASR\n");
				//buf=generateCommand(3, 0, 0x11, 0x00, MBL_param(1,1,0), 0x14); //唤醒指令  播放第一条语言   ASR中间方向音频循环识别  超时20s
				//sendMsg(buf,getCmdLen(buf));
		break;
		default:
				//printf("ASR\n");
				buf=generateCommand(3, 0, 0x11, 0x00, MBL_param(1,1,1), 0x14); //唤醒指令  播放第一条语言   ASR中间方向音频循环识别  超时20s
				sendMsg(buf,getCmdLen(buf));
			break;
	}

	return buf;

};

	
int upCmdParsing(unsigned char *arg){
	unsigned int allLen=getCmdLen(arg);
	unsigned char *arr=NULL; //保存识别文本
	unsigned char *playOrder=NULL;
	unsigned char  playNum=0; 
	int i=0;
	if(upCmdCheck(arg,allLen)==0){
		printf("检验出错\n");
		return 0;
	}
	switch(arg[cmdPos]){
	case 0x01: //通信状态反馈，包括系统初始化成功，命令帧是否有效
		{
			switch(arg[cmdPos+1]){
			case 0x00: // 初始化成功  
					 printf("初始化成功\n");
					 wakeUpMode(1);
				break; 
			case 0x10: //  收到正确命令帧
					//printf("收到正确命令帧\n");
				break; 
			case 0x11: //  收到错误命令帧
					printf("收到错误命令帧\n");
				break;
			case 0x12: //  参数错误
					printf("参数错误\n");
				break;
			case 0x13: //   收到正确的启动合成命令，返回不支持此功能
					printf("不支持此功能\n");
				break;
			default:
				break;
			}
		}
		break;
	case 0x02: //反馈固件版本信息
			if(allLen<14){
				return 0;
			}
		//printf("%d.%d.%d.%d",arg[cmdPos+1],arg[cmdPos+2],arg[cmdPos+3],arg[cmdPos+4]+1000);
		break;
	case 0x03: //反馈当前运行状态
		{
			switch(arg[cmdPos+1]){
			case 0x00: // 空闲和就绪状态
					printf("空闲和就绪状态\n");
				break; 
			case 0x10: // 语音识别状态
					printf(" 语音识别状态\n");
				break; 
			case 0x11: //  语音播放状态
				 	printf(" 语音播放状态\n");
				break;
			case 0x12: //  语音合成状态
					printf(" 语音合成状态\n");
				break;
			case 0x13: //   系统休眠（低功耗）状态
					printf(" 系统休眠（低功耗）状态\n");
				break;
			default:
					printf(" 无效状态\n");
				break;
			}
		}
		break;
	case 0x10: //反馈正常识别结果
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
			//printf("你说的是第 %d 条指令 命令词是：%s  次数：%d\n",playNum,al[i].name,al[i].time);
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
			//playOrder=generateCommand(4, 0, 0x12, playNum, 0x00, 0x00, 0x00);  //第x条播放指令
			//sendMsg(playOrder,getCmdLen(playOrder));
		break;
	case 0x11: //识别超时状态反馈
		if(arg[cmdPos+1]==0x01){   //超时
			printf("识别超时\n");
			//playOrder=generateCommand(3, 0, 0x11, 0x00, MBL_param(2,1,1), 0x14); //唤醒指令  播放第一条语言   ASR中间方向音频循环识别  超时20s
			//sendMsg(playOrder,getCmdLen(playOrder));
		}
	    if(arg[cmdPos+1]==0x10){   //引擎出错
			printf("引擎出错\n");
		}
		break;
	case 0x20: //播音结束反馈
		//wakeUpMode(2);
		printf("++++++++++++++++++++++++播音结束+++++++++++++++++++++++++");
		break;
	case 0x30: //合成结束反馈
		printf("合成结束\n");
		break;
	default:
		break;
	}

	//printf("\n_________________________________________________________\n");
return 1;
}


/*
void main(){
	 generateCommand(3, 0, 0x11, 0x01, MBL_param(3,1,1), 0x14); //唤醒指令  播放第一条语言   多轮交互中间方向音频循环识别  超时20s

	 ////printf("score:%d  ",getNum(arg[cmdPos+2],arg[cmdPos+3]));
	//upCmdParsing(testData);
	while(1);
}*/