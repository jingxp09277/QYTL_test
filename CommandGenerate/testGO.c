#include "StdAfx.h"
#include "testGO.h"
#include  "UpCMD.h"
#include  "ttlWrapper.h"

#include  <windows.h>
#include <process.h>
#include <locale.h>

#include "pcm_play.h"
#include "file_get.h"

#include "mod.h"
#include "MSG_DEAL.h"
#include "Run_4002.h"



unsigned char databuf[1024]={0};
unsigned int __stdcall uartMessage(LPVOID lpParameter){
	unsigned char *dd=NULL;
	while(1){
			 dd=recMsg();
			 if(dd!=NULL){
				memcpy(databuf,dd,1024);
#if RUN_MODE==2
	recv_deal(databuf);
#else
	upCmdParsing(databuf);	
#endif
								

				memset(databuf,0,1024);
			 }
	}
}


//0x58 0x46 0x0D 0x00 0x00 0x55 0xF0 0x00 0x01 0x07 0xAA 0x0A 0x54
//unsigned char testData2[]={0x58,0x46,0xe,0x0,0x0,0x54,0xf0,0x0,0x12,0x2,0x0,0x0,0x0,0xfc};



unsigned int __stdcall palyAudioThread(LPVOID lpParameter){
	Sleep(3000);
	while(1){
		if(!paly_audio("allAuido/1001.pcm")){
			printf("\n打开文件失败");
		};
		Sleep(1000);
	
	}
}




void main(){
	int num=0;
	char fileList[512];
	//_wsetlocale(LC_ALL, _T(".51949")); //这东西只影响控制台 115200
	 int input;
	 int btl=9600;
	 int sl=1;
	 uartCOMGet();
	 label:
	 printf("输入串口号： ");
	 scanf("%d", &input);
	 printf("\n选择波特率 1.9600  2.115200 ： ");
	 scanf("%d", &sl);
	 if(sl==2){
		 btl=115200;
	 }
	if(!openPort(input,btl)){
		printf("打开设备失败\n");
		goto label;
	}
	init_uart(sendMsg);
	(HANDLE)_beginthreadex(NULL,0,uartMessage,NULL,0,NULL); 

#if RUN_MODE==2

#else
	wakeUpMode(1);
#endif
	

#if mode == 1
	Sleep(2000);
	//num=get_ALLFiles("allAuido",fileList);
#endif

	while(1){
		Sleep(10);
	}


}