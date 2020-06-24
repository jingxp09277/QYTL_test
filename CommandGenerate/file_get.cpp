#include <iostream>
#include <io.h>
#include <string>
#include <vector>
#include <windows.h>
#include "file_get.h"

#include "waveout/waveout.h"
#include <fstream>
using namespace std;

void getFiles(string, vector<string>&);

extern "C" int paly_audio(char *filepath) ;
extern "C" int now_cmd;

char cp[1280]={0};
waveout wout;

void sendfile(string filename){
	//="KeyboardTest.bin";
    ifstream infile;
    infile.open(filename.c_str(),ios::binary);
    if (!infile)
    {
		printf("\n没有该文件");
        return;
    }
    infile.seekg( 0 , ios::end );
    unsigned long len = infile.tellg();
	infile.seekg(0,ios::beg);
	unsigned long now_position=infile.tellg();
	 BYTE bytesfile[2560];

	while(now_position!=-1){
		infile.read( reinterpret_cast<char*>(bytesfile), sizeof(bytesfile)* sizeof(BYTE));
		now_position=infile.tellg();
		//printf("\nnow_p:%d ----  len:%d",now_position,len);
		//p.input(bytesfile,sizeof(bytesfile));
		wout.input(bytesfile);
		memset(bytesfile,0,sizeof(bytesfile));
		//Sleep(100);
	}
	printf("\n音频发送完成");
    infile.close();
}
int get_ALLFiles(char *filePath,char arr[])
{
	FILE* fp = NULL; // 文件指针
	errno_t eResult;
	
	wout.start();


	int j=0;
    vector<string> files;

    getFiles( "allAuido", files );

    // print the files get
    for(;j< files.size(); ++j)
    {
		sendfile(files[j]);
		//paly_audio((char *)files[j].c_str()) ;
		Sleep(6000);
		printf(" 当前文件位置：%d   文件名：%s   识别命令词序号：%d \n",j+1,(char *)files[j].c_str(),now_cmd);
		sprintf(cp,"当前文件位置：%d   文件名：%s   识别命令词序号：%d \n",j+1,(char *)files[j].c_str(),now_cmd);
		now_cmd=-1;
		
	// 以附加方式打开可读/写的文件, 如果没有此文件则会进行创建，然后以附加方式打开可读/写的文件
	eResult = fopen_s(&fp, "recognize_1.txt", "a+");
	// 打开文件失败
	if (eResult != 0){
		printf("打开文件失败！");
		exit(-1);}else{
	// 将追加内容写入文件指针当前的位置
	fputs(cp, fp);
	// 最后不要忘了,关闭打开的文件~~~
	fclose(fp);
		}
	Sleep(500);
    }   
	wout.stop();
    return j;
}

void getFiles(string path, vector<string>& files)
{
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;

    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            //如果是目录,迭代之
            //如果不是,加入列表
            if ((fileinfo.attrib &  _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
            }
            else
            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
            }
        }while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
}