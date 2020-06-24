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
  //每读取一次dwSizeValueName和dwSizeofPortName都会被修改
  //注意一定要重置,否则会出现很离奇的错误,本人就试过因没有重置,出现读不了COM大于10以上的串口
  dwSizeValueName = NAME_LEN;
  dwSizeofPortName = NAME_LEN;
} while((status!= ERROR_NO_MORE_ITEMS));
RegCloseKey(hKey);
 printf("\n");
}