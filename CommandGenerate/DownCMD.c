#include <stdarg.h>
#include <stdlib.h>
#include "DownCMD.h"
#include "string.h"


#define headLength 6
#define DataLength 3
#define modNumber 0x100		//取模参数
unsigned char *coomandArr=NULL;		//存放指令数组



void checkSumGen(unsigned char* Data_send,int headLen,int dataLen){
	int k=0;
	int allLen=headLen+dataLen;
	unsigned char sum=0;
	for(k=0;k<allLen;k++){
		if(k<=headLen-2){
			sum += Data_send[k];
		}
		if(k==headLen-1){
			Data_send[k]= modNumber-sum%modNumber;
			sum=0;
		}

		if(headLen <= k && k<= allLen-2){
			sum += Data_send[k];
		}
		if(k==allLen-1){
			Data_send[k]= modNumber-sum%modNumber;
		}
	}	
}


unsigned char* generateCommand(unsigned int count, unsigned char orderIndex, unsigned char order , ... ){ 
	 unsigned int i;
	unsigned int j=0;
	va_list valist;
	unsigned int AllLength=0;
	unsigned char commandHead[headLength]={0x58,0x46,0x00,0x00,orderIndex,0x00};
	unsigned char commandData[DataLength]={0xF0,0x00,order};
	AllLength=headLength+count+DataLength+1; //1 为最后的校验位

	//命令帧长度 低位在前，高位在后
	commandHead[2]=AllLength|commandHead[2];
	commandHead[3]= AllLength>>8|commandHead[3];

	free_arr(coomandArr);
	coomandArr = (unsigned char *)malloc(sizeof(unsigned char)*AllLength);
	memcpy(coomandArr,commandHead,headLength);
	memcpy(&coomandArr[headLength],commandData,DataLength);


	/* 为 count 个参数初始化 valist */
	va_start(valist, order);
	/* 访问所有赋给 valist 的参数 */
	for (i = 0;i < count;i++)
	{
	    coomandArr[headLength+DataLength+j]  = va_arg(valist, unsigned int);
		//printf("参数%d:%x",i,coomandArr[headLength+DataLength+j]);
		j++;
	}
	/* 清理为 valist 保留的内存 */
	va_end(valist);

	checkSumGen(coomandArr,headLength,AllLength-headLength);
	//printf("\n AllLength: %d \n",AllLength);
	//printf("\nTx:");
	for(i=0;i<AllLength;i++){
		//printf("%x ",coomandArr[i]);
	}
	
	return coomandArr;

}



unsigned char MBL_param(unsigned char mode,unsigned char beam,unsigned char loop){
	return mode|beam<<4|loop<<7;
}



void free_arr(unsigned char * fr){
	if(fr!=NULL){
		free(fr);
		fr=NULL;
	}
}

unsigned char* get_arr(){
	return coomandArr;
}


/*
int main(){
	 //1参数个数   2命令帧序号  3识别命令  4前置播音    5识别模式  6超时时间
	 generateCommand(3,0,0x11,0x01,MBL_param(3,1,1),0);
	//generateCommand(6,0,0x12,0x01,0,0,0);
	free(coomandArr);
	
	while(1){
		Sleep(1000);
	}
	return 0;
}
*/
