#include "pcm_play.h"
#include <stdio.h>
#include <Windows.h>
 
#pragma comment(lib, "winmm.lib")
 
#define DATASIZE 1024*10  //�ִν�ȡ���ݴ�С
FILE*			pcmfile;  //��Ƶ�ļ�
HWAVEOUT        hwo;
 
void CALLBACK WaveCallback(HWAVEOUT hWave, UINT uMsg, DWORD dwInstance, DWORD dw1, DWORD dw2)//�ص�����
{
	switch (uMsg)
	{
		case WOM_DONE://�ϴλ��沥�����,�������¼�
		{
				//printf("\naaaaaasssssss");
			LPWAVEHDR pWaveHeader = (LPWAVEHDR)dw1;
			pWaveHeader->dwBufferLength = fread(pWaveHeader->lpData, 1, DATASIZE, pcmfile);;
			waveOutPrepareHeader(hwo, pWaveHeader, sizeof(WAVEHDR));
			waveOutWrite(hwo, pWaveHeader, sizeof(WAVEHDR));
			break;
		}
	}
}
 
int paly_audio(char *filepath) 
{
	int             cnt;
	WAVEHDR         wh1;
	WAVEHDR         wh2;
	WAVEFORMATEX    wfx;
 
	if(fopen_s(&pcmfile, filepath, "rb")){//"allAuido/1001.pcm"
		printf("\n����Ƶʧ��");
		return 0;
	};//���ļ�
	wfx.wFormatTag = WAVE_FORMAT_PCM;//���ò��������ĸ�ʽ
	wfx.nChannels = 1;//������Ƶ�ļ���ͨ������
	wfx.nSamplesPerSec = 16000;//����ÿ���������źͼ�¼ʱ������Ƶ��
	wfx.nAvgBytesPerSec = 32000;//���������ƽ�����ݴ�����,��λbyte/s�����ֵ���ڴ��������С�Ǻ����õ�
	wfx.nBlockAlign = 2;//���ֽ�Ϊ��λ���ÿ����
	wfx.wBitsPerSample = 16;
	wfx.cbSize = 0;//������Ϣ�Ĵ�С
 
	waveOutOpen(&hwo, WAVE_MAPPER, &wfx, (DWORD)WaveCallback, 0L, CALLBACK_FUNCTION);//��һ�������Ĳ�����Ƶ���װ���������������ţ���ʽΪ�ص�������ʽ������ǶԻ�����򣬿��Խ������������Ϊ(DWORD)this����������Demo��������

	wh1.dwLoops = 0L;//������һ
	wh1.lpData = new char[DATASIZE];
	wh1.dwBufferLength = DATASIZE; 
	fread(wh1.lpData, 1, DATASIZE, pcmfile);
	wh1.dwFlags = 0L;
	waveOutPrepareHeader(hwo, &wh1, sizeof(WAVEHDR));//׼��һ���������ݿ����ڲ���
	waveOutWrite(hwo, &wh1, sizeof(WAVEHDR));//����Ƶý���в��ŵڶ�������ָ�������ݣ�Ҳ�൱�ڿ���һ������������˼
	wh2.dwLoops = 0L;//��������������ͬ��
	wh2.lpData = new char[DATASIZE];
	wh2.dwBufferLength = DATASIZE;
	fread(wh2.lpData, 1, DATASIZE, pcmfile);
	wh2.dwFlags = 0L;
	waveOutPrepareHeader(hwo, &wh2, sizeof(WAVEHDR));
	waveOutWrite(hwo, &wh2, sizeof(WAVEHDR));
 
	while (wh1.dwBufferLength != 0 || wh2.dwBufferLength != 0)//����ļ�����û��������ȴ�500ms
	{
		printf("\n wait paly %d ,%d",wh1.dwBufferLength,wh2.dwBufferLength);
		Sleep(500);
	}


	printf("\n De1 1");


	waveOutUnprepareHeader(hwo, &wh1, sizeof(WAVEHDR));//��������
	waveOutUnprepareHeader(hwo, &wh2, sizeof(WAVEHDR));
	
	delete []wh1.lpData;
	delete []wh2.lpData;

	Sleep(1000);

	printf("\n waveOutReset 1");
	//waveOutReset(hwo);
	printf("\n waveOut 1");
	waveOutClose(hwo);

	printf("\n waveOutClose 1");
	//hwo=NULL;
	Sleep(1000);
	printf("\n fclose 0");
	fclose(pcmfile);//�ر��ļ�
	printf("\n fclose 1");

	
	return 1;
}
