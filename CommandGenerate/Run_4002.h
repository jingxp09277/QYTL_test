#pragma once
#ifndef _RUN4002_H
#define _RUN4002_H



/** 
* @brief 上传命令解析
* @param arg  指令数组
* @return 
*	-<em>1</em> 解析成功
*   -<em>0</em> 解析失败
*/
int upCmdParsing(unsigned char *arg);

unsigned char* wakeUpMode(int i);

#endif