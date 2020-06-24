#include "UARTLIST.h"
#include "windows.h"
#include<iostream>
#include <stdio.h>
#include <string.h>

UARTLIST::UARTLIST(void)
{
}


UARTLIST::~UARTLIST(void)
{
}

void UARTLIST::enumPort(void)
{
 
HKEY hKey;
LPCTSTR lpSubKey=L"HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
 
if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hKey)!= ERROR_SUCCESS)
{
  return ;
}
#define NAME_LEN 100
 
wchar_t szValueName[NAME_LEN];
BYTE szPortName[NAME_LEN];
LONG status;
DWORD dwIndex = 0;
DWORD dwSizeValueName=100;
DWORD dwSizeofPortName=100;
DWORD Type;
dwSizeValueName = NAME_LEN;
dwSizeofPortName = NAME_LEN;
do
{
  status = RegEnumValue(hKey, dwIndex++, szValueName, &dwSizeValueName, NULL, &Type,
   szPortName, &dwSizeofPortName);
  if((status == ERROR_SUCCESS))
  {
  // m_lstPort.AddString((char *)szPortName);
	  printf("\n");
	  for(int i=0;i<dwSizeValueName-3;i++)
		printf("%c",szPortName[i]);
    
  }
  //ÿ��ȡһ��dwSizeValueName��dwSizeofPortName���ᱻ�޸�
  //ע��һ��Ҫ����,�������ֺ�����Ĵ���,���˾��Թ���û������,���ֶ�����COM����10���ϵĴ���
  dwSizeValueName = NAME_LEN;
  dwSizeofPortName = NAME_LEN;
} while((status!= ERROR_NO_MORE_ITEMS));
RegCloseKey(hKey);
 printf("\n");
}