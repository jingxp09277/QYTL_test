#pragma once
#ifndef _UPCMD_H
#define _UPCMD_H

/** 
* @brief 上传命令校验位检测
* @param arg  指令数组
* @param allLen 指令数组长度
* @return 
*	-<em>1</em> 校验成功
*	-<em>0</em> 校验失败
*/
int upCmdCheck(unsigned char *arg,int allLen);


/** 
* @brief 上传命令长度解析
* @param arg  指令数组
* @return 
*	-<em>len</em> 长度
*/
int getCmdLen(unsigned char *arg);



/** 
* @brief 对命令中的两个字节长度的数字解析 比如命令长度 或者 识别得分
* @param arg1 低字节 
* @param arg1 高字节  
* @return 
*	-<em>num</em>  转换后对应的数 
*/
int getNum(unsigned char arg1,unsigned char arg2);



/** 
* @brief 上传命令解析
* @param arg  指令数组
* @return 
*	-<em>1</em> 解析成功
*   -<em>0</em> 解析失败
*/
int upCmdParsing(unsigned char *arg);

#endif