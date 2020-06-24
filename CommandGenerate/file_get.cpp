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
		printf("\nû�и��ļ�");
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
	printf("\n��Ƶ�������");
    infile.close();
}
int get_ALLFiles(char *filePath,char arr[])
{
	FILE* fp = NULL; // �ļ�ָ��
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
		printf(" ��ǰ�ļ�λ�ã�%d   �ļ�����%s   ʶ���������ţ�%d \n",j+1,(char *)files[j].c_str(),now_cmd);
		sprintf(cp,"��ǰ�ļ�λ�ã�%d   �ļ�����%s   ʶ���������ţ�%d \n",j+1,(char *)files[j].c_str(),now_cmd);
		now_cmd=-1;
		
	// �Ը��ӷ�ʽ�򿪿ɶ�/д���ļ�, ���û�д��ļ������д�����Ȼ���Ը��ӷ�ʽ�򿪿ɶ�/д���ļ�
	eResult = fopen_s(&fp, "recognize_1.txt", "a+");
	// ���ļ�ʧ��
	if (eResult != 0){
		printf("���ļ�ʧ�ܣ�");
		exit(-1);}else{
	// ��׷������д���ļ�ָ�뵱ǰ��λ��
	fputs(cp, fp);
	// ���Ҫ����,�رմ򿪵��ļ�~~~
	fclose(fp);
		}
	Sleep(500);
    }   
	wout.stop();
    return j;
}

void getFiles(string path, vector<string>& files)
{
    //�ļ����
    long hFile = 0;
    //�ļ���Ϣ
    struct _finddata_t fileinfo;
    string p;

    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
    {
        do
        {
            //�����Ŀ¼,����֮
            //�������,�����б�
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