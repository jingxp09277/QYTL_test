#pragma once
#ifndef _DOWNCMD_H
#define _DOWNCMD_H

/** 
* @brief 校验和生成
* @param Data_send  要计算的数组
* @param headLen  命令头长度
* @param dataLen  命令帧长度
*/
void checkSumGen(unsigned char* Data_send,int headLen,int dataLen);

/** 
* @brief 生成命令数组
* @param count  参数个数 
* @param orderIndex  命令帧序号 一个字节
* @param order  命令字
* @param ...  命令内容
*/
unsigned char* generateCommand(unsigned int count, unsigned char orderIndex, unsigned char order , ... );

/** 
* @brief 生成识别命令的MBL参数
* @param mode  模式
* @param beam  拾音波束
* @param loop  是否循环
*/
unsigned char MBL_param(unsigned char mode,unsigned char beam,unsigned char loop);


/** 
* @brief 释放生成的空间
* @param fr  释放对象
*/
void free_arr(unsigned char * fr);


/** 
* @brief 获得存放指令的数组
* @return 
*	-<em>arr</em> 存放指令的数组指针
*/
unsigned char* get_arr();

#endif