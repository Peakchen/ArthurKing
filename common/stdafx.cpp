// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ArthurTest.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO:  �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

void Trace_In(const char* szFamt, ...)
{
#ifdef DEBUG
	char temp[10381];
	va_list args; 
	va_start(args, szFamt); 
	vsprintf_s(temp, sizeof(temp), szFamt, args); 
	va_end(args); 
	std::cout << temp << endl; 
#endif // DEBUG

}
