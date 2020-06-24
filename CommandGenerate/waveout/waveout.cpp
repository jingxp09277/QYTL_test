﻿#include "waveout.h"
#include "../dataStruct.h"


waveout::waveout(){
	wave_format.wFormatTag= WAVE_FORMAT_PCM;
	wave_format.nChannels= 1;
	wave_format.nSamplesPerSec= 16000;
	wave_format.wBitsPerSample= 16;
	wave_format.nAvgBytesPerSec= 32000;
	wave_format.nBlockAlign= 2;
	wave_format.cbSize= 0;
	h_waveout = NULL;
}

waveout::~waveout(){
	stop();
}

void __stdcall waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance,DWORD dwParam1, DWORD dwParam2){
	if(uMsg == WOM_DONE){
		WAVEHDR* p_wavehdr = (WAVEHDR *) dwParam1;
		waveout* p_wvo = (waveout *) dwInstance;
		p_wvo->m_buf_free.push_back((char *) p_wavehdr);
	}
}


int waveout::input(unsigned char* buf){
	size_t nSize = m_buf_free.size();
	if(nSize == 0)
		return 0;

	WAVEHDR *p_wavehdr = (WAVEHDR *) m_buf_free.front();
	m_buf_free.pop_front();

	memcpy(p_wavehdr->lpData, buf, RECORD_BUF_LENGTH);
	waveOutWrite(h_waveout, p_wavehdr, sizeof(WAVEHDR));

	return 0;
}

bool waveout::start(){
	if(h_waveout != NULL)
		return true;

	MMRESULT nRet = waveOutOpen(&h_waveout, WAVE_MAPPER, &wave_format, (DWORD) waveOutProc, (DWORD) this, CALLBACK_FUNCTION);
	if(nRet != MMSYSERR_NOERROR)
		return false;

	for(int i = 0; i < BUFFER_SIZE; ++ i)
	{
		WAVEHDR *p_wavehdr = (WAVEHDR *)m_buf[i];
		p_wavehdr->dwBufferLength = RECORD_BUF_LENGTH;
		p_wavehdr->lpData = m_buf[i] + sizeof(WAVEHDR);
		p_wavehdr->dwFlags = 0;

		waveOutPrepareHeader(h_waveout, p_wavehdr, sizeof(WAVEHDR));
		m_buf_free.push_back((char *) p_wavehdr);
	}

	return true;
}

bool waveout::stop(){
	if(h_waveout != NULL){
		while(m_buf_free.size() != BUFFER_SIZE)
			Sleep(80);
		m_buf_free.clear();
		waveOutReset(h_waveout);

		for(int i = 0; i < BUFFER_SIZE; ++ i){
			WAVEHDR *p_wavehdr = (WAVEHDR *)m_buf[i];
			waveOutUnprepareHeader(h_waveout, p_wavehdr, sizeof(WAVEHDR));
		}

		waveOutClose(h_waveout);
		h_waveout = NULL;
	}
	return true;
}