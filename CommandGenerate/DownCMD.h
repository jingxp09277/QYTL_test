#pragma once
#ifndef _DOWNCMD_H
#define _DOWNCMD_H

/** 
* @brief У�������
* @param Data_send  Ҫ���������
* @param headLen  ����ͷ����
* @param dataLen  ����֡����
*/
void checkSumGen(unsigned char* Data_send,int headLen,int dataLen);

/** 
* @brief ������������
* @param count  �������� 
* @param orderIndex  ����֡��� һ���ֽ�
* @param order  ������
* @param ...  ��������
*/
unsigned char* generateCommand(unsigned int count, unsigned char orderIndex, unsigned char order , ... );

/** 
* @brief ����ʶ�������MBL����
* @param mode  ģʽ
* @param beam  ʰ������
* @param loop  �Ƿ�ѭ��
*/
unsigned char MBL_param(unsigned char mode,unsigned char beam,unsigned char loop);


/** 
* @brief �ͷ����ɵĿռ�
* @param fr  �ͷŶ���
*/
void free_arr(unsigned char * fr);


/** 
* @brief ��ô��ָ�������
* @return 
*	-<em>arr</em> ���ָ�������ָ��
*/
unsigned char* get_arr();

#endif