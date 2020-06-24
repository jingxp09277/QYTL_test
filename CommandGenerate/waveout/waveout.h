#ifndef waveout_h
#define waveout_h
#include <windows.h>
#include <mmsystem.h>
#include <list>

#pragma once
using namespace std;

#define BUFFER_SIZE 2560
#define BLOCK_SIZE 2560 + sizeof(WAVEHDR)


class waveout{
	WAVEFORMATEX wave_format;
	HWAVEOUT  h_waveout;
public:
	char m_buf[BUFFER_SIZE][BLOCK_SIZE];
	list<char*>m_buf_free;
	waveout();
	~waveout();
	bool start();
	bool stop();
	int input(unsigned char* buf);
	bool inlineis_start(){
		return (h_waveout != NULL);
	}
};
#endif