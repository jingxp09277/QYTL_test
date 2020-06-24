#pragma once
#ifndef _UPCMD_H
#define _UPCMD_H

/** 
* @brief �ϴ�����У��λ���
* @param arg  ָ������
* @param allLen ָ�����鳤��
* @return 
*	-<em>1</em> У��ɹ�
*	-<em>0</em> У��ʧ��
*/
int upCmdCheck(unsigned char *arg,int allLen);


/** 
* @brief �ϴ�����Ƚ���
* @param arg  ָ������
* @return 
*	-<em>len</em> ����
*/
int getCmdLen(unsigned char *arg);



/** 
* @brief �������е������ֽڳ��ȵ����ֽ��� ��������� ���� ʶ��÷�
* @param arg1 ���ֽ� 
* @param arg1 ���ֽ�  
* @return 
*	-<em>num</em>  ת�����Ӧ���� 
*/
int getNum(unsigned char arg1,unsigned char arg2);



/** 
* @brief �ϴ��������
* @param arg  ָ������
* @return 
*	-<em>1</em> �����ɹ�
*   -<em>0</em> ����ʧ��
*/
int upCmdParsing(unsigned char *arg);

#endif