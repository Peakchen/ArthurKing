// stdafx.cpp : 只包括标准包含文件的源文件
// ArthurTest.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO:  在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用

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
