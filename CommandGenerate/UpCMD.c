#include "StdAfx.h"
#include "UpCMD.h"


#define modNumber 0x100		//ȡģ����




int getCmdLen(unsigned char *arg){
	int len=0;
	if(arg!=NULL){
		len=(len|arg[3])<<8|arg[2];
	}
	//printf("tx_len:%d",len);
	return len;
}


int getNum(unsigned char arg1,unsigned char arg2){
	int len=0;
	len=(len|arg2)<<8|arg1;
	return len;
}


int upCmdCheck(unsigned char *arg,int allLen){
	int k=0;
	int LCHK=0;
	int DCHK=0;
	int headLen=6;
	int dataLen=0;
	unsigned int chekNum=0;
	unsigned int sum=0;
	dataLen=allLen-headLen;

	//Э���� ����֡���4λ
	if(dataLen<4){
		return 0;
	}

	for(k=0;k<allLen;k++){
		//֡ͷУ��
		if(k<=headLen-2){
			sum += arg[k];
		}
		if(k==headLen-1){
			if(sum==0){
				return 0;
			}
			chekNum=modNumber-sum%modNumber;

			//printf("֡ͷ����ֵ��%x ʵ��ֵ��%x \n",chekNum,arg[k]);
			if((int)arg[k] == ((int)chekNum==modNumber? 0:chekNum)){  //
				LCHK=1;
			}else{
			 return 0;
			}
			sum=0;
		}
		//֡����У��
		if(headLen <= k && k<= allLen-2){
			sum += arg[k];
		}
		if(k==allLen-1){
			if(sum==0){
				return 0;
			}
			chekNum=modNumber-sum%modNumber;
			//printf("֡���ݼ���ֵ��%x ʵ��ֵ��%x\n",chekNum,arg[k]);
			if((int)arg[k]== ((int)chekNum==modNumber? 0:chekNum) ){//
				DCHK=1;
			}else{
			return 0;
			}
		}
	}

	return LCHK&&DCHK;
}






//void main(){
//	upCmdParsing(testData);
//	while(1){
//		Sleep(1000);
//	}
//}