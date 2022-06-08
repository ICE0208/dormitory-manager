#pragma once
#include <stdio.h>
#include <windows.h>

#ifndef CLEAR
#define CLEAR "cls"
#endif

#ifndef TEXTMAX
#define TEXTMAX 20
#endif

#ifndef FLOORMAX
#define FLOORMAX 15
#endif

#ifndef HOMAX
#define HOMAX 20
#endif

#ifndef STUMAX
#define STUMAX 3
#endif

#ifndef DEFAULT_TITLE
#define DEFAULT_TITLE L"기숙사 관리 프로그램 - "
#endif

#ifndef DEFAULT_NAME
#define DEFAULT_NAME "미지정"
#endif

#ifndef DEFAULT_SNUM
#define DEFAULT_SNUM 0
#endif

#ifndef DEFAULT_PHONENUM
#define DEFAULT_PHONENUM "010-xxxx-xxxx"
#endif

#ifndef DEFAULT_BREAKFAST
#define DEFAULT_BREAKFAST 0
#endif

extern int clearBuffer();
extern void setTitle(wchar_t* title);
extern void printInputErrMsg();