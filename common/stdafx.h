// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

//#include <Windows.h>
//#include <winuser.h>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <algorithm>
#include <ostream>
#include <time.h>

#include <SDKDDKVer.h>
#include <stdarg.h>

#include "AIPersonMessageMacro.h"

using namespace std;

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����

//#define GWORD unsigned long 
//
//#define LPCSTR char *


// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�

/************************************************************************/
/*
func: print some param info
return: no
param: ...
*/
/************************************************************************/
void Trace_In(const char* szFamt, ...);
